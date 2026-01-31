#include<hgl/util/xml/ElementParseKV.h>
#include<hgl/Charset.h>

namespace hgl::xml
{
    const U8String *ElementParseKV::GetAttrValue(const U8String &name)
    {
        return attrs_map.GetValuePointer(name);
    }

    void ElementParseKV::Attr(const u8char *flag,const u8char *info)
    {
        attrs_map.Add(flag,info);
    }

    const bool ElementParseKV::Get(const U8String &name,U8String &str)
    {
        const U8String *val=GetAttrValue(name);

        if(!val)return(false);

        str=*val;
        return(true);
    }

    const bool ElementParseKV::Get(const U8String &name,U16String &str)
    {
        const U8String *val=GetAttrValue(name);

        if(!val)return(false);

        str=to_u16(*val);
        return(true);
    }

    const bool ElementParseKV::Get(const U8String &name,u8char &ch)
    {
        const U8String *val=GetAttrValue(name);

        if(!val)return(false);

        ch=val->GetFirstChar();
        return(true);
    }

    const bool ElementParseKV::Get(const U8String &name,bool &value)
    {
        const U8String *val=GetAttrValue(name);

        return(val?stob<u8char>(val->c_str(),value):false);
    }

    const bool ElementParseKV::GetHexStr(const U8String &name,uint8 *data)
    {
        const U8String *val=GetAttrValue(name);

        if(!val)return(false);

        ParseHexStr(data,val->c_str(),val->Length());
        return(true);
    }
}//namespace hgl::xml
