#ifndef HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
#define HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE

#include<hgl/util/xml/ElementParse.h>
#include<hgl/type/String.h>
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

            virtual bool Init       (){return true;}                                ///<初始化节点
            virtual void Attr       (const u8char *flag,const u8char *info){}       ///<节点属性
            virtual bool Start      (){return true;}                                ///<开始内部数据解晰
            virtual void CharData   (const u8char *str,const int str_length){}      ///<文本数据
            virtual void End        (){}                                            ///<节点结束
        };//class ElementCreater

        class ElementAttribute:public ElementCreater
        {
        protected:

            UTF8String null_string;

            Map<UTF8String,UTF8String> attrs_list;

        public:

            ElementAttribute(const UTF8String &en):ElementCreater(en){}
            virtual ~ElementAttribute()=default;

            const UTF8String operator[](const UTF8String &flag)
            {
                UTF8String info;

                if(attrs_list.Get(flag,info))
                    return info;
                else
                    return null_string;
            }

        public:

            virtual bool Init       () override
            {
                attrs_list.ClearData();
                return(true);
            }

            virtual void Attr       (const u8char *flag,const u8char *info) override///<节点属性
            {
                attrs_list.Add(flag,info);
            }
        };//class ElementAttribute:public ElementCreater

        /**
         * Creater模式XML节点解析器
         */
        class ElementParseCreater:public ElementParse
        {
            Stack<ElementCreater *> ecs_stack;

            Map<AnsiString,ElementCreater *> ecs_map;

            ElementCreater *cur_ec;

        public:

            ElementParseCreater(ElementCreater *root_ec)
            {
                cur_ec=nullptr;

                Registry(root_ec);
            }

            virtual ~ElementParseCreater()=default;

            bool Registry   (ElementCreater *ec);

        public:

            virtual bool Init       (const u8char *element_name) override;
            virtual void Attr       (const u8char *flag,const u8char *info) override;
            virtual bool Start      () override;
            virtual void CharData   (const u8char *str,const int str_length) override;
            virtual void End        (const u8char *element_name) override;
        };//class ElementParseCreater:public ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
