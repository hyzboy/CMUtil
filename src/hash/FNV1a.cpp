#include<hgl/util/hash/Hash.h>

namespace hgl
{
    namespace util
    {
        namespace
        {
            uint32_t FNV1aHash(const void *key, int len)
            {
                //本代码来自Github Copilot

                //FNV-1a 是一种简单且高效的哈希算法，适用于大多数场景。它具有良好的分布性和较快的计算速度。

                const uint8_t *data = (const uint8_t *)key;
                uint32_t hash = 2166136261u;

                for (int i = 0; i < len; ++i) {
                    hash ^= data[i];
                    hash *= 16777619u;
                }

                return hash;
            }
        }//namespace
    }//namespace util
}//namespace hgl
