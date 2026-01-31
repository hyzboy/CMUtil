#include<hgl/util/hash/Hash.h>
#include<hgl/io/FileInputStream.h>
#include<map>

namespace hgl
{
    namespace util
    {
        // 前向声明所有Hash类
        class Adler32;
        class CRC32;
        class MD4;
        class MD5;
        class SHA1;
        class SHA1LE;
        class SHA256;
        class SHA512;
        class xxHash32;
        class xxHash64;
        class xxHash3_64;
        class xxHash3_128;
        class FNV1a;
        class MurmurHash3;
        class GoogleCityHash32;
        class GoogleCityHash64;
        class GoogleCityHash128;

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
                {HASH::FNV1a, 4},
                {HASH::Murmur3, 4},
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

            // 这种方式需要在.cpp中实现特化版本
            // 推荐用户使用template版本：ComputeHash<HASH::MD5>(data, size, result);
            return false;
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
