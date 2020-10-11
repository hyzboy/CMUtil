#pragma once
#include<json/json.h>
#include<hgl/type/String.h>

namespace hgl
{
    /**
     * 转换Json数据类型到普通UTF8字符串
     */
    bool JsonToString(const Json::Value &jv_root,UTF8String &str,OSString &error_info);

    /**
     * 解释一个json数据流
     */
    bool ParseJson(Json::Value &root,const char *str,const int size,OSString &error_info);

    bool LoadJson(Json::Value &,const hgl::OSString &filename,OSString &error_info);
    bool SaveJson(Json::Value &,const hgl::OSString &filename,OSString &error_info);
};//
