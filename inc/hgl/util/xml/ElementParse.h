#ifndef HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE
#define HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE

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

            virtual bool Start      (const char *element_name)              {return(true);}
            virtual void Attr       (const char *flag,const char *info)     {}
            virtual void CharData   (const char *str,const int str_length)  {}
            virtual void End        (const char *element_name)              {}
        };//class ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_INCLUDE
