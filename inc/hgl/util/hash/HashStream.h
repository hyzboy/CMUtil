#pragma once

#include<hgl/io/HashInputStream.h>
#include<hgl/io/HashOutputStream.h>
#include<hgl/util/hash/Hash.h>
#include<memory>

namespace hgl
{
    namespace io
    {
        /**
        * Hash流便利工厂类
        *
        * 提供简单的方式创建Hash包装流
        */
        namespace hash_stream
        {
            /**
            * 创建Hash输入流
            *
            * 示例：
            * auto hash_input = hgl::io::hash_stream::make_hash_input<MyHasher>(source_stream);
            */
            template<typename HashImpl>
            inline std::unique_ptr<HashInputStream<HashImpl>> make_hash_input(
                InputStream* source,
                bool own_source = false)
            {
                return std::make_unique<HashInputStream<HashImpl>>(source, own_source);
            }

            /**
            * 创建Hash输出流
            *
            * 示例：
            * auto hash_output = hgl::io::hash_stream::make_hash_output<MyHasher>(dest_stream);
            */
            template<typename HashImpl>
            inline std::unique_ptr<HashOutputStream<HashImpl>> make_hash_output(
                OutputStream* dest,
                bool own_dest = false)
            {
                return std::make_unique<HashOutputStream<HashImpl>>(dest, own_dest);
            }

        }//namespace hash_stream

        /**
        * Hash流工具类 - 简化API
        *
        * 提供对Hash流的统一操作接口
        *
        * 示例：
        * HashStreamTools<MD5Hasher> tools;
        * tools.ProcessInputStream(source_stream, [](const uint8* digest){
        *     // 处理摘要
        * });
        */
        template<typename HashImpl>
        class HashStreamTools
        {
        public:
            using DigestType = std::array<uint8, HashImpl::DigestSize>;

            /**
            * 处理输入流并计算Hash
            * @param source 源输入流
            * @param callback Hash完成后的回调函数，接收摘要指针
            * @param buffer_size 临时缓冲区大小（用于Copy）
            * @return 处理的字节数，-1表示失败
            */
            static int64 ProcessInputStream(
                InputStream* source,
                std::function<void(const uint8*)> callback = nullptr,
                size_t buffer_size = 65536)
            {
                if(!source)
                    return -1;

                HashInputStream<HashImpl> hash_stream(source, false);

                std::unique_ptr<uint8[]> buf(new uint8[buffer_size]);
                int64 total = 0;
                int64 read_size;

                while((read_size = hash_stream.Read(buf.get(), buffer_size)) > 0)
                {
                    total += read_size;
                }

                if(callback)
                {
                    uint8 digest[HashImpl::DigestSize];
                    hash_stream.GetDigest(digest);
                    callback(digest);
                }

                return total;
            }

            /**
            * 处理输出流并计算Hash
            * @param dest 目标输出流
            * @param data 要写入的数据
            * @param size 数据大小
            * @param callback Hash完成后的回调函数，接收摘要指针
            * @return 实际写入的字节数，-1表示失败
            */
            static int64 ProcessOutputStream(
                OutputStream* dest,
                const void* data,
                size_t size,
                std::function<void(const uint8*)> callback = nullptr)
            {
                if(!dest || !data)
                    return -1;

                HashOutputStream<HashImpl> hash_stream(dest, false);
                int64 written = hash_stream.Write(data, size);

                if(callback && written > 0)
                {
                    uint8 digest[HashImpl::DigestSize];
                    hash_stream.GetDigest(digest);
                    callback(digest);
                }

                return written;
            }

            /**
            * 获取摘要为十六进制字符串
            * @param digest Hash摘要
            * @return 十六进制字符串（小写）
            */
            static std::string DigestToHexString(const uint8* digest, bool uppercase = false)
            {
                std::string result;
                result.reserve(HashImpl::DigestSize * 2);

                for(size_t i = 0; i < HashImpl::DigestSize; ++i)
                {
                    uint8 byte = digest[i];
                    const char* hex_chars = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
                    result += hex_chars[(byte >> 4) & 0x0F];
                    result += hex_chars[byte & 0x0F];
                }

                return result;
            }

        };//template<typename HashImpl> class HashStreamTools

    }//namespace io
}//namespace hgl
