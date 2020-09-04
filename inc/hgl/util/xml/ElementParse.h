#ifndef HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE
#define HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE

#include<hgl/type/DataType.h>
namespace hgl
{
    namespace xml
    {
        /**
         * XML节点解析器
         */
        class ElementParse
        {
        public:

            virtual ~ElementParse()=default;

            virtual bool Init       (const u8char *element_name)            {return(true);}
            virtual void Attr       (const u8char *flag,const u8char *info) {}
            virtual bool Start      ()                                      {return(true);}
            virtual void CharData   (const u8char *str,const int str_length){}
            virtual void End        (const u8char *element_name)            {}
        };//class ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE
