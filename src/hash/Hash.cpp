#include<hgl/util/hash/Hash.h>
#include<hgl/util/hash/SHA1LE.h>
#include<hgl/io/FileInputStream.h>
#include<map>

namespace hgl
{
    namespace util
    {
        namespace hash
        {
        // 前向声明各Hash算法的计算函数
        void ComputeHash_Adler32(const void* data, uint size, void* result);
        void ComputeHash_CRC32(const void* data, uint size, void* result);
        void ComputeHash_MD4(const void* data, uint size, void* result);
        void ComputeHash_MD5(const void* data, uint size, void* result);
        void ComputeHash_SHA1(const void* data, uint size, void* result);
        void ComputeHash_SHA256(const void* data, uint size, void* result);
        void ComputeHash_SHA512(const void* data, uint size, void* result);
        void ComputeHash_Blake3(const void* data, uint size, void* result);
        void ComputeHash_xxHash32(const void* data, uint size, void* result);
        void ComputeHash_xxHash64(const void* data, uint size, void* result);
        void ComputeHash_xxHash3_64(const void* data, uint size, void* result);
        void ComputeHash_xxHash3_128(const void* data, uint size, void* result);
        void ComputeHash_FNV1a(const void* data, uint size, void* result);
        void ComputeHash_MurmurHash3(const void* data, uint size, void* result);
        void ComputeHash_GoogleCityHash32(const void* data, uint size, void* result);
        void ComputeHash_GoogleCityHash64(const void* data, uint size, void* result);
        void ComputeHash_GoogleCityHash128(const void* data, uint size, void* result);

        // 存储各类型hash的ID
        const std::map<Algorithm, uint32> hash_ids = {
            {Algorithm::Adler32, ID::Adler32},
            {Algorithm::CRC32, ID::CRC32},
            {Algorithm::MD4, ID::MD4},
            {Algorithm::MD5, ID::MD5},
            {Algorithm::SHA1, ID::SHA1},
            {Algorithm::SHA1LE, ID::SHA1LE},
            {Algorithm::SHA256, ID::SHA256},
            {Algorithm::SHA512, ID::SHA512},
            {Algorithm::BLAKE3, ID::BLAKE3},
            {Algorithm::xxH32, ID::xxH32},
            {Algorithm::xxH64, ID::xxH64},
            {Algorithm::xxH3_64, ID::xxH3_64},
            {Algorithm::xxH3_128, ID::xxH3_128},
            {Algorithm::FNV1a, ID::FNV1a},
            {Algorithm::Murmur3, ID::Murmur3},
            {Algorithm::City32, ID::City32},
            {Algorithm::City64, ID::City64},
            {Algorithm::City128, ID::City128},
        };

        // 存储各类型hash的摘要大小
        const std::map<Algorithm, size_t> hash_sizes = {
            {Algorithm::Adler32, 4},
            {Algorithm::CRC32, 4},
            {Algorithm::MD4, 16},
            {Algorithm::MD5, 16},
            {Algorithm::SHA1, 20},
            {Algorithm::SHA1LE, 20},
            {Algorithm::SHA256, 32},
            {Algorithm::SHA512, 64},
            {Algorithm::BLAKE3, 32},
            {Algorithm::xxH32, 4},
            {Algorithm::xxH64, 8},
            {Algorithm::xxH3_64, 8},
            {Algorithm::xxH3_128, 16},
            {Algorithm::FNV1a, 8},
            {Algorithm::Murmur3, 16},
            {Algorithm::City32, 4},
            {Algorithm::City64, 8},
            {Algorithm::City128, 16},
        };

        // 存储各类型hash的名称
        const std::map<Algorithm, const char*> hash_names = {
            {Algorithm::Adler32, "Adler32"},
            {Algorithm::CRC32, "CRC32"},
            {Algorithm::MD4, "MD4"},
            {Algorithm::MD5, "MD5"},
            {Algorithm::SHA1, "SHA1"},
            {Algorithm::SHA1LE, "SHA1LE"},
            {Algorithm::SHA256, "SHA256"},
            {Algorithm::SHA512, "SHA512"},
            {Algorithm::BLAKE3, "BLAKE3"},
            {Algorithm::xxH32, "xxHash32"},
            {Algorithm::xxH64, "xxHash64"},
            {Algorithm::xxH3_64, "xxHash3-64"},
            {Algorithm::xxH3_128, "xxHash3-128"},
            {Algorithm::FNV1a, "FNV1a"},
            {Algorithm::Murmur3, "MurmurHash3"},
            {Algorithm::City32, "CityHash32"},
            {Algorithm::City64, "CityHash64"},
            {Algorithm::City128, "CityHash128"},
        };

