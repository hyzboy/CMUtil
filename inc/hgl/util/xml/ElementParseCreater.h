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

            UTF8String element_name;

        protected:
        
            Map<AnsiString,ElementCreater *> ecs_map;

            virtual ElementCreater *GetSubElementCreater(const UTF8String &sub_name);

        public:

            const UTF8String &GetElementName()const{return element_name;}

        public:

            ElementCreater(const UTF8String &en){element_name=en;}
            virtual ~ElementCreater()=default;

            bool Registry(ElementCreater *ec);

        public:

            virtual bool Start      (){return true;}
            virtual void Attr       (const u8char *flag,const u8char *info){}
            virtual void CharData   (const u8char *str,const int str_length){}

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
        
            bool Start      (const u8char *element_name) override;
            void Attr       (const u8char *flag,const u8char *info) override;
            void CharData   (const u8char *str,const int str_length) override;
            void End        (const u8char *element_name) override;
        };//class ElementParseCreater:public ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
