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

        class xxHash32:public HashBase<xxHash32, 4>
        {
            XXH32_state_t *state=nullptr;
            uint32 seed;

        public:

            xxHash32() = default;

            void Init()
            {
                state=XXH32_createState();
                seed=0;//mt_rand32_dist(mt_rand32);

                XXH32_reset(state,seed);
            }

            void Update(const void *input,uint inputLen)
            {
                XXH32_update(state,input,inputLen);
            }

            void Final(void *digest)
            {
                *(XXH32_hash_t *)digest=XXH32_digest(state);
            }
        };//class xxHash32

        void ComputeHash_xxHash32(const void* data, uint size, void* result)
        {
            xxHash32 h;
            h.Init();
            h.Update(data, size);
            h.Final(result);
        }

        class xxHash64:public HashBase<xxHash64, 8>
        {
            XXH64_state_t *state=nullptr;
            uint64 seed;

        public:

            xxHash64() = default;

            void Init()
            {
                state=XXH64_createState();
                seed=0;//mt_rand64_dist(mt_rand64);

                XXH64_reset(state,seed);
            }

            void Update(const void *input,uint inputLen)
            {
                XXH64_update(state,input,inputLen);
            }

            void Final(void *digest)
            {
                *(XXH64_hash_t *)digest=XXH64_digest(state);
            }
        };//class xxHash64

        void ComputeHash_xxHash64(const void* data, uint size, void* result)
        {
            xxHash64 h;
            h.Init();
            h.Update(data, size);
            h.Final(result);
        }

        class xxHash3_64:public HashBase<xxHash3_64, 8>
        {
            XXH3_state_t *state=nullptr;
            uint64 seed;

        public:

            xxHash3_64() = default;

            void Init()
            {
                state=XXH3_createState();
                seed=0;//mt_rand64_dist(mt_rand64);

                XXH3_64bits_reset_withSeed(state,seed);
            }

            void Update(const void *input,uint inputLen)
            {
                XXH3_64bits_update(state,input,inputLen);
            }

            void Final(void *digest)
            {
                *(XXH64_hash_t *)digest=XXH3_64bits_digest(state);
            }
        };//class xxHash3_64

        void ComputeHash_xxHash3_64(const void* data, uint size, void* result)
        {
            xxHash3_64 h;
            h.Init();
            h.Update(data, size);
            h.Final(result);
        }

        class xxHash3_128:public HashBase<xxHash3_128, 16>
        {
            XXH3_state_t *state=nullptr;
            XXH64_hash_t seed;

        public:

            xxHash3_128() = default;

            void Init()
            {
                state=XXH3_createState();
                seed=0;//mt_rand64_dist(mt_rand64);

                XXH3_128bits_reset_withSeed(state,seed);
            }

            void Update(const void *input,uint inputLen)
            {
                XXH3_128bits_update(state,input,inputLen);
            }

            void Final(void *digest)
            {
                *(XXH128_hash_t *)digest=XXH3_128bits_digest(state);
            }
        };//class xxHash3_128

        void ComputeHash_xxHash3_128(const void* data, uint size, void* result)
        {
            xxHash3_128 h;
            h.Init();
            h.Update(data, size);
            h.Final(result);
        }
        
    }//namespace util
}//namespace hgl
