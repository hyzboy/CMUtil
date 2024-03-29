﻿#include<hgl/util/xml/ElementParseKV.h>
#include<hgl/CodePage.h>

namespace hgl
{
    namespace xml
    {
        const ElementParseKV::AttrItem *ElementParseKV::GetAttrItem(const UTF8String &name)
        {
            const int pos=attrs_map.FindPos(name);

            if(pos<0)return(false);

            return attrs_map.GetItem(pos);
        }

        void ElementParseKV::Attr(const char *flag,const char *info)
        {
            attrs_map.Add(flag,info);
        }

        const bool ElementParseKV::Get(const UTF8String &name,UTF8String &str)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            str=ai->value;
            return(true);
        }

        const bool ElementParseKV::Get(const UTF8String &name,UTF16String &str)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            str=to_u16(ai->value);
            return(true);
        }

        const bool ElementParseKV::Get(const UTF8String &name,char &ch)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ch=ai->value.GetFirstChar();
            return(true);
        }

        const bool ElementParseKV::Get(const UTF8String &name,bool &value)
        {
            const AttrItem *ai=GetAttrItem(name);

            return(ai?stob<char>(ai->value.c_str(),value):false);
        }

        const bool ElementParseKV::GetHexStr(const UTF8String &name,uint8 *data)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ParseHexStr(data,ai->value.c_str(),ai->value.Length());
            return(true);
        }
    }//namespace xml
}//namespace hgl
