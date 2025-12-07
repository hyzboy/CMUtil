#pragma once

#include<hgl/CoreType.h>
namespace hgl   //校验/加密算法
{
    namespace io
    {
        class OutputStream;
    }//namespace io

    namespace crypt
    {
        bool OverflowEncrypt(void *target, const void *source, size_t size, const void *key, size_t key_size);
        bool OverflowDecrypt(void *target, const void *source, size_t size, const void *key, size_t key_size);

        void AesEncrypt(uint8 data[16], uint8 *key, int keysize);               ///<AES加密
        void AesDecrypt(uint8 data[16], uint8 *key, int keysize);               ///<AES解密

        void RC4Encrypt(uint8 *data, int datasize, uint8 *key, int keysize);    ///<RC4加密

        bool base64_encode(io::OutputStream *os,const uchar *input,size_t len);
        bool base64_decode(io::OutputStream *os,const uchar *input,size_t len);
    }//namespace crypt
}//namespace hgl
