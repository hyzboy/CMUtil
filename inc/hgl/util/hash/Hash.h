#pragma once

#include<hgl/type/String.h>
#include<compare>
#include<hgl/type/MemoryUtil.h>
#include<memory>
#include<array>
#include<hgl/platform/Platform.h>

namespace hgl::util::hash
{
    //--------------------------------------------------------------------------------------------------
    // Hash algorithm identifiers
    //--------------------------------------------------------------------------------------------------
    namespace ID
    {
        constexpr uint32 Adler32       = HGL_MERGE32('A','d','l','r');
        constexpr uint32 CRC32         = HGL_MERGE32('C','R','C','3');
        constexpr uint32 MD4           = HGL_MERGE32('M','D','4',' ');
        constexpr uint32 MD5           = HGL_MERGE32('M','D','5',' ');
        constexpr uint32 SHA1          = HGL_MERGE32('S','H','A','1');
        constexpr uint32 SHA1LE        = HGL_MERGE32('S','H','L','E');
        constexpr uint32 SHA256        = HGL_MERGE32('S','H','2','5');
        constexpr uint32 SHA512        = HGL_MERGE32('S','H','5','1');
        constexpr uint32 BLAKE3        = HGL_MERGE32('B','L','K','3');
        constexpr uint32 XXH32         = HGL_MERGE32('X','X','H','2');
        constexpr uint32 XXH64         = HGL_MERGE32('X','X','H','6');
        constexpr uint32 XXH3_64       = HGL_MERGE32('X','3','6','4');
        constexpr uint32 XXH3_128      = HGL_MERGE32('X','3','1','2');
        constexpr uint32 FNV1a         = HGL_MERGE32('F','N','V','1');
        constexpr uint32 Murmur3       = HGL_MERGE32('M','u','r','m');
        constexpr uint32 City32        = HGL_MERGE32('C','i','3','2');
        constexpr uint32 City64        = HGL_MERGE32('C','i','6','4');
        constexpr uint32 City128       = HGL_MERGE32('C','i','1','2');
    }//namespace ID

    /**
    * Hash算法枚举
    */
    enum class Algorithm            ///Hash算法枚举
    {
        Adler32,                ///<一种较CRC32更为安全的快速HASH算法
        CRC32,                  ///<最快速的HASH算法，但最不安全，仅用于低安全性的简单验证
        MD4,                    ///<较MD5在安全性下稍弱。但仍未被攻破，且较MD5更快
        MD5,                    ///<最常用的HASH算法

        SHA1,                   ///<较MD5更为安全，但计算较慢
        SHA1LE,                 ///<SHA1改版
        SHA256,
        SHA512,

        BLAKE3,                 ///<BLAKE3 (256-bit)

        XXH32,
        XXH64,
        XXH3_64,
        XXH3_128,

        FNV1a,
        Murmur3,

        City32,
        City64,
        City128,

        ENUM_CLASS_RANGE(Adler32,City128)
    };//enum class Algorithm

    // 向后兼容别名
    using HASH = Algorithm;

    /**
    * Hash摘要结构模板
    */
    template<size_t SIZE> struct Digest
    {
        uint8 code[SIZE]{};

    public:

        template<typename T>
        using CharArray=T[(SIZE<<1)+1];

    public:

        static constexpr int size()noexcept{return SIZE;}

        const uint8 operator[](int index)const{return code[index];}

        void CopyFrom   (const void *ptr){memcpy(code,ptr,SIZE);}
        void FromString (const char *str){ParseHexStr(code,str,SIZE);}

        template<typename T> void ToUpperString(T *str,const T gap_char=0) const {ToUpperHexStr<T>(str,code,SIZE,gap_char);}
        template<typename T> void ToLowerString(T *str,const T gap_char=0) const {ToLowerHexStr<T>(str,code,SIZE,gap_char);}

        /**
         * 三路比较运算符（C++20）
         * @param other 要比较的另一个 Digest
         * @return std::strong_ordering 比较结果（less, equal, greater）
         */
        std::strong_ordering operator<=>(const Digest &other) const
        {
            return hgl::mem_compare_ordering(code, other.code, SIZE);
        }

        /**
         * 相等比较运算符
         */
        bool operator==(const Digest &other) const
        {
            return hgl::mem_compare(code, other.code, SIZE) == 0;
        }

        /**
         * 不相等比较运算符
         */
        bool operator!=(const Digest &other) const
        {
            return !(*this == other);
        }

    };//template<size_t SIZE> struct Digest

