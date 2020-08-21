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

            using AttrsMap=Map<AnsiString,AnsiString>;
            using AttrItem=Pair<AnsiString,AnsiString>;

            AttrsMap attrs_map;

        protected:

            const AttrItem *GetAttrItem(const AnsiString &name);

            template<typename T> const bool GetInteger  (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stoi(ai->right.c_str(),value):false);}
            template<typename T> const bool GetUInteger (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stou(ai->right.c_str(),value):false);}
            template<typename T> const bool GetFloat    (const AnsiString &name,T &value){const AttrItem *ai=GetAttrItem(name);return(ai?stof(ai->right.c_str(),value):false);}        

        public:

            virtual ~ElementParseKV()=default;

            virtual void Attr(const char *flag,const char *info) override;

        public:

            const bool      IsExist     (const AnsiString &name)const{return attrs_map.KeyExist(name);}

            const char *    ToCString   (const AnsiString &name){const AttrItem *ai=GetAttrItem(name);return(ai?ai->right.c_str():nullptr);}
            const char *    operator[]  (const AnsiString &name){return ToCString(name);}

        public:

            const bool      Get(const AnsiString &name,AnsiString &str);
            const bool      Get(const AnsiString &name,UTF16String &str);
            const bool      Get(const AnsiString &name,char &ch);
            const bool      Get(const AnsiString &name,bool &value);

            const bool      Get(const AnsiString &name, int8  &value){return GetInteger < int8 >(name,value);}
            const bool      Get(const AnsiString &name,uint8  &value){return GetUInteger<uint8 >(name,value);}
            const bool      Get(const AnsiString &name, int16 &value){return GetInteger < int16>(name,value);}
            const bool      Get(const AnsiString &name,uint16 &value){return GetUInteger<uint16>(name,value);}
            const bool      Get(const AnsiString &name, int32 &value){return GetInteger < int32>(name,value);}
            const bool      Get(const AnsiString &name,uint32 &value){return GetUInteger<uint32>(name,value);}
            const bool      Get(const AnsiString &name, int64 &value){return GetInteger < int64>(name,value);}
            const bool      Get(const AnsiString &name,uint64 &value){return GetUInteger<uint64>(name,value);}

            const bool      GetHexStr(const AnsiString &name,uint8 *data);
        };//class ElementParseKV:public ElementParse
    }//namespace xml
}//namespace hgl
#endif//HGL_UTIL_XML_ELEMENT_PARSE_KV_INCLUDE
