#include<hgl/util/hash/Hash.h>

namespace hgl
{
    namespace util
    {
        namespace
        {
            uint32_t CountFNV1a(uint32_t hash,const void *key, int len)
            {
                //本代码来自Github Copilot

                //FNV-1a 是一种简单且高效的哈希算法，适用于大多数场景。它具有良好的分布性和较快的计算速度。

                const uint8_t *data = (const uint8_t *)key;

                for (int i = 0; i < len; ++i) {
                    hash ^= data[i];
                    hash *= 16777619u;
                }

                return hash;
            }
        }//namespace

        class FNV1a:public Hash
        {
            uint32_t result;

        public:

            FNV1a():Hash(4,"FNV1a"){}

            void Init()override
            {
                result=2166136261u;
            }
            void Update(const void *input,uint inputLen)override
            {
                result=CountFNV1a(result,input,inputLen);
            }
            void Final(void *digest)override
            {
                *(uint32_t *)digest=result;
            }
        };//class FNV1a

        template<> Hash *CreateHash<HASH::FNV1a>()
        {
            return(new FNV1a);
        }
    }//namespace util
}//namespace hgl
