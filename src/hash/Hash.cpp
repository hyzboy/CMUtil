#include<hgl/util/hash/Hash.h>
#include<hgl/io/FileInputStream.h>

namespace hgl
{
    namespace util
    {
        namespace
        {
            struct
            {
                HASH hash;
                Hash *(*func)();
            }
            create_hash_func_list[]=
            {
                #define HASH_FUNC(name) {HASH::name,CreateHash<HASH::name>},

                HASH_FUNC(Adler32)
                HASH_FUNC(CRC32)
                HASH_FUNC(MD4)
                HASH_FUNC(MD5)
                HASH_FUNC(SHA1)
                HASH_FUNC(SHA1LE)
                HASH_FUNC(SHA256)
                HASH_FUNC(SHA512)
                HASH_FUNC(xxH32)
                HASH_FUNC(xxH64)
                HASH_FUNC(xxH3_64)
                HASH_FUNC(xxH3_128)
                HASH_FUNC(FNV1a)
                HASH_FUNC(Murmur3)
                HASH_FUNC(City32)
                HASH_FUNC(City64)
                HASH_FUNC(City128)
            };
        }//namespace

        Hash *CreateHash(const HASH ha)
        {
            RANGE_CHECK_RETURN_NULLPTR(ha)

            for(auto &hf:create_hash_func_list)
            {
                if(hf.hash==ha)
                    return hf.func();
            }

            return nullptr;
        }

        bool GetFileHash(const OSString &filename,Hash *hash,void *hash_code)
        {
            if(!hash)return(false);
            if(!hash_code)return(false);

            io::FileInputStream fp;

            if(fp.Open(filename)==false)
                return(false);

            int filesize=fp.GetSize();
            int pos=0,size;
            uint8 data[HGL_SIZE_1MB];

            hash->Init();

            while(pos<filesize)
            {
                size=HGL_SIZE_1MB;
                if(pos+size>filesize)size=filesize-pos;

                fp.Read(data,size);

                hash->Update(data,size);
                pos+=size;
            }

            hash->Final(hash_code);
            fp.Close();

            return(true);
        }
    }//namespace util
}//namespace hgl
