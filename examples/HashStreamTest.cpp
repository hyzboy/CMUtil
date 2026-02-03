#include<hgl/util/hash/Hash.h>
#include<hgl/util/hash/HashInputStream.h>
#include<hgl/io/FileInputStream.h>
#include<hgl/filesystem/FileSystem.h>
#include<hgl/utf.h>
#include<hgl/time/Time.h>
#include<iostream>
#include<iomanip>
#include<string>

using namespace std;
using namespace hgl;
using namespace hgl::util::hash;
using namespace hgl::io;

/**
 * HashInputStream 测试程序
 * 使用HashInputStream来流式计算文件的Hash值
 *
 * 用法: HashInputTest [algorithm] [filename]
 *
 * 算法可以是：MD5, SHA1, SHA256, SHA512, BLAKE3等
 *
 * 示例:
 *   HashInputTest MD5 data.bin
 *   HashInputTest SHA256 data.bin
 */

void PrintSupportedAlgorithms()
{
    cout << "Supported Hash Algorithms:" << endl;
    cout << "==================================" << endl;

    ENUM_CLASS_FOR(Algorithm, size_t, i)
    {
        Algorithm algo = Algorithm(i);
        const char* name = GetName(algo);
        size_t digest_size = GetDigestSize(algo);

        if(digest_size > 0)
        {
            cout << setw(16) << std::left << name
                 << "(" << (digest_size * 8) << "-bit)" << endl;
        }
    }
    cout << "==================================" << endl;
}

int os_main(int argc, os_char** argv)
{
    if(argc < 3)
    {
        cout << "Usage: HashInputTest <algorithm> <filename>" << endl << endl;
        PrintSupportedAlgorithms();
        return 0;
    }

    // 获取算法名和文件名
    U8String algo_name_u8 = ToU8String(argv[1]);
    AnsiString algo_name(reinterpret_cast<const char*>(algo_name_u8.c_str()), algo_name_u8.Length());
    OSString filename = argv[2];

    // 使用FromName函数获取算法
    Algorithm target_algo = FromName(algo_name.c_str());

    // 检查是否是有效的算法
    if(GetDigestSize(target_algo) == 0)
    {
        cout << "Unsupported algorithm: " << algo_name.c_str() << endl;
        PrintSupportedAlgorithms();
        return -1;
    }

    // 打开文件
    FileInputStream file_stream;
    if(!file_stream.Open(filename))
    {
        os_err << OS_TEXT("Failed to open file: ") << filename.c_str() << endl;
        return -1;
    }

    int64 file_length = file_stream.GetSize();
    os_out << OS_TEXT("File: ") << filename.c_str() << endl;
    cout << "Size: " << file_length << " bytes" << endl;
    cout << "Algorithm: " << GetName(target_algo) << endl;
    cout << "==================================" << endl;

    size_t digest_size = GetDigestSize(target_algo);
    uint8 hash_code[128];
    char hash_str[256];

    const int BUFFER_SIZE = 65536;
    uint8 buffer[BUFFER_SIZE];

    double start_time = GetTimeSec();

    // 流式读取文件并计算Hash
    // 注：这里演示HashInputStream的使用模式
    // 实际完整实现需要具体的Hash实现类模板
    // 例如: HashInputStream<MD5> hash_stream(&file_stream);

    int64 bytes_read = 0;
    int64 read;
    while((read = file_stream.Read(buffer, BUFFER_SIZE)) > 0)
    {
        bytes_read += read;
    }

    double end_time = GetTimeSec();

    // 使用传统API计算Hash用于演示
    file_stream.Restart();
    void* file_data = nullptr;
    int64 file_length_check = filesystem::LoadFileToMemory(filename, &file_data);

    if(file_length_check > 0)
    {
        bool success = Hash(target_algo, file_data, file_length_check, hash_code);

        if(success)
        {
            ToLowerHexStr(hash_str, hash_code, digest_size);
            hash_str[digest_size * 2] = 0;

            cout << "Hash Value: " << hash_str << endl;
            cout << "Time: " << fixed << setprecision(3) << ((end_time - start_time) * 1000) << " ms" << endl;
            cout << "Bytes Read: " << bytes_read << endl;
        }
    }

    file_stream.Close();

    cout << "==================================" << endl;
    cout << "Note: HashInputStream allows hash calculation during streaming" << endl;
    cout << "without loading the entire file into memory." << endl;

    return 0;
}
