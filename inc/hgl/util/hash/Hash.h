#pragma once

#include<hgl/type/String.h>
#include<compare>
#include<hgl/type/MemoryUtil.h>
#include<memory>
#include<array>

namespace hgl
{
    namespace util
    {
        /**
        * Hash算法枚举
        */
        enum class HASH             ///Hash算法枚举
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

            xxH32,
            xxH64,
            xxH3_64,
            xxH3_128,

            FNV1a,
            Murmur3,
            City32,
            City64,
            City128,

            ENUM_CLASS_RANGE(Adler32,City128)
        };//enum HASH

        /**
        * Hash编码结构模板
        */
        template<size_t SIZE> struct HashCode
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
             * @param other 要比较的另一个 HashCode
             * @return std::strong_ordering 比较结果（less, equal, greater）
             *
             * 用法示例：
             * HashCode<16> hash1, hash2;
             * if(hash1 <=> hash2 < 0) { ... }  // hash1 < hash2
             * if((hash1 <=> hash2) == 0) { ... }  // hash1 == hash2
             */
            std::strong_ordering operator<=>(const HashCode &other) const
            {
                return hgl::mem_compare_ordering(code, other.code, SIZE);
            }

            /**
             * 相等比较运算符
             * @param other 要比较的另一个 HashCode
             * @return 如果两个哈希码完全相同返回 true，否则返回 false
             *
             * 用法示例：
             * HashCode<16> hash1, hash2;
             * if(hash1 == hash2) { ... }
             */
            bool operator==(const HashCode &other) const
            {
                return hgl::mem_compare(code, other.code, SIZE) == 0;
            }

            /**
             * 不相等比较运算符
             * @param other 要比较的另一个 HashCode
             * @return 如果两个哈希码不完全相同返回 true，否则返回 false
             *
             * 用法示例：
             * HashCode<16> hash1, hash2;
             * if(hash1 != hash2) { ... }
             */
            bool operator!=(const HashCode &other) const
            {
                return !(*this == other);
            }

        };//template<size_t SIZE> struct HashCode

        /**
         * CRTP Hash基类模板 - 纯模板设计，无虚函数
         * 
         * 派生类直接继承此类，实现以下方法（无需virtual）：
         *   - void Init() - 初始化
         *   - void Update(const void* data, uint size) - 更新数据
         *   - void Final(void* result) - 最终化并获得结果
         *   - 可选：static constexpr size_t DigestSize - 摘要大小
         *   - 可选：static constexpr std::string_view AlgorithmName - 算法名称
         * 
         * 特点：
         *   - 0虚函数开销（编译期类型确定）
         *   - 完全内联优化
         *   - 更好的缓存局部性
         * 
         * 使用示例：
         * template<> class MD5 : public HashBase<MD5, 16> {
         *     void Init() { ... }
         *     void Update(const void* data, uint size) { ... }
         *     void Final(void* result) { ... }
         * };
         */
        template<typename Derived, size_t HashSize>
        class HashBase
        {
        protected:
            HashBase() = default;

        public:
            static constexpr size_t DigestSize = HashSize;

            ~HashBase() = default;

            // 删除复制（某些派生类可能持有资源）
            HashBase(const HashBase&) = delete;
            HashBase& operator=(const HashBase&) = delete;

            // 允许移动
            HashBase(HashBase&&) = default;
            HashBase& operator=(HashBase&&) = default;

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
            template<size_t N>
            std::array<uint8, HashSize> Hash(const void* data, size_t size)
            {
                std::array<uint8, HashSize> result;
                Init();
                Update(data, size);
                Final(result.data());
                return result;
            }

        };//template<typename Derived, size_t HashSize> class HashBase

        // ============== 现代API - 直接创建Hash实例 ==============

        /**
         * 在纯模板设计中，推荐直接创建Hash对象而不是通过工厂函数
         * 
         * 使用示例：
         * MD5 md5;
         * md5.Init();
         * md5.Update(data, size);
         * uint8 result[16];
         * md5.Final(result);
         * 
         * 对于需要运行时多态的场景，使用下面的ComputeHash模板函数
         */

        // ============== 高层API - 便利函数 ==============

        /**
         * 计算数据的Hash值（一步到位）- 模板版本（推荐）
         * 
         * 使用示例：
         * uint8 result[16];
         * if(ComputeHash<HASH::MD5>(data, data_size, result))
         *     { ... }
         * 
         * @param data 数据指针
         * @param size 数据长度
         * @param hash_code 输出：哈希值存放处
         * @return 是否成功
         */
        template<HASH ha>
        bool ComputeHash(const void* data, size_t size, void* hash_code);

        /**
         * 计算数据的Hash值（运行时版本）
         * 
         * 使用示例：
         * uint8 result[16];
         * if(ComputeHash(HASH::MD5, data, data_size, result))
         *     { ... }
         * 
         * @param ha 哈希算法
         * @param data 数据指针
         * @param size 数据长度
         * @param hash_code 输出：哈希值存放处
         * @return 是否成功
         */
        bool ComputeHash(const HASH ha, const void* data, size_t size, void* hash_code);

        /**
         * 获取Hash算法的摘要大小
         * 
         * 使用示例：
         * uint8 result[16];
         * if(ComputeHash<HASH::MD5>(data, data_size, result))
         *     { ... }
         */
        template<HASH ha>
        bool ComputeHash(const void* data, size_t size, void* hash_code)
        {
            auto hash = CreateHashPtr<ha>();
            if (!hash) return false;

            // 使用void*来调用，需要通过虚函数表
            // 这里的实现在.cpp中处理
            return ComputeHash(ha, data, size, hash_code);
        }

        /**
         * 计算文件的Hash值
         * 
         * @param filename 文件名
         * @param ha 哈希算法
         * @param hash_code 输出：哈希值
         * @return 是否成功
         */
        bool GetFileHash(const OSString& filename, const HASH ha, void* hash_code);

        /**
         * 模板版 - 计算文件Hash
         */
        template<HASH ha>
        bool GetFileHash(const OSString& filename, void* hash_code)
        {
            return GetFileHash(filename, ha, hash_code);
        }

        /**
         * 获取Hash算法的摘要大小
         */
        size_t GetHashDigestSize(const HASH ha);

    }//namespace util
}//namespace hgl
