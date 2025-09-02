#pragma once
#include<nlohmann/json.hpp>
#include<hgl/type/String.h>

namespace hgl
{
    /**
     * 转换Json数据类型到普通UTF8字符串
     */
    bool JsonToString(const nlohmann::json &jv_root,U8String &str,OSString &error_info);

    /**
     * 解释一个json数据流
     */
    bool ParseJson(nlohmann::json &root,const char *str,const int size,OSString &error_info);

    bool LoadJson(nlohmann::json &,const hgl::OSString &filename,OSString &error_info);
    bool SaveJson(nlohmann::json &,const hgl::OSString &filename,OSString &error_info);
};//
