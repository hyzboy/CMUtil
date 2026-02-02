#include<hgl/util/hash/Hash.h>

namespace hgl::util::hash
{
    namespace
    {
        //本代码来自Github Copilot
        //MurmurHash 是一种高性能的哈希算法，特别适用于哈希表。它具有良好的分布性和较低的碰撞率。

        uint32_t CountMurmurHash3(const void *key, int len, uint32_t seed)
        {
            const uint8_t *data = (const uint8_t *)key;
            const int nblocks = len / 4;
            uint32_t h1 = seed;

            const uint32_t c1 = 0xcc9e2d51;
            const uint32_t c2 = 0x1b873593;

            // Body
            const uint32_t *blocks = (const uint32_t *)(data + nblocks * 4);
            for (int i = -nblocks; i; i++) {
                uint32_t k1 = blocks[i];

                k1 *= c1;
                k1 = (k1 << 15) | (k1 >> (32 - 15));
                k1 *= c2;

                h1 ^= k1;
                h1 = (h1 << 13) | (h1 >> (32 - 13));
                h1 = h1 * 5 + 0xe6546b64;
            }

            // Tail
            const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
            uint32_t k1 = 0;

            switch (len & 3)
            {
                case 3:
                    k1 ^= tail[2] << 16;
                case 2:
                    k1 ^= tail[1] << 8;
                case 1:
                    k1 ^= tail[0];
                    k1 *= c1;
                    k1 = (k1 << 15) | (k1 >> (32 - 15));
                    k1 *= c2;
                    h1 ^= k1;
            }

            // Finalization
            h1 ^= len;
            h1 ^= h1 >> 16;
            h1 *= 0x85ebca6b;
            h1 ^= h1 >> 13;
            h1 *= 0xc2b2ae35;
            h1 ^= h1 >> 16;

            return h1;
        }
    }//namespace

    class MurmurHash3:public hash::Base<MurmurHash3, 16>
    {
        uint32_t result;

    public:

        MurmurHash3() = default;
        void Init()
        {
            result=0;
        }
        void Update(const void *input,uint inputLen)
        {
            result=CountMurmurHash3(input,inputLen,result);
        }
        void Final(void *digest)
        {
            *(uint32_t *)digest=result;
        }
    };//class MurmurHash3

    void ComputeHash_MurmurHash3(const void* data, uint size, void* result)
    {
        MurmurHash3 h;
        h.Init();
        h.Update(data, size);
        h.Final(result);
    }

}//namespace hgl::util::hash
