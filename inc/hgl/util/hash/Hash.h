#pragma once

#include<hgl/type/String.h>
namespace hgl
{
    namespace util
    {
        /**
        * Hash算法枚举
        */
        enum class HASH			    ///Hash算法枚举
        {
            Adler32,				///<一种较CRC32更为安全的快速HASH算法
            CRC32,					///<最快速的HASH算法，但最不安全，仅用于低安全性的简单验证
            MD4,					///<较MD5在安全性下稍弱。但仍未被攻破，且较MD5更快
            MD5,					///<最常用的HASH算法

            SHA1,					///<较MD5更为安全，但计算较慢
            SHA1LE,                 ///<SHA1改版
            SHA256,
            SHA512,

            xxH32,
            xxH64,
            xxH3_64,
            xxH3_128,

            FNV1a,
            Murmur3,
            City32,
            City64,
            City128,

            ENUM_CLASS_RANGE(Adler32,City128)
        };//enum HASH

        /**
        * Hash编码结构模板
        */
        template<size_t SIZE> struct HashCode
        {
            uint8 code[SIZE]{};

        public:

            template<typename T>
            using CharArray=T[(SIZE<<1)+1];

        public:

            static constexpr int size()noexcept{return SIZE;}

            const uint8 operator[](int index)const{return code[index];}

            void CopyFrom   (const void *ptr){memcpy(code,ptr,SIZE);}
            void FromString (const char *str){ParseHexStr(code,str,SIZE);}

            template<typename T> void ToUpperString(T *str,const T gap_char=0) const {ToUpperHexStr<T>(str,code,SIZE,gap_char);}
            template<typename T> void ToLowerString(T *str,const T gap_char=0) const {ToLowerHexStr<T>(str,code,SIZE,gap_char);}
        };//template<size_t SIZE> struct HashCode

        /**
        * 散列值计算功能基类
        */
        class Hash											///散列值计算功能基类
        {
            AnsiString hash_name;
            size_t hash_size;

        public:

            Hash(const size_t s,const AnsiString &n):hash_size(s),hash_name(n){}
            virtual ~Hash()=default;
            
                    void    GetName     (AnsiString &name)const {name=hash_name;}                   ///<取得HASH算法的名称
            const   size_t  GetHashBytes()const noexcept        {return hash_size;}                 ///<取得HASH码字节长度(MD4/MD5为16,SHA1为20)

            virtual void Init()=0;							///<初始化散列值计算
            virtual void Update(const void *,uint)=0;		///<提交新的数据
            virtual void Final(void *)=0;					///<结束并取得结果

            template<typename T>
                void Write(const T &data)
                {
                    Update(&data,sizeof(T));
                }

            template<typename T>
                void Write(const T *ptr,const uint count)
                {
                    Update(ptr,sizeof(T)*count);
                }
        };//class Hash

        template<HASH ha> Hash *CreateHash();					///<创建一个hash值计算类实例

        Hash *CreateHash(const HASH ha);                        ///<创建一个hash值计算类实例

        /**
        * 计算一段数据的Hash值
        * @param data 数据指针
        * @param size 数据长度
        * @param ha hash算法
        * @param hash_code 计算后的hash值存放处
        * @return 是否计算成功
        */
        template<HASH ha> bool CountHash(const void *data,int size,void *hash_code)
        {
            if(!data||size<=0||!hash_code)return(false);

            Hash *h=CreateHash<ha>();

            if(!h)return(false);

            h->Init();
            h->Update(data,size);
            h->Final(hash_code);

            delete h;
            return(true);
        }

        /**
        * 取得一个文件的hash值
        * @param filename 文件名
        * @param ha hash对象
        * @param hash_code 计算后的hash存放处
        * @return 是否计算成功
        */
        bool GetFileHash(const OSString &filename,Hash *ha,void *hash_code);

        template<typename ha> bool GetFileHash(const OSString &filename,void *hash_code,size_t &hash_size)
        {
            Hash *h=CreateHash<ha>();
            if(!h)return(false);

            if(!GetFileHash(filename,h,hash_code))
            {
                delete h;
                return(false);
            }
            hash_size=h->GetHashBytes();
            delete h;
            return(true);
        }

        /**
        * 取得一个文件的hash值
        * @param filename 文件名
        * @param ha hash算法
        * @param hash_str 计算后的hash值存放处
        * @param litter 小写字母
        * @return 是否计算成功
        */
        //bool GetFileHash(const OSString &filename,HASH ha,U8String &hash_str,bool litter=true);
    }//namespace util
}//namespace hgl
