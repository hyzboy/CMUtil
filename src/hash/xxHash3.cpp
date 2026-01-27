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

            xxHash32():Hash(4,"xxH32"){}

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

        template<> Hash *CreateHash<HASH::xxH32>()
        {
            return(new xxHash32);
        }

        class xxHash64:public Hash
        {
            XXH64_state_t *state=nullptr;
            uint64 seed;

        public:

            xxHash64():Hash(8,"xxH64"){}

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

        template<> Hash *CreateHash<HASH::xxH64>()
        {
            return(new xxHash64);
        }

        class xxHash3_64:public Hash
        {
            XXH3_state_t *state=nullptr;
            uint64 seed;

        public:

            xxHash3_64():Hash(8,"xxH3_64bits"){}

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

        template<> Hash *CreateHash<HASH::xxH3_64>()
        {
            return(new xxHash3_64);
        }

        class xxHash3_128:public Hash
        {
            XXH3_state_t *state=nullptr;
            XXH64_hash_t seed;

        public:

            xxHash3_128():Hash(16,"xxH3_128bits"){}

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

        template<> Hash *CreateHash<HASH::xxH3_128>()
        {
            return(new xxHash3_128);
        }
    }//namespace util
}//namespace hgl
