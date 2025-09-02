#include<string>
#include<nlohmann/json.hpp>
#include<hgl/filesystem/FileSystem.h>
#include<hgl/type/StdString.h>

using namespace hgl::filesystem;
using namespace std;

namespace hgl
{
    bool JsonToString(const nlohmann::json &jv_root,U8String &str,OSString &error_info)
    {
        try
        {
            std::string json_result = jv_root.dump();
            str = ToU8String(json_result);
            return true;
        }
        catch(std::exception &e)
        {
            error_info=OS_TEXT("[C++ Exception][nlohmann::json::dump] ")+ToOSString(e.what());
            return false;
        }
    }

    bool ParseJson(nlohmann::json &root,const char *txt,const int size,OSString &error_str)
    {
        try
        {
            root = nlohmann::json::parse(txt, txt + size);
            return true;
        }
        catch(nlohmann::json::parse_error &e)
        {
            error_str = ToOSString(e.what());
            return false;
        }
        catch(std::exception &e)
        {
            error_str = ToOSString(e.what());
            return false;
        }
    }

    bool LoadJson(nlohmann::json &root,const OSString &filename,OSString &error_info)
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

    bool SaveJson(nlohmann::json &root,const OSString &filename,OSString &error_info)
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
