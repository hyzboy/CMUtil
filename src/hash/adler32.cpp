﻿#include<hgl/util/hash/Hash.h>

namespace hgl
{
    namespace
    {
        #define BASE 65521UL    /* largest prime smaller than 65536 */
        #define NMAX 5552
        /* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
        #define DO1(buf,i)  {adler += (buf)[i]; sum2 += adler;}
        #define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
        #define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
        #define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
        #define DO16(buf)   DO8(buf,0); DO8(buf,8);
        /* use NO_DIVIDE if your processor does not do division in hardware */
        #define NO_DIVIDE            //不使用除法
        #ifdef NO_DIVIDE
        #  define MOD(a) \
            do { \
                if (a >= (BASE << 16)) a -= (BASE << 16); \
                if (a >= (BASE << 15)) a -= (BASE << 15); \
                if (a >= (BASE << 14)) a -= (BASE << 14); \
                if (a >= (BASE << 13)) a -= (BASE << 13); \
                if (a >= (BASE << 12)) a -= (BASE << 12); \
                if (a >= (BASE << 11)) a -= (BASE << 11); \
                if (a >= (BASE << 10)) a -= (BASE << 10); \
                if (a >= (BASE << 9)) a -= (BASE << 9); \
                if (a >= (BASE << 8)) a -= (BASE << 8); \
                if (a >= (BASE << 7)) a -= (BASE << 7); \
                if (a >= (BASE << 6)) a -= (BASE << 6); \
                if (a >= (BASE << 5)) a -= (BASE << 5); \
                if (a >= (BASE << 4)) a -= (BASE << 4); \
                if (a >= (BASE << 3)) a -= (BASE << 3); \
                if (a >= (BASE << 2)) a -= (BASE << 2); \
                if (a >= (BASE << 1)) a -= (BASE << 1); \
                if (a >= BASE) a -= BASE; \
            } while (0)
        #  define MOD4(a) \
            do { \
                if (a >= (BASE << 4)) a -= (BASE << 4); \
                if (a >= (BASE << 3)) a -= (BASE << 3); \
                if (a >= (BASE << 2)) a -= (BASE << 2); \
                if (a >= (BASE << 1)) a -= (BASE << 1); \
                if (a >= BASE) a -= BASE; \
            } while (0)
        #else
        #  define MOD(a) a %= BASE
        #  define MOD4(a) a %= BASE
        #endif
    }//namespace

    namespace util
    {
        /**
        * Adler32校检码计算
        * @param adler 初始码
        * @param buf 待校验数据指针
        * @param len 待校验数据长度
        * @return 校检码
        */
        uint32 CountAdler32(uint32 adler,const uint8 *buf,uint32 len)
        {
            uint32 sum2;
            uint32 n;
            /* split Adler-32 into component sums */
            sum2 = (adler >> 16) & 0xffff;
            adler &= 0xffff;
            /* in case user likes doing a byte at a time, keep it fast */
            if (len == 1) {
                adler += buf[0];
                if (adler >= BASE)
                    adler -= BASE;
                sum2 += adler;
                if (sum2 >= BASE)
                    sum2 -= BASE;
                return adler | (sum2 << 16);
            }
            /* initial Adler-32 value (deferred check for len == 1 speed) */
            if (buf == 0)
                return 1L;
            /* in case short lengths are provided, keep it somewhat fast */
            if (len < 16) {
                while (len--) {
                    adler += *buf++;
                    sum2 += adler;
                }
                if (adler >= BASE)
                    adler -= BASE;
                MOD4(sum2);             /* only added so many BASE's */
                return adler | (sum2 << 16);
            }
            /* do length NMAX blocks -- requires just one modulo operation */
            while (len >= NMAX) {
                len -= NMAX;
                n = NMAX / 16;          /* NMAX is divisible by 16 */
                do {
                    DO16(buf);          /* 16 sums unrolled */
                    buf += 16;
                } while (--n);
                MOD(adler);
                MOD(sum2);
            }
            /* do remaining bytes (less than NMAX, still just one modulo) */
            if (len) {                  /* avoid modulos if none remaining */
                while (len >= 16) {
                    len -= 16;
                    DO16(buf);
                    buf += 16;
                }
                while (len--) {
                    adler += *buf++;
                    sum2 += adler;
                }
                MOD(adler);
                MOD(sum2);
            }
            /* return recombined sums */
            return adler | (sum2 << 16);
        }

        class Adler32:public Hash
        {
            uint32 result;

        public:

            Adler32():Hash(4,"Adler32"){}

            void Init()override
            {
                result=0;
            }

            void Update(const void *input,uint inputLen)override
            {
                result=CountAdler32(result,(const uint8 *)input,inputLen);
            }

            void Final(void *digest)override
            {
                *(uint32 *)digest=result;
            }
        };//class Adler32

        template<> Hash *CreateHash<HASH::Adler32>()
        {
            return(new Adler32());
        }
    }//namespace util
}//namespace hgl