        // 注意：在纯模板设计中，推荐用户直接创建Hash对象而不是通过工厂函数
        // 例如：
        //   MD5 md5;
        //   md5.Init();
        //   md5.Update(data, size);
        //   uint8 result[16];
        //   md5.Final(result);
        //
        // 如果需要运行时多态，可以使用虚函数包装器（见下面的ComputeHash示例）

        // 便利函数：直接计算哈希
        bool Hash(Algorithm algo, const void* data, size_t size, void* hash_code)
        {
            if(!data || size==0 || !hash_code) return false;
            if(!RangeCheck(algo)) return false;

            // 获取摘要大小
            size_t digest_size = GetDigestSize(algo);
            if(digest_size == 0) return false;

            // 使用switch调用各Hash算法的计算函数
            switch(algo)
            {
                case Algorithm::Adler32:
                    ComputeHash_Adler32(data, (uint)size, hash_code);
                    return true;
                case Algorithm::CRC32:
                    ComputeHash_CRC32(data, (uint)size, hash_code);
                    return true;
                case Algorithm::MD4:
                    ComputeHash_MD4(data, (uint)size, hash_code);
                    return true;
                case Algorithm::MD5:
                    ComputeHash_MD5(data, (uint)size, hash_code);
                    return true;
                case Algorithm::SHA1:
                    ComputeHash_SHA1(data, (uint)size, hash_code);
                    return true;
                case Algorithm::SHA1LE:
                {
                    SHA1LE h;
                    h.Init();
                    h.Update(data, (uint)size);
                    h.Final(hash_code);
                    return true;
                }
                case Algorithm::SHA256:
                    ComputeHash_SHA256(data, (uint)size, hash_code);
                    return true;
                case Algorithm::SHA512:
                    ComputeHash_SHA512(data, (uint)size, hash_code);
                    return true;
                case Algorithm::BLAKE3:
                    ComputeHash_Blake3(data, (uint)size, hash_code);
                    return true;
                case Algorithm::xxH32:
                    ComputeHash_xxHash32(data, (uint)size, hash_code);
                    return true;
                case Algorithm::xxH64:
                    ComputeHash_xxHash64(data, (uint)size, hash_code);
                    return true;
                case Algorithm::xxH3_64:
                    ComputeHash_xxHash3_64(data, (uint)size, hash_code);
                    return true;
                case Algorithm::xxH3_128:
                    ComputeHash_xxHash3_128(data, (uint)size, hash_code);
                    return true;
                case Algorithm::FNV1a:
                    ComputeHash_FNV1a(data, (uint)size, hash_code);
                    return true;
                case Algorithm::Murmur3:
                    ComputeHash_MurmurHash3(data, (uint)size, hash_code);
                    return true;
                case Algorithm::City32:
                    ComputeHash_GoogleCityHash32(data, (uint)size, hash_code);
                    return true;
                case Algorithm::City64:
                    ComputeHash_GoogleCityHash64(data, (uint)size, hash_code);
                    return true;
                case Algorithm::City128:
                    ComputeHash_GoogleCityHash128(data, (uint)size, hash_code);
                    return true;
                default:
                    return false;
            }
        }

        // 获取Hash算法的摘要大小
        size_t GetDigestSize(Algorithm algo)
        {
            if(!RangeCheck(algo)) return 0;

            auto it = hash_sizes.find(algo);
            if(it != hash_sizes.end())
                return it->second;

            return 0;
        }

        // 获取Hash算法的名称
        const char* GetName(Algorithm algo)
        {
            if(!RangeCheck(algo)) return "";

            auto it = hash_names.find(algo);
            if(it != hash_names.end())
                return it->second;

            return "";
        }

        // 获取Hash算法的ID
        uint32 GetID(Algorithm algo)
        {
            if(!RangeCheck(algo)) return 0;

            auto it = hash_ids.find(algo);
            if(it != hash_ids.end())
                return it->second;

            return 0;
        }

        // 根据Hash算法ID获取枚举值
        Algorithm FromID(uint32 id)
        {
            for(const auto& pair : hash_ids)
            {
                if(pair.second == id)
                    return pair.first;
            }
            return Algorithm::MD5; // 默认返回MD5
        }

        // 文件哈希计算
        bool HashFile(Algorithm algo, const OSString& filename, void* hash_code)
        {
            // 这需要通过运行时多态或特化模板实现
            // 为了保持纯模板设计，推荐用户使用template版本
            return false;
        }
        }//namespace hash
    }//namespace util
}//namespace hgl
