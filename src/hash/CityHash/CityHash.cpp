// source codes repository: https://github.com/google/cityhash.git

// vcpkg： cityhash, cityhash[sse]

#include<hgl/util/hash/Hash.h>

#include"city.h"

namespace hgl::util
{
    class GoogleCityHash32:public HashBase<GoogleCityHash32, 4>
    {
        uint32 result;

    public:

        GoogleCityHash32() = default;
        void Init()
        {
            result=0;
        }
        void Update(const void *input,uint inputLen)
        {
            result=CityHash32((const char *)input,inputLen);
        }
        void Final(void *digest)
        {
            *(uint32 *)digest=result;
        }
    };

    class GoogleCityHash64:public HashBase<GoogleCityHash64, 8>
    {
        uint64 result;

    public:

        GoogleCityHash64() = default;
        void Init()
        {
            result=0;
        }
        void Update(const void *input,uint inputLen)
        {
            result=::CityHash64WithSeed((const char *)input,inputLen,result);
        }
        void Final(void *digest)
        {
            *(uint64 *)digest=result;
        }
    };

    class GoogleCityHash128:public HashBase<GoogleCityHash128, 16>
    {
        uint128 result;

    public:

        GoogleCityHash128() = default;
        void Init()
        {
            result.first=0;
            result.second=0;
        }
        void Update(const void *input,uint inputLen)
        {
            ::CityHash128WithSeed((const char *)input,inputLen,result);
        }
        void Final(void *digest)
        {
            ((uint64 *)digest)[0]=result.first;
            ((uint64 *)digest)[1]=result.second;
        }
    };//class CityHash128:public Hash

}//namespace hgl::util
