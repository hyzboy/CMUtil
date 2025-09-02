// source codes repository: https://github.com/google/cityhash.git

// vcpkg： cityhash, cityhash[sse]

#include<hgl/util/hash/Hash.h>

#include"city.h"

namespace hgl::util
{
    class GoogleCityHash32:public Hash
    {
        uint32 result;

    public:

        GoogleCityHash32():Hash(4,"CityHash32")
        {}
        void Init()override
        {
            result=0;
        }
        void Update(const void *input,uint inputLen)override
        {
            result=CityHash32((const char *)input,inputLen);
        }
        void Final(void *digest)override
        {
            *(uint32 *)digest=result;
        }
    };

    template<> Hash *CreateHash<HASH::City32>()
    {
        return(new GoogleCityHash32);
    }

    class GoogleCityHash64:public Hash
    {
        uint64 result;

    public:

        GoogleCityHash64():Hash(8,"CityHash64")
        {}
        void Init()override
        {
            result=0;
        }
        void Update(const void *input,uint inputLen)override
        {
            result=::CityHash64WithSeed((const char *)input,inputLen,result);
        }
        void Final(void *digest)override
        {
            *(uint64 *)digest=result;
        }
    };//class CityHash64:public Hash

    template<> Hash *CreateHash<HASH::City64>()
    {
        return(new GoogleCityHash64);
    }

    class GoogleCityHash128:public Hash
    {
        uint128 result;

    public:

        GoogleCityHash128():Hash(16,"CityHash128")
        {}
        void Init()override
        {
            result.first=0;
            result.second=0;
        }
        void Update(const void *input,uint inputLen)override
        {
            ::CityHash128WithSeed((const char *)input,inputLen,result);
        }
        void Final(void *digest)override
        {
            ((uint64 *)digest)[0]=result.first;
            ((uint64 *)digest)[1]=result.second;
        }
    };//class CityHash128:public Hash

    template<> Hash *CreateHash<HASH::City128>()
    {
        return(new GoogleCityHash128);
    }
}//namespace hgl::util
