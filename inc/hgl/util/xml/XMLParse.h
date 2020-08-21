#ifndef HGL_XML_PARSE_INCLUDE
#define HGL_XML_PARSE_INCLUDE

#include<hgl/type/BaseString.h>
#include<hgl/util/xml/ElementParse.h>

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

    namespace xml
    {
        constexpr int XML_PARSE_BUFFER_SIZE=HGL_SIZE_1KB*128;       ///<XML解析缓冲区大小

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

            ElementParse *element_parse;

            virtual void StartParse();

        public:

            XMLParse(ElementParse *,const int size=XML_PARSE_BUFFER_SIZE);
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
    }//namespace xml
}//namespace hgl
#endif//HGL_XML_PARSE_INCLUDE
