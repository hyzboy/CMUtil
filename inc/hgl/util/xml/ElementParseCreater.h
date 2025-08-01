﻿#ifndef HGL_UTIL_XML_ELEMENT_PARSE_CREATER_INCLUDE
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

            U8String element_name;

        protected:

            Map<U8String,ElementCreater *> ecs_map;

            virtual ElementCreater *GetSubElementCreater(const U8String &sub_name);

        public:

            const U8String &GetElementName()const{return element_name;}

        public:

            ElementCreater(const U8String &en){element_name=en;}
            virtual ~ElementCreater()=default;

            bool Register(ElementCreater *ec);

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

            U8String null_string;

            Map<U8String,U8String> attrs_list;

        public:

            ElementAttribute(const U8String &en):ElementCreater(en){}
            virtual ~ElementAttribute()=default;

            const U8String operator[](const U8String &flag)
            {
                U8String key=flag.ToLowerCase();
                U8String info;

                if(attrs_list.Get(key,info))
                    return info;
                else
                    return null_string;
            }

            #define TO_CONV(TYPE,FN,SFN,DEFAULT_VALUE)  \
            const TYPE          FN  (const U8String &flag,const TYPE default_value=DEFAULT_VALUE) \
            {   \
                const U8String key=flag.ToLowerCase();    \
            \
                U8String info;    \
            \
                if(!attrs_list.Get(key,info))   \
                    return default_value;   \
            \
                TYPE result;    \
            \
                return info.SFN(result)?result:default_value;   \
            }

            TO_CONV(uint,   ToUInteger, ToUint,     0)
            TO_CONV( int,   ToInteger,  ToInt,      0)
            TO_CONV(float,  ToFloat,    ToFloat,    0)
            TO_CONV(double, ToDouble,   ToFloat,    0)
            TO_CONV(bool,   ToBool,     ToBool,     false)

            #undef TO_CONV

            const U8String    ToString    (const U8String &flag){return operator[](flag);}
            const int           ToSerial    (const u8char **list,const U8String &flag,const int default_value)
            {
                U8String key=flag.ToLowerCase();
                U8String info;

                if(!attrs_list.Get(key,info))
                    return default_value;

                int result=find_str_in_array(list,info.c_str());

                if(result==-1)return default_value;
                return result;
            }
            
            template<typename T> const T ToEnum(const u8char **str_list,const u8char *str,const T &default_enum)
            {
                return T(this->ToSerial(str_list,str,(int)default_enum));
            }

        public:

            virtual bool Init       () override
            {
                attrs_list.Clear();
                return(true);
            }

            virtual void Attr       (const u8char *flag,const u8char *info) override///<节点属性
            {
                U8String key=flag;

                key.LowerCase();

                attrs_list.Add(key,info);
            }
        };//class ElementAttribute:public ElementCreater

        /**
         * Creater模式XML节点解析器
         */
        class ElementParseCreater:public ElementParse
        {
            Stack<ElementCreater *> ecs_stack;

            Map<U8String,ElementCreater *> ecs_map;

            ElementCreater *cur_ec;

        public:

            ElementParseCreater(ElementCreater *root_ec)
            {
                cur_ec=nullptr;

                Register(root_ec);
            }

            virtual ~ElementParseCreater()=default;

            bool Register   (ElementCreater *ec);

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
