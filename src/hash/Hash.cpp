#include<hgl/util/hash/Hash.h>
#include<hgl/util/hash/SHA1LE.h>
#include<hgl/io/FileInputStream.h>
#include<map>

namespace hgl
{
    namespace util
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

        namespace
        {
            // 存储各类型hash的大小
            const std::map<HASH, size_t> hash_sizes = {
                {HASH::Adler32, 4},
                {HASH::CRC32, 4},
                {HASH::MD4, 16},
                {HASH::MD5, 16},
                {HASH::SHA1, 20},
                {HASH::SHA1LE, 20},
                {HASH::SHA256, 32},
                {HASH::SHA512, 64},
                {HASH::BLAKE3, 32},
                {HASH::xxH32, 4},
                {HASH::xxH64, 8},
                {HASH::xxH3_64, 8},
                {HASH::xxH3_128, 16},
                {HASH::FNV1a, 8},
                {HASH::Murmur3, 16},
                {HASH::City32, 4},
                {HASH::City64, 8},
                {HASH::City128, 16},
            };
        }//namespace

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
        bool ComputeHash(const HASH ha, const void* data, size_t size, void* hash_code)
        {
            if(!data || size==0 || !hash_code) return false;
            if(!RangeCheck(ha)) return false;

            // 获取摘要大小
            size_t digest_size = GetHashDigestSize(ha);
            if(digest_size == 0) return false;

            // 使用switch调用各Hash算法的计算函数
            switch(ha)
            {
                case HASH::Adler32:
                    ComputeHash_Adler32(data, (uint)size, hash_code);
                    return true;
                case HASH::CRC32:
                    ComputeHash_CRC32(data, (uint)size, hash_code);
                    return true;
                case HASH::MD4:
                    ComputeHash_MD4(data, (uint)size, hash_code);
                    return true;
                case HASH::MD5:
                    ComputeHash_MD5(data, (uint)size, hash_code);
                    return true;
                case HASH::SHA1:
                    ComputeHash_SHA1(data, (uint)size, hash_code);
                    return true;
                case HASH::SHA1LE:
                {
                    SHA1LE h;
                    h.Init();
                    h.Update(data, (uint)size);
                    h.Final(hash_code);
                    return true;
                }
                case HASH::SHA256:
                    ComputeHash_SHA256(data, (uint)size, hash_code);
                    return true;
                case HASH::SHA512:
                    ComputeHash_SHA512(data, (uint)size, hash_code);
                    return true;
                case HASH::BLAKE3:
                    ComputeHash_Blake3(data, (uint)size, hash_code);
                    return true;
                case HASH::xxH32:
                    ComputeHash_xxHash32(data, (uint)size, hash_code);
                    return true;
                case HASH::xxH64:
                    ComputeHash_xxHash64(data, (uint)size, hash_code);
                    return true;
                case HASH::xxH3_64:
                    ComputeHash_xxHash3_64(data, (uint)size, hash_code);
                    return true;
                case HASH::xxH3_128:
                    ComputeHash_xxHash3_128(data, (uint)size, hash_code);
                    return true;
                case HASH::FNV1a:
                    ComputeHash_FNV1a(data, (uint)size, hash_code);
                    return true;
                case HASH::Murmur3:
                    ComputeHash_MurmurHash3(data, (uint)size, hash_code);
                    return true;
                case HASH::City32:
                    ComputeHash_GoogleCityHash32(data, (uint)size, hash_code);
                    return true;
                case HASH::City64:
                    ComputeHash_GoogleCityHash64(data, (uint)size, hash_code);
                    return true;
                case HASH::City128:
                    ComputeHash_GoogleCityHash128(data, (uint)size, hash_code);
                    return true;
                default:
                    return false;
            }
        }

        // 获取Hash算法的摘要大小
        size_t GetHashDigestSize(const HASH ha)
        {
            if(!RangeCheck(ha)) return 0;

            auto it = hash_sizes.find(ha);
            if(it != hash_sizes.end())
                return it->second;

            return 0;
        }

        // 文件哈希计算（需要虚函数包装或特化实现）
        bool GetFileHash(const OSString& filename, const HASH ha, void* hash_code)
        {
            // 这需要通过运行时多态或特化模板实现
            // 为了保持纯模板设计，推荐用户使用template版本
            return false;
        }
    }//namespace util
}//namespace hgl
