#pragma once

#include<hgl/util/xml/ElementParse.h>
#include<hgl/type/String.h>
#include<hgl/type/Map.h>
namespace hgl
{
    namespace xml
    {
        /**
         * KV模式XML节点解析器
         */
        class ElementParseKV:public ElementParse
        {
        protected:

            using AttrsMap=Map<U8String,U8String>;
            using AttrItem=KeyValue<U8String,U8String>;

            AttrsMap attrs_map;

        protected:

            const AttrItem *GetAttrItem(const U8String &name);

            template<typename T> const bool GetInteger  (const U8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stoi(ai->value.c_str(),value):false);}
            template<typename T> const bool GetUInteger (const U8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stou(ai->value.c_str(),value):false);}
            template<typename T> const bool GetFloat    (const U8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stof(ai->value.c_str(),value):false);}

        public:

            virtual ~ElementParseKV()=default;

            virtual void Attr(const u8char *flag,const u8char *info) override;

        public:

            const bool      Contains     (const U8String &name)const{return attrs_map.ContainsKey(name);}

            const u8char *  ToCString   (const U8String &name){const AttrItem *ai=GetAttrItem(name);return(ai?ai->value.c_str():nullptr);}
            const u8char *  operator[]  (const U8String &name){return ToCString(name);}

        public:

            const bool      Get(const U8String &name,U8String &str);
            const bool      Get(const U8String &name,U16String &str);
            const bool      Get(const U8String &name,u8char &ch);
            const bool      Get(const U8String &name,bool &value);

            const bool      Get(const U8String &name, int8  &value){return GetInteger < int8 >(name,value);}
            const bool      Get(const U8String &name,uint8  &value){return GetUInteger<uint8 >(name,value);}
            const bool      Get(const U8String &name, int16 &value){return GetInteger < int16>(name,value);}
            const bool      Get(const U8String &name,uint16 &value){return GetUInteger<uint16>(name,value);}
            const bool      Get(const U8String &name, int32 &value){return GetInteger < int32>(name,value);}
            const bool      Get(const U8String &name,uint32 &value){return GetUInteger<uint32>(name,value);}
            const bool      Get(const U8String &name, int64 &value){return GetInteger < int64>(name,value);}
            const bool      Get(const U8String &name,uint64 &value){return GetUInteger<uint64>(name,value);}

            const bool      GetHexStr(const U8String &name,uint8 *data);
        };//class ElementParseKV:public ElementParse
    }//namespace xml
}//namespace hgl
