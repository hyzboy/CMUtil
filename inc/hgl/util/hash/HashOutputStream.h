#pragma once

#include<hgl/io/OutputStream.h>
#include<hgl/util/hash/Hash.h>
#include<memory>

namespace hgl
{
    namespace io
    {
        /**
        * Hash输出流模板 - CRTP模式
        *
        * 在写入数据的同时计算Hash值
        *
        * 使用示例：
        * class SHA256Hasher : public hgl::util::hash::Base<SHA256Hasher, 32> { ... };
        * auto hash_stream = std::make_unique<HashOutputStream<SHA256Hasher>>(dest_stream);
        * hash_stream->Write(buf, size);
        * uint8 digest[32];
        * hash_stream->GetDigest(digest);
        */
        template<typename HashImpl>
        class HashOutputStream : public OutputStream
        {
        private:
            OutputStream*       dest_;          ///<目标输出流
            HashImpl             hasher_;        ///<Hash计算器
            bool                own_dest_;      ///<是否拥有目标流的所有权

        public:

            /**
            * 构造函数
            * @param dest 目标输出流指针
            * @param own_dest 是否拥有目标流的所有权（默认为false，不删除）
            */
            HashOutputStream(OutputStream* dest, bool own_dest = false)
                : dest_(dest), own_dest_(own_dest)
            {
                if(dest_)
                    hasher_.Init();
            }

            ~HashOutputStream()
            {
                if(own_dest_ && dest_)
                    delete dest_;
            }

            // 禁止拷贝
            HashOutputStream(const HashOutputStream&) = delete;
            HashOutputStream& operator=(const HashOutputStream&) = delete;

            // 允许移动
            HashOutputStream(HashOutputStream&& other) noexcept
                : dest_(other.dest_), hasher_(std::move(other.hasher_)), own_dest_(other.own_dest_)
            {
                other.dest_ = nullptr;
                other.own_dest_ = false;
            }

            HashOutputStream& operator=(HashOutputStream&& other) noexcept
            {
                if(this != &other)
                {
                    if(own_dest_ && dest_)
                        delete dest_;
                    dest_ = other.dest_;
                    hasher_ = std::move(other.hasher_);
                    own_dest_ = other.own_dest_;
                    other.dest_ = nullptr;
                    other.own_dest_ = false;
                }
                return *this;
            }

            ///<关闭输出流
            void Close() override
            {
                if(dest_)
                    dest_->Close();
            }

            /**
            * 写入数据
            * @param buf 数据缓冲区
            * @param size 要写入的字节数
            * @return 实际写入的字节数
            */
            int64 Write(const void* buf, int64 size) override
            {
                if(!dest_)
                    return 0;

                int64 write_size = dest_->Write(buf, size);
                if(write_size > 0)
                {
                    hasher_.Update(buf, write_size);
                }
                return write_size;
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
            * 复位Hash计算（继续之前的写入）
            * 仅复位Hash计算器，不影响流位置
            */
            void ResetHash()
            {
                hasher_.Init();
            }

            ///<是否可以复位
            bool CanRestart() const override
            {
                return dest_ ? dest_->CanRestart() : false;
            }

            ///<是否可以定位
            bool CanSeek() const override
            {
                return dest_ ? dest_->CanSeek() : false;
            }

            ///<是否可以取得尺寸
            bool CanSize() const override
            {
                return dest_ ? dest_->CanSize() : false;
            }

            ///<复位访问指针
            bool Restart() override
            {
                if(!dest_)
                    return false;
                bool result = dest_->Restart();
                if(result)
                    hasher_.Init();
                return result;
            }

            ///<移动访问指针
            int64 Seek(int64 pos, SeekOrigin origin = SeekOrigin::Begin) override
            {
                if(!dest_)
                    return -1;
                return dest_->Seek(pos, origin);
            }

            ///<返回当前访问位置
            int64 Tell() const override
            {
                return dest_ ? dest_->Tell() : -1;
            }

            ///<取得流长度
            int64 GetSize() const override
            {
                return dest_ ? dest_->GetSize() : -1;
            }

            ///<剩下的可以不受阻塞写入的字节数
            int64 Available() const override
            {
                return dest_ ? dest_->Available() : 0;
            }

            /**
            * 获取目标流指针
            */
            OutputStream* GetDestStream() const
            {
                return dest_;
            }

        };//template<typename HashImpl> class HashOutputStream

    }//namespace io
}//namespace hgl
