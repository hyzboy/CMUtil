#include<hgl/util/hash/Hash.h>
#include<hgl/filesystem/FileSystem.h>
#include<hgl/time/Time.h>
#include<iostream>
#include<iomanip>

using namespace std;
using namespace hgl;
using namespace hgl::util;

int os_main(int argc,os_char **argv)
{
    if(argc<2)
    {
        cout<<"CountHash [filename]"<<endl;
        return(0);
    }

    os_out<<OS_TEXT("CountHash \"")<<argv[1]<<OS_TEXT('\"')<<endl;

    void *file_data;
    int64 file_length;

    file_length=filesystem::LoadFileToMemory(argv[1],&file_data);

    cout<<"file length: "<<file_length<<endl;

    size_t hash_length;
    uint8 hash_code[128];  // Max hash size supported
    char hash_str[256];

    double start_time,end_time;

    ENUM_CLASS_FOR(HASH,size_t,i)
    {
        HASH current_hash = HASH(i);
        hash_length = util::GetHashDigestSize(current_hash);

        if(hash_length == 0 || hash_length > sizeof(hash_code))
            continue;

        start_time=GetTimeSec();

        bool success = util::ComputeHash(current_hash, file_data, file_length, hash_code);

        end_time=GetTimeSec();

        if(!success)
            continue;

        ToLowerHexStr(hash_str, hash_code, hash_length);

        hash_str[hash_length*2]=0;

        // Get hash algorithm name from enum
        const char* hash_name = "";
        switch(current_hash)
        {
            case HASH::Adler32:  hash_name = "Adler32"; break;
            case HASH::CRC32:    hash_name = "CRC32"; break;
            case HASH::MD4:      hash_name = "MD4"; break;
            case HASH::MD5:      hash_name = "MD5"; break;
            case HASH::SHA1:     hash_name = "SHA1"; break;
            case HASH::SHA1LE:   hash_name = "SHA1LE"; break;
            case HASH::SHA256:   hash_name = "SHA256"; break;
            case HASH::SHA512:   hash_name = "SHA512"; break;
            case HASH::BLAKE3:   hash_name = "BLAKE3"; break;
            case HASH::xxH32:    hash_name = "xxH32"; break;
            case HASH::xxH64:    hash_name = "xxH64"; break;
            case HASH::xxH3_64:  hash_name = "xxH3_64"; break;
            case HASH::xxH3_128: hash_name = "xxH3_128"; break;
            case HASH::FNV1a:    hash_name = "FNV1a"; break;
            case HASH::Murmur3:  hash_name = "Murmur3"; break;
            case HASH::City32:   hash_name = "City32"; break;
            case HASH::City64:   hash_name = "City64"; break;
            case HASH::City128:  hash_name = "City128"; break;
        }

        cout<<setw(16)<<std::right<<hash_name<<"["<<setw(16)<<std::left<<(end_time-start_time)<<"] "<<hash_str<<endl;
    }
}
