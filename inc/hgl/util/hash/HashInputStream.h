#pragma once

#include<hgl/io/InputStream.h>
#include<hgl/util/hash/Hash.h>
#include<memory>

namespace hgl
{
    namespace io
    {
        /**
        * Hash输入流模板 - CRTP模式
        *
        * 在读取数据的同时计算Hash值
        *
        * 使用示例：
        * class MD5Hasher : public hgl::util::hash::Base<MD5Hasher, 16> { ... };
        * auto hash_stream = std::make_unique<HashInputStream<MD5Hasher>>(source_stream);
        * hash_stream->Read(buf, size);
        * MD5Hasher::Digest digest;
        * hash_stream->GetDigest(digest.code);
        */
        template<typename HashImpl>
        class HashInputStream : public InputStream
        {
        private:
            InputStream*        source_;        ///<源输入流
            HashImpl             hasher_;        ///<Hash计算器
            bool                own_source_;    ///<是否拥有源流的所有权

        public:

            /**
            * 构造函数
            * @param source 源输入流指针
            * @param own_source 是否拥有源流的所有权（默认为false，不删除）
            */
            HashInputStream(InputStream* source, bool own_source = false)
                : source_(source), own_source_(own_source)
            {
                if(source_)
                    hasher_.Init();
            }

            ~HashInputStream()
            {
                if(own_source_ && source_)
                    delete source_;
            }

            // 禁止拷贝
            HashInputStream(const HashInputStream&) = delete;
            HashInputStream& operator=(const HashInputStream&) = delete;

            // 允许移动
            HashInputStream(HashInputStream&& other) noexcept
                : source_(other.source_), hasher_(std::move(other.hasher_)), own_source_(other.own_source_)
            {
                other.source_ = nullptr;
                other.own_source_ = false;
            }

            HashInputStream& operator=(HashInputStream&& other) noexcept
            {
                if(this != &other)
                {
                    if(own_source_ && source_)
                        delete source_;
                    source_ = other.source_;
                    hasher_ = std::move(other.hasher_);
                    own_source_ = other.own_source_;
                    other.source_ = nullptr;
                    other.own_source_ = false;
                }
                return *this;
            }

            ///<关闭输入流
            void Close() override
            {
                if(source_)
                    source_->Close();
            }

            /**
            * 读取数据
            * @param buf 数据缓冲区
            * @param size 要读取的字节数
            * @return 实际读取的字节数
            */
            int64 Read(void* buf, int64 size) override
            {
                if(!source_)
                    return 0;

                int64 read_size = source_->Read(buf, size);
                if(read_size > 0)
                {
                    hasher_.Update(buf, read_size);
                }
                return read_size;
            }

            /**
            * 预览数据（不更新Hash）
            * @param buf 数据缓冲区
            * @param size 要预览的字节数
            * @return 实际预览的字节数
            */
            int64 Peek(void* buf, int64 size) override
            {
                if(!source_)
                    return 0;
                return source_->Peek(buf, size);
            }

            /**
            * 获取当前Hash摘要（不结束流）
            * @param digest_buf Hash摘要缓冲区，大小应为HashImpl::DigestSize
            */
            void GetDigest(void* digest_buf) const
            {
                // 创建临时Hasher副本并获取结果
                HashImpl temp_hasher = hasher_;
                temp_hasher.Final(digest_buf);
            }

            /**
            * 获取Hash摘要大小
            */
            static constexpr size_t GetDigestSize()
            {
                return HashImpl::DigestSize;
            }

            /**
            * 复位Hash计算（继续之前的读取）
            * 仅复位Hash计算器，不影响流位置
            */
            void ResetHash()
            {
                hasher_.Init();
            }

            ///<是否可以复位
            bool CanRestart() const override
            {
                return source_ ? source_->CanRestart() : false;
            }

            ///<是否可以定位
            bool CanSeek() const override
            {
                return source_ ? source_->CanSeek() : false;
            }

            ///<是否可以取得尺寸
            bool CanSize() const override
            {
                return source_ ? source_->CanSize() : false;
            }

            ///<是否可以预览数据
            bool CanPeek() const override
            {
                return source_ ? source_->CanPeek() : false;
            }

            ///<复位访问指针
            bool Restart() override
            {
                if(!source_)
                    return false;
                bool result = source_->Restart();
                if(result)
                    hasher_.Init();
                return result;
            }

            ///<跳过指定字节
            int64 Skip(int64 bytes) override
            {
                if(!source_)
                    return 0;

                // 创建临时缓冲区用于跳过时的Hash计算
                const int64 SKIP_BUF_SIZE = 65536;
                uint8 skip_buf[SKIP_BUF_SIZE];
                int64 skipped = 0;

                while(bytes > 0)
                {
                    int64 to_read = (bytes > SKIP_BUF_SIZE) ? SKIP_BUF_SIZE : bytes;
                    int64 read_size = Read(skip_buf, to_read);
                    if(read_size <= 0)
                        break;
                    skipped += read_size;
                    bytes -= read_size;
                }

                return skipped;
            }

            ///<移动访问指针
            int64 Seek(int64 pos, SeekOrigin origin = SeekOrigin::Begin) override
            {
                if(!source_)
                    return -1;
                return source_->Seek(pos, origin);
            }

            ///<返回当前访问位置
            int64 Tell() const override
            {
                return source_ ? source_->Tell() : -1;
            }

            ///<取得流长度
            int64 GetSize() const override
            {
                return source_ ? source_->GetSize() : -1;
            }

            ///<剩下的可以不受阻塞访问的字节数
            int64 Available() const override
            {
                return source_ ? source_->Available() : 0;
            }

            /**
            * 获取源流指针
            */
            InputStream* GetSourceStream() const
            {
                return source_;
            }

        };//template<typename HashImpl> class HashInputStream

    }//namespace io
}//namespace hgl
