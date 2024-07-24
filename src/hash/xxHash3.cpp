#include"xxHash/xxh3.h"
#include<hgl/util/hash/Hash.h>
#include<random>

namespace hgl
{
    namespace util
    {
        namespace
        {
            static std::random_device rd;
            static std::mt19937 mt_rand32(rd());
            static std::uniform_int_distribution<uint32> mt_rand32_dist;

            static std::mt19937_64 mt_rand64(rd());
            static std::uniform_int_distribution<uint64> mt_rand64_dist;
        }

        class xxHash32:public Hash
        {
            XXH32_state_t *state=nullptr;
            uint32 seed;

        public:

            void GetName(UTF8String &str)const override{str=U8_TEXT("XXH32");}
            void GetName(UTF16String &str)const override{str=U16_TEXT("XXH32");}

            const int GetHashBytes()const override{return 4;}

            void Init()override
            {
                state=XXH32_createState();
                seed=0;//mt_rand32_dist(mt_rand32);

                XXH32_reset(state,seed);
            }

            void Update(const void *input,uint inputLen)override
            {
                XXH32_update(state,input,inputLen);
            }

            void Final(void *digest)override
            {
                *(XXH32_hash_t *)digest=XXH32_digest(state);
            }
        };//class xxHash32

        Hash *CreatexxH32Hash()
        {
            return(new xxHash32);
        }

        class xxHash64:public Hash
        {
            XXH64_state_t *state=nullptr;
            uint64 seed;

        public:

            void GetName(UTF8String &str)const override{str=U8_TEXT("XXH64");}
            void GetName(UTF16String &str)const override{str=U16_TEXT("XXH64");}
    
            const int GetHashBytes()const override{return 8;}
    
            void Init()override
            {
                state=XXH64_createState();
                seed=0;//mt_rand64_dist(mt_rand64);
    
                XXH64_reset(state,seed);
            }
    
            void Update(const void *input,uint inputLen)override
            {
                XXH64_update(state,input,inputLen);
            }
    
            void Final(void *digest)override
            {
                *(XXH64_hash_t *)digest=XXH64_digest(state);
            }
        };//class xxHash64

        Hash *CreatexxH64Hash()
        {
            return(new xxHash64);
        }

        class xxHash3_64:public Hash
        {
            XXH3_state_t *state=nullptr;
            uint64 seed;

        public:

            void GetName(UTF8String &str)const override{str=U8_TEXT("XXH3_64bits");}
            void GetName(UTF16String &str)const override{str=U16_TEXT("XXH3_64bits");}

            const int GetHashBytes()const override{return 8;}

            void Init()override
            {
                state=XXH3_createState();
                seed=0;//mt_rand64_dist(mt_rand64);

                XXH3_64bits_reset_withSeed(state,seed);
            }

            void Update(const void *input,uint inputLen)override
            {
                XXH3_64bits_update(state,input,inputLen);
            }

            void Final(void *digest)override
            {
                *(XXH64_hash_t *)digest=XXH3_64bits_digest(state);
            }
        };//class xxHash3_64

        Hash *CreateXXH3_64Hash()
        {
            return(new xxHash3_64);
        }

        class xxHash3_128:public Hash
        {
            XXH3_state_t *state=nullptr;
            XXH64_hash_t seed;

        public:

            void GetName(UTF8String &str)const override{str=U8_TEXT("XXH3_128bits");}
            void GetName(UTF16String &str)const override{str=U16_TEXT("XXH3_128bits");}

            const int GetHashBytes()const override{return 16;}

            void Init()override
            {
                state=XXH3_createState();
                seed=0;//mt_rand64_dist(mt_rand64);

                XXH3_128bits_reset_withSeed(state,seed);
            }

            void Update(const void *input,uint inputLen)override
            {
                XXH3_128bits_update(state,input,inputLen);
            }

            void Final(void *digest)override
            {
                *(XXH128_hash_t *)digest=XXH3_128bits_digest(state);
            }
        };//class xxHash3_128

        Hash *CreateXXH3_128Hash()
        {
            return(new xxHash3_128);
        }
    }//namespace util
}//namespace hgl
