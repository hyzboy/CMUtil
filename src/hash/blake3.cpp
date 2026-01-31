#include<hgl/util/hash/Hash.h>
#include<blake3.h>

namespace hgl::util
{
    class Blake3:public HashBase<Blake3, 32>
    {
        blake3_hasher hasher{};

    public:

        Blake3() = default;

        void Init()
        {
            blake3_hasher_init(&hasher);
        }

        void Update(const void *input,uint inputLen)
        {
            if(!input || inputLen==0) return;
            blake3_hasher_update(&hasher, input, inputLen);
        }

        void Final(void *digest)
        {
            if(!digest) return;
            blake3_hasher_finalize(&hasher, static_cast<uint8_t *>(digest), 32);
        }
    };//class Blake3

    void ComputeHash_Blake3(const void* data, uint size, void* result)
    {
        Blake3 h;
        h.Init();
        h.Update(data, size);
        h.Final(result);
    }
}
