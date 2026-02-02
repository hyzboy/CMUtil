#include<hgl/util/hash/Hash.h>

namespace hgl::util::hash
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

        class FNV1a:public hash::Base<FNV1a, 8>
        {
            uint32_t result;

        public:

            FNV1a() = default;

            void Init()
            {
                result=2166136261u;
            }
            void Update(const void *input,uint inputLen)
            {
                result=CountFNV1a(result,input,inputLen);
            }
            void Final(void *digest)
            {
                *(uint32_t *)digest=result;
            }
        };//class FNV1a

        void ComputeHash_FNV1a(const void* data, uint size, void* result)
        {
            FNV1a h;
            h.Init();
            h.Update(data, size);
            h.Final(result);
        }
        
}//namespace hgl::util::hash
