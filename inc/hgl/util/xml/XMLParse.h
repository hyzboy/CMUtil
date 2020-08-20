#ifndef HGL_XML_PARSE_INCLUDE
#define HGL_XML_PARSE_INCLUDE

#include<hgl/type/BaseString.h>
#include<hgl/type/Map.h>
#include<hgl/type/StrChar.h>
#include<hgl/CodePage.h>

extern "C"
{
    /**
    * 该XML解晰器使用Expat实现,根据MIT协议取得免费授权,授权协议参见 doc/license/MIT.txt
    * Expat官方网站：http://expat.sourceforge.net/
    */

    struct XML_ParserStruct;

    using XML_Parser=struct XML_ParserStruct *;
}

namespace hgl
{
    namespace io
    {
        class InputStream;
    }//namespace io

    /**
     * XML节点解析器
     */
    class XMLElementParse
    {
    public:

        virtual bool StartElement(const char *element_name)=0;
        virtual void Attr(const char *flag,const char *info){};
        virtual void CharData(const char *str,int str_length){};
        virtual void EndElement(const char *element_name){};
    };//class XMLElementParse

    class XMLElementParseKV:public XMLElementParse
    {
    protected:

        using AttrsMap=Map<AnsiString,AnsiString>;
        using AttrItem=Pair<AnsiString,AnsiString>;

        AttrsMap attrs_map;

    protected:

        const AttrItem *GetAttrItem(const AnsiString &name);

        template<typename T> const bool GetInteger  (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stoi(ai->right.c_str(),value):false);}
        template<typename T> const bool GetUInteger (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stou(ai->right.c_str(),value):false);}
        template<typename T> const bool GetFloat    (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stof(ai->right.c_str(),value):false);}        

    public:

        virtual void Attr(const char *flag,const char *info) override;

    public:

        const bool      IsExist     (const AnsiString &name)const{return attrs_map.KeyExist(name);}

        const char *    ToCString   (const AnsiString &name){const AttrItem *ai=GetAttrItem(name);return(ai?ai->right.c_str():nullptr);}
        const char *    operator[]  (const AnsiString &name){return ToCString(name);}

    public:

        const bool      Get(const AnsiString &name,AnsiString &str)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            str=ai->right;
            return(true);
        }

        const bool      Get(const AnsiString &name,UTF16String &str)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            str=to_u16(ai->right);
            return(true);
        }

        const bool      Get(const AnsiString &name,char &ch)
        {        
            const AttrItem *ai=GetAttrItem(name);
            
            if(!ai)return(false);
            
            ch=ai->right.GetBeginChar();
            return(true);
        }

        const bool      Get(const AnsiString &name,bool   &value)
        {
            const AttrItem *ai=GetAttrItem(name);
            
            return(ai?stob<char>(ai->right.c_str(),value):false);
        }

        const bool      Get(const AnsiString &name, int8  &value){return GetInteger < int8 >(name,value);}
        const bool      Get(const AnsiString &name,uint8  &value){return GetUInteger<uint8 >(name,value);}
        const bool      Get(const AnsiString &name, int16 &value){return GetInteger < int16>(name,value);}
        const bool      Get(const AnsiString &name,uint16 &value){return GetUInteger<uint16>(name,value);}
        const bool      Get(const AnsiString &name, int32 &value){return GetInteger < int32>(name,value);}
        const bool      Get(const AnsiString &name,uint32 &value){return GetUInteger<uint32>(name,value);}
        const bool      Get(const AnsiString &name, int64 &value){return GetInteger < int64>(name,value);}
        const bool      Get(const AnsiString &name,uint64 &value){return GetUInteger<uint64>(name,value);}

        const bool      GetHexStr(const AnsiString &name,uint8 *data)
        {
            const AttrItem *ai=GetAttrItem(name);

            if(!ai)return(false);

            ParseHexStr(data,ai->right.c_str(),ai->right.Length());
            return(true);
        }
    };//class XMLElementParseKV:public XMLElementParse

    /**
    * XML解析器<br>
    */
    class XMLParse
    {
    protected:

        XML_Parser xml;

        int buffer_size;
        char *buffer;

    protected:

        XMLElementParse *element_parse;

        virtual void StartParse();

    public:

        XMLParse(XMLElementParse *,const int size=HGL_SIZE_1KB*128);
        virtual ~XMLParse();

        virtual void Start(const char *charset="utf-8");
        virtual bool Parse(const char *buf,int len,bool isFin);
        virtual bool Parse(io::InputStream *,bool isFin=true);
    };//class XMLParse

    bool XMLParseFile(XMLParse *xml,const OSString &filename);

#define XML_START_PARSE(name)   while(*name)    \
                                {   \
                                    const char *flag=*name;++name;  \
                                    const char *info=*name;++name;

#define XML_END_PARSE()             LOG_ERROR(UTF8String(__FILE__)+U8_TEXT(":")+UTF8String(__LINE__)+U8_TEXT(" can't parse atts \"")+UTF8String(flag)+U8_TEXT("\" , info \"")+UTF8String(info)+U8_TEXT("\".")); \
                                }
#define XML_END_PARSE_SKIP()    ;}

#define xml_parse_skip(name)        if(hgl::strcmp(flag,#name)==0)continue;else
#define xml_parse_string_u16(name)  if(hgl::strcmp(flag,#name)==0)name=to_u16(info);else
#define xml_parse_string_u8(name)   if(hgl::strcmp(flag,#name)==0)name=info;else
#define xml_parse_int(name)         if(hgl::strcmp(flag,#name)==0)hgl::stoi(info,name);else
#define xml_parse_uint(name)        if(hgl::strcmp(flag,#name)==0)hgl::stou(info,name);else
#define xml_parse_float(name)       if(hgl::strcmp(flag,#name)==0)hgl::stof(info,name);else
#define xml_parse_bool(name)        if(hgl::strcmp(flag,#name)==0)hgl::stob(info,name);else
#define xml_parse_hexstr(name)      if(hgl::strcmp(flag,#name)==0)hgl::ParseHexStr(name,info);else

#define xml_parse_to_string_u8(name,value)   if(hgl::strcmp(flag,name)==0)value=info;else
#define xml_parse_to_int(name,value)         if(hgl::strcmp(flag,name)==0)hgl::stoi(info,value);else
#define xml_parse_to_uint(name,value)        if(hgl::strcmp(flag,name)==0)hgl::stou(info,value);else
#define xml_parse_to_float(name,value)       if(hgl::strcmp(flag,name)==0)hgl::stof(info,value);else
#define xml_parse_to_bool(name,value)        if(hgl::strcmp(flag,name)==0)hgl::stob(info,value);else

/** 使用范例:

    <root>
        <role name="Bill" sex="true" age="18"/>
        <role name="Lucy" sex="false" age="17"/>
    </root>

    void StartElement(const char *element_name,const char **atts) override
    {
        if(strcmp(element_name,"role")==0)
        {
            std::string name;
            bool sex;
            int age;

            XML_START_PARSE(atts)

                xml_parse_string_u8(name)
                xml_parse_bool(sex)
                xml_parse_int(age)

            XML_END_PARSE
        }
    }
*/
}//namespace hgl
#endif//HGL_XML_PARSE_INCLUDE
