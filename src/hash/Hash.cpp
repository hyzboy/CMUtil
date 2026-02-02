#include<hgl/util/hash/Hash.h>
#include<hgl/util/hash/SHA1LE.h>
#include<hgl/io/FileInputStream.h>

namespace hgl::util::hash
{
    // 前向声明各Hash算法的计算函数
    void ComputeHash_Adler32(const void* data, uint size, void* result);
    void ComputeHash_CRC32(const void* data, uint size, void* result);
    void ComputeHash_MD4(const void* data, uint size, void* result);
    void ComputeHash_MD5(const void* data, uint size, void* result);
    void ComputeHash_SHA1(const void* data, uint size, void* result);
    void ComputeHash_SHA1LE(const void* data, uint size, void* result);
    void ComputeHash_SHA256(const void* data, uint size, void* result);
    void ComputeHash_SHA512(const void* data, uint size, void* result);
    void ComputeHash_Blake3(const void* data, uint size, void* result);
    void ComputeHash_XXH32(const void* data, uint size, void* result);
    void ComputeHash_XXH64(const void* data, uint size, void* result);
    void ComputeHash_XXH3_64(const void* data, uint size, void* result);
    void ComputeHash_XXH3_128(const void* data, uint size, void* result);
    void ComputeHash_FNV1a(const void* data, uint size, void* result);
    void ComputeHash_MurmurHash3(const void* data, uint size, void* result);
    void ComputeHash_GoogleCityHash32(const void* data, uint size, void* result);
    void ComputeHash_GoogleCityHash64(const void* data, uint size, void* result);
    void ComputeHash_GoogleCityHash128(const void* data, uint size, void* result);

    // Hash算法信息结构体
    struct HashAlgorithmInfo
    {
        Algorithm algo;
        uint32 id;
        size_t digest_size;
        const char* name;
        void (*compute_func)(const void* data, uint size, void* result);
    };

    // Hash算法信息数组
    constexpr HashAlgorithmInfo HASH_ALGORITHM_INFO[] = {
        {Algorithm::Adler32, ID::Adler32, 4, "Adler32", ComputeHash_Adler32},
        {Algorithm::CRC32, ID::CRC32, 4, "CRC32", ComputeHash_CRC32},
        {Algorithm::MD4, ID::MD4, 16, "MD4", ComputeHash_MD4},
        {Algorithm::MD5, ID::MD5, 16, "MD5", ComputeHash_MD5},

        {Algorithm::SHA1, ID::SHA1, 20, "SHA1", ComputeHash_SHA1},
        {Algorithm::SHA1LE, ID::SHA1LE, 20, "SHA1LE", ComputeHash_SHA1LE},
        {Algorithm::SHA256, ID::SHA256, 32, "SHA256", ComputeHash_SHA256},
        {Algorithm::SHA512, ID::SHA512, 64, "SHA512", ComputeHash_SHA512},

        {Algorithm::BLAKE3, ID::BLAKE3, 32, "BLAKE3", ComputeHash_Blake3},

        {Algorithm::XXH32, ID::XXH32, 4, "XXH32", ComputeHash_XXH32},
        {Algorithm::XXH64, ID::XXH64, 8, "XXH64", ComputeHash_XXH64},
        {Algorithm::XXH3_64, ID::XXH3_64, 8, "XXH3-64", ComputeHash_XXH3_64},
        {Algorithm::XXH3_128, ID::XXH3_128, 16, "XXH3-128", ComputeHash_XXH3_128},

        {Algorithm::FNV1a, ID::FNV1a, 8, "FNV1a", ComputeHash_FNV1a},
        {Algorithm::Murmur3, ID::Murmur3, 16, "MurmurHash3", ComputeHash_MurmurHash3},

        {Algorithm::City32, ID::City32, 4, "CityHash32", ComputeHash_GoogleCityHash32},
        {Algorithm::City64, ID::City64, 8, "CityHash64", ComputeHash_GoogleCityHash64},
        {Algorithm::City128, ID::City128, 16, "CityHash128", ComputeHash_GoogleCityHash128},
    };

    // 根据Algorithm查找对应的HashAlgorithmInfo
    const HashAlgorithmInfo* FindHashInfo(Algorithm algo)
    {
        for(const auto& info : HASH_ALGORITHM_INFO)
        {
            if(info.algo == algo)
                return &info;
        }
        return nullptr;
    }

    // 根据ID查找对应的HashAlgorithmInfo
    const HashAlgorithmInfo* FindHashInfoByID(uint32 id)
    {
        for(const auto& info : HASH_ALGORITHM_INFO)
        {
            if(info.id == id)
                return &info;
        }
        return nullptr;
    }

    // 便利函数：直接计算哈希
    bool Hash(Algorithm algo, const void* data, size_t size, void* hash_code)
    {
        if(!data || size==0 || !hash_code) return false;
        if(!RangeCheck(algo)) return false;

        const HashAlgorithmInfo* info = FindHashInfo(algo);
        if(!info || info->digest_size == 0) return false;

        // 通过函数指针调用计算函数
        if(info->compute_func)
        {
            info->compute_func(data, (uint)size, hash_code);
            return true;
        }

        return false;
    }

    // 获取Hash算法的摘要大小
    size_t GetDigestSize(Algorithm algo)
    {
        if(!RangeCheck(algo)) return 0;

        const HashAlgorithmInfo* info = FindHashInfo(algo);
        return info ? info->digest_size : 0;
    }

    // 获取Hash算法的名称
    const char* GetName(Algorithm algo)
    {
        if(!RangeCheck(algo)) return "";

        const HashAlgorithmInfo* info = FindHashInfo(algo);
        return info ? info->name : "";
    }

    // 获取Hash算法的ID
    uint32 GetID(Algorithm algo)
    {
        if(!RangeCheck(algo)) return 0;

        const HashAlgorithmInfo* info = FindHashInfo(algo);
        return info ? info->id : 0;
    }

    // 根据Hash算法ID获取枚举值
    Algorithm FromID(uint32 id)
    {
        const HashAlgorithmInfo* info = FindHashInfoByID(id);
        return info ? info->algo : Algorithm::MD5; // 默认返回MD5
    }

    // 根据Hash算法名称获取枚举值
    Algorithm FromName(const char* name)
    {
        if(!name || !*name)
            return Algorithm::MD5; // 默认返回MD5

        for(const auto& info : HASH_ALGORITHM_INFO)
        {
            if(strcmp(info.name, name) == 0)
                return info.algo;
        }

        return Algorithm::MD5; // 未找到则返回MD5
    }

    // SHA1LE计算函数
    void ComputeHash_SHA1LE(const void* data, uint size, void* result)
    {
        SHA1LE h;
        h.Init();
        h.Update(data, size);
        h.Final(result);
    }

    // 文件哈希计算
    bool HashFile(Algorithm algo, const OSString& filename, void* hash_code)
    {
        // 这需要通过运行时多态或特化模板实现
        // 为了保持纯模板设计，推荐用户使用template版本
        return false;
    }
}//namespace hgl::util::hash
