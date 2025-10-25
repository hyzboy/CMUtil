#pragma once

#include<hgl/type/StringList.h>

namespace hgl::util
{
    /**
    * 命令行参数解析辅助类
    */
    class CmdParse                                                          ///命令行参数解析辅助类
    {
        OSStringList args;

    public:

        CmdParse(const OSStringList &);
        CmdParse(const int,os_char **);
        virtual ~CmdParse()=default;

        int Find(const OSString &)const;                                    ///<查找一个指定字串开头的参数是否存在

        bool Contains(const OSString &flag)const{return Find(flag)!=-1;}    ///<检测是否包含某参数

        bool GetInteger(const OSString &,int *)const;                       ///<取得一个数值参数
        bool GetString(const OSString &,OSString &)const;                   ///<取得一个字符串参数
    };//class CmdParse
}//namespace hgl::util
