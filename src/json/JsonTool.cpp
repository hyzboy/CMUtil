#include<string>
#include<sstream>
#include<json/json.h>
#include<hgl/filesystem/FileSystem.h>
#include<hgl/type/StdString.h>

using namespace hgl::filesystem;
using namespace std;

namespace hgl
{
    const U8String GetJsoncppVersion()
    {
        return U8String((const u8char *)JSONCPP_VERSION_STRING);
    }

    bool JsonToString(const Json::Value &jv_root,U8String &str,OSString &error_info)
    {
        Json::StreamWriterBuilder builder;
        Json::StreamWriter *writer=builder.newStreamWriter();

        JSONCPP_OSTRINGSTREAM json_result;

        bool result;

        try
        {
            writer->write(jv_root,&json_result);
            result=true;

            str=ToU8String(json_result.str());
        }
        catch(std::exception &e)
        {
            error_info=OS_TEXT("[C++ Exception][Json::StreamWriter::write] ")+ToOSString(e.what());
            result=false;
        }

        delete writer;
        return result;
    }

    bool ParseJson(Json::Value &root,const char *txt,const int size,OSString &error_str)
    {
        Json::CharReaderBuilder builder;
        Json::CharReader *reader=builder.newCharReader();

        JSONCPP_STRING errs;

        const bool result=reader->parse(txt,txt+size,&root,&errs);

        delete reader;

        error_str=ToOSString(errs);

        return result;
    }

    bool LoadJson(Json::Value &root,const OSString &filename,OSString &error_info)
    {
        char *txt;
        int size;

        size=LoadFileToMemory(filename,(void **)&txt);

        if(size<=0)
        {
            error_info=OS_TEXT("[ERROR][LoadJson] Load file failed, filename: ")+filename;
            return(false);
        }

        bool result;

        result=ParseJson(root,txt,size,error_info);
        delete[] txt;

        return(result);
    }

    bool SaveJson(Json::Value &root,const OSString &filename,OSString &error_info)
    {
        U8String txt;

        if(!JsonToString(root,txt,error_info))
            return(false);

        const int64 result=SaveMemoryToFile(filename,txt.c_str(),txt.Length());

        if(result!=txt.Length())
        {
            error_info=OS_TEXT("[ERROR][SaveJson] Save file failed, only write ")+OSString::numberOf(result)+OS_TEXT("/")+OSString::numberOf(txt.Length());
            return(false);
        }

        return(true);
    }
}//namespace hgl
