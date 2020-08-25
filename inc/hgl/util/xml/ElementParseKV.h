#ifndef HGL_UTIL_XML_ELEMENT_PARSE_KV_INCLUDE
#define HGL_UTIL_XML_ELEMENT_PARSE_KV_INCLUDE

#include<hgl/util/xml/ElementParse.h>
#include<hgl/type/BaseString.h>
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

            using AttrsMap=Map<UTF8String,UTF8String>;
            using AttrItem=Pair<UTF8String,UTF8String>;

            AttrsMap attrs_map;

        protected:

            const AttrItem *GetAttrItem(const UTF8String &name);

            template<typename T> const bool GetInteger  (const UTF8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stoi(ai->right.c_str(),value):false);}
            template<typename T> const bool GetUInteger (const UTF8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stou(ai->right.c_str(),value):false);}
            template<typename T> const bool GetFloat    (const UTF8String &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stof(ai->right.c_str(),value):false);}        

        public:

            virtual ~ElementParseKV()=default;

            virtual void Attr(const u8char *flag,const u8char *info) override;

        public:

            const bool      IsExist     (const UTF8String &name)const{return attrs_map.KeyExist(name);}

            const u8char *  ToCString   (const UTF8String &name){const AttrItem *ai=GetAttrItem(name);return(ai?ai->right.c_str():nullptr);}
            const u8char *  operator[]  (const UTF8String &name){return ToCString(name);}

        public:

            const bool      Get(const UTF8String &name,UTF8String &str);
            const bool      Get(const UTF8String &name,UTF16String &str);
            const bool      Get(const UTF8String &name,u8char &ch);
            const bool      Get(const UTF8String &name,bool &value);

            const bool      Get(const UTF8String &name, int8  &value){return GetInteger < int8 >(name,value);}
            const bool      Get(const UTF8String &name,uint8  &value){return GetUInteger<uint8 >(name,value);}
            const bool      Get(const UTF8String &name, int16 &value){return GetInteger < int16>(name,value);}
            const bool      Get(const UTF8String &name,uint16 &value){return GetUInteger<uint16>(name,value);}
            const bool      Get(const UTF8String &name, int32 &value){return GetInteger < int32>(name,value);}
            const bool      Get(const UTF8String &name,uint32 &value){return GetUInteger<uint32>(name,value);}
            const bool      Get(const UTF8String &name, int64 &value){return GetInteger < int64>(name,value);}
            const bool      Get(const UTF8String &name,uint64 &value){return GetUInteger<uint64>(name,value);}

            const bool      GetHexStr(const UTF8String &name,uint8 *data);
        };//class ElementParseKV:public ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_KV_INCLUDE
