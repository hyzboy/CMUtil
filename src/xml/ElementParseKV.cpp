#include<hgl/util/xml/ElementParseKV.h>
#include<hgl/Charset.h>

namespace hgl
{
    namespace xml
    {
        const ElementParseKV::AttrItem *ElementParseKV::GetAttrItem(const U8String &name)
        {
            const int pos=attrs_map.FindPos(name);

            if(pos<0)return(nullptr);

            return attrs_map.GetItem(pos);
        }

        void ElementParseKV::Attr(const u8char *flag,const u8char *info)
        {
            attrs_map.Add(flag,info);
        }

        const bool ElementParseKV::Get(const U8String &name,U8String &str)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            str=ai->value;
            return(true);
        }

        const bool ElementParseKV::Get(const U8String &name,U16String &str)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            str=to_u16(ai->value);
            return(true);
        }

        const bool ElementParseKV::Get(const U8String &name,u8char &ch)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ch=ai->value.GetFirstChar();
            return(true);
        }

        const bool ElementParseKV::Get(const U8String &name,bool &value)
        {
            const AttrItem *ai=GetAttrItem(name);

            return(ai?stob<u8char>(ai->value.c_str(),value):false);
        }

        const bool ElementParseKV::GetHexStr(const U8String &name,uint8 *data)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ParseHexStr(data,ai->value.c_str(),ai->value.Length());
            return(true);
        }
    }//namespace xml
}//namespace hgl