    // 向后兼容别名
    template<size_t SIZE> using HashCode = Digest<SIZE>;

    /**
     * CRTP Hash基类模板 - 纯模板设计，无虚函数
     *
     * 派生类直接继承此类，实现以下方法（无需virtual）：
     *   - void Init() - 初始化
     *   - void Update(const void* data, uint size) - 更新数据
     *   - void Final(void* result) - 最终化并获得结果
     *
     * 特点：
     *   - 0虚函数开销（编译期类型确定）
     *   - 完全内联优化
     *   - 更好的缓存局部性
     *
     * 使用示例：
     * class MD5 : public hash::Base<MD5, 16> {
     *     void Init() { ... }
     *     void Update(const void* data, uint size) { ... }
     *     void Final(void* result) { ... }
     * };
     */
    template<typename Derived, size_t HashSize>
    class Base
    {
    protected:
        Base() = default;

    public:
        static constexpr size_t DigestSize = HashSize;

        ~Base() = default;

        // 删除复制（某些派生类可能持有资源）
        Base(const Base&) = delete;
        Base& operator=(const Base&) = delete;

        // 允许移动
        Base(Base&&) = default;
        Base& operator=(Base&&) = default;

        // 公开接口 - 调用派生类的实现
        void Init()
        {
            static_cast<Derived*>(this)->Init();
        }

        void Update(const void* data, uint size)
        {
            static_cast<Derived*>(this)->Update(data, size);
        }

        void Final(void* result)
        {
            static_cast<Derived*>(this)->Final(result);
        }

        // 便利函数：计算完整哈希
        std::array<uint8, HashSize> Hash(const void* data, size_t size)
        {
            std::array<uint8, HashSize> result;
            Init();
            Update(data, size);
            Final(result.data());
            return result;
        }

    };//template<typename Derived, size_t HashSize> class Base

    // ============== 高层API - 便利函数 ==============

    /**
     * 计算数据的Hash值（编译期版本）
     *
     * 使用示例：
     * uint8 result[16];
     * if(hash::Hash<hash::Algorithm::MD5>(data, data_size, result))
     *     { ... }
     */
    template<Algorithm algo>
    bool Hash(const void* data, size_t size, void* hash_code);

    /**
     * 计算数据的Hash值（运行时版本）
     *
     * 使用示例：
     * uint8 result[16];
     * if(hash::Hash(hash::Algorithm::MD5, data, data_size, result))
     *     { ... }
     */
    bool Hash(Algorithm algo, const void* data, size_t size, void* hash_code);

    /**
     * 计算文件的Hash值
     */
    bool HashFile(Algorithm algo, const OSString& filename, void* hash_code);

    /**
     * 编译期版本 - 计算文件Hash
     */
    template<Algorithm algo>
    bool HashFile(const OSString& filename, void* hash_code)
    {
        return HashFile(algo, filename, hash_code);
    }

    /**
     * 获取Hash算法的摘要大小
     */
    size_t GetDigestSize(Algorithm algo);

    /**
     * 获取Hash算法的名称
     */
    const char* GetName(Algorithm algo);

    /**
     * 获取Hash算法的ID
     */
    uint32 GetID(Algorithm algo);

    /**
     * 根据Hash算法ID获取枚举值
     */
    Algorithm FromID(uint32 id);

    // ============ 向后兼容的旧 API 别名 ============
    inline bool ComputeHash(Algorithm ha, const void* data, size_t size, void* hash_code)
    {
        return Hash(ha, data, size, hash_code);
    }

    inline bool GetFileHash(Algorithm ha, const OSString& filename, void* hash_code)
    {
        return HashFile(ha, filename, hash_code);
    }

    inline size_t GetHashDigestSize(Algorithm ha)
    {
        return GetDigestSize(ha);
    }

    inline const char* GetHashAlgorithmName(Algorithm ha)
    {
        return GetName(ha);
    }

    inline uint32 GetHashAlgorithmID(Algorithm ha)
    {
        return GetID(ha);
    }

    inline Algorithm GetHashFromID(uint32 id)
    {
        return FromID(id);
    }
}//namespace hgl::util::hash
