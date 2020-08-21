#include<hgl/util/xml/ElementParseKV.h>
#include<hgl/CodePage.h>

namespace hgl
{
    namespace xml
    {
        const ElementParseKV::AttrItem *ElementParseKV::GetAttrItem(const AnsiString &name)
        {
            const int pos=attrs_map.FindPos(name);

            if(pos<0)return(false);

            return attrs_map.GetItem(pos);
        }

        void ElementParseKV::Attr(const char *flag,const char *info)
        {
            attrs_map.Add(flag,info);
        }

        const bool ElementParseKV::Get(const AnsiString &name,AnsiString &str)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            str=ai->right;
            return(true);
        }

        const bool ElementParseKV::Get(const AnsiString &name,UTF16String &str)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            str=to_u16(ai->right);
            return(true);
        }

        const bool ElementParseKV::Get(const AnsiString &name,char &ch)
        {        
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            ch=ai->right.GetBeginChar();
            return(true);
        }

        const bool ElementParseKV::Get(const AnsiString &name,bool &value)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            return(ai?stob<char>(ai->right.c_str(),value):false);
        }
        
        const bool ElementParseKV::GetHexStr(const AnsiString &name,uint8 *data)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ParseHexStr(data,ai->right.c_str(),ai->right.Length());
            return(true);
        }
    }//namespace xml
}//namespace hgl
