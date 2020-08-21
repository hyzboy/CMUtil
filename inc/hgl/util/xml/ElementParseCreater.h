#ifndef HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
#define HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE

#include<hgl/util/xml/ElementParse.h>
#include<hgl/type/BaseString.h>
#include<hgl/type/Stack.h>
#include<hgl/type/Map.h>
namespace hgl
{
    namespace xml
    {
        class ElementCreater
        {
            friend class ElementParseCreater;

            AnsiString element_name;

        protected:
        
            Map<AnsiString,ElementCreater *> ecs_map;

            virtual ElementCreater *GetSubElementCreater(const AnsiString &sub_name);

        public:

            const AnsiString &GetElementName()const{return element_name;}

        public:

            ElementCreater(const AnsiString &en){element_name=en;}
            virtual ~ElementCreater()=default;

            bool Registry(const AnsiString &name,ElementCreater *ec);

        public:

            virtual bool Start      (){return true;}
            virtual void Attr       (const char *flag,const char *info){}
            virtual void CharData   (const char *str,const int str_length){}

            virtual void End        (){}
        };//class ElementCreater
    
        /**
         * Creater模式XML节点解析器
         */
        class ElementParseCreater:public ElementParse
        {
            Stack<ElementCreater *> ecs_stack;

            ElementCreater *root_ec;
            ElementCreater *cur_ec;

        public:

            ElementParseCreater(ElementCreater *rec)
            {
                root_ec=rec;
                cur_ec=rec;
            }

            virtual ~ElementParseCreater()=default;

        public:
        
            bool Start      (const char *element_name) override;
            void Attr       (const char *flag,const char *info) override;
            void CharData   (const char *str,const int str_length) override;
            void End        (const char *element_name) override;
        };//class ElementParseCreater:public ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
