#include<hgl/util/hash/Hash.h>
#include<hgl/filesystem/FileSystem.h>
#include<hgl/time/Time.h>
#include<iostream>
#include<iomanip>

using namespace std;
using namespace hgl;
using namespace hgl::util::hash;

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

    ENUM_CLASS_FOR(Algorithm,size_t,i)
    {
        Algorithm current_algo = Algorithm(i);
        hash_length = GetDigestSize(current_algo);

        if(hash_length == 0 || hash_length > sizeof(hash_code))
            continue;

        start_time=GetTimeSec();

        bool success = Hash(current_algo, file_data, file_length, hash_code);

        end_time=GetTimeSec();

        if(!success)
            continue;

        ToLowerHexStr(hash_str, hash_code, hash_length);

        hash_str[hash_length*2]=0;

        const char* hash_name = GetName(current_algo);

        cout<<setw(16)<<std::right<<hash_name<<"["<<setw(16)<<std::left<<(end_time-start_time)<<"] "<<hash_str<<endl;
    }
}
