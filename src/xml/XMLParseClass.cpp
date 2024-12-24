//取名为XMLParseClass是为了避免与expat的xmlparse.c编译造成obj冲突

#include<hgl/util/xml/XMLParse.h>
#include<hgl/io/FileInputStream.h>
#include<hgl/filesystem/FileSystem.h>
#include<expat.h>

namespace hgl
{
    namespace xml
    {
        namespace
        {        
            const char *xml_error_code[]=
            {            
                "UNKNOW_ERROR"

                "NONE",
                "NO_MEMORY",
                "SYNTAX",
                "NO_ELEMENTS",
                "INVALID_TOKEN",
                "UNCLOSED_TOKEN",
                "PARTIAL_CHAR",
                "TAG_MISMATCH",
                "DUPLICATE_ATTRIBUTE",
                "JUNK_AFTER_DOC_ELEMENT",
                "PARAM_ENTITY_REF",
                "UNDEFINED_ENTITY",
                "RECURSIVE_ENTITY_REF",
                "ASYNC_ENTITY",
                "BAD_CHAR_REF",
                "BINARY_ENTITY_REF",
                "ATTRIBUTE_EXTERNAL_ENTITY_REF",
                "MISPLACED_XML_PI",
                "UNKNOWN_ENCODING",
                "INCORRECT_ENCODING",
                "UNCLOSED_CDATA_SECTION",
                "EXTERNAL_ENTITY_HANDLING",
                "NOT_STANDALONE",
                "UNEXPECTED_STATE",
                "ENTITY_DECLARED_IN_PE",
                "FEATURE_REQUIRES_XML_DTD",
                "CANT_CHANGE_FEATURE_ONCE_PARSING",
                /* Added in 1.95.7. */
                "UNBOUND_PREFIX",
                /* Added in 1.95.8. */
                "UNDECLARING_PREFIX",
                "INCOMPLETE_PE",
                "XML_DECL",
                "TEXT_DECL",
                "PUBLICID",
                "SUSPENDED",
                "NOT_SUSPENDED",
                "ABORTED",
                "FINISHED",
                "SUSPEND_PE",
                /* Added in 2.0. */
                "RESERVED_PREFIX_XML",
                "RESERVED_PREFIX_XMLNS",
                "RESERVED_NAMESPACE_URI",
                /* Added in 2.2.1. */
                "INVALID_ARGUMENT"
            };
        }//namespace 

        const U8String GetExpatVersion()
        {
            return( U8String::numberOf(XML_MAJOR_VERSION)+
                    U8String(U8_TEXT("."))+
                    U8String::numberOf(XML_MINOR_VERSION)+
                    U8String(U8_TEXT("."))+
                    U8String::numberOf(XML_MICRO_VERSION));
        }

        const char *GetExpatError(int code)
        {
            if(code<XML_ERROR_NONE
             ||code>XML_ERROR_INVALID_ARGUMENT)
            return xml_error_code[0];

            return xml_error_code[code+1];
        }

        namespace
        {
            void XMLStartElement(ElementParse *ep,const XML_Char *name,const XML_Char **atts)
            {
                if(!ep->Init((const u8char *)name))
                    return;

                const u8char *flag;
                const u8char *info;

                while(*atts)
                {
                    flag=(u8char *)(*atts);++atts;
                    info=(u8char *)(*atts);++atts;

                    ep->Attr(flag,info);
                }

                ep->Start();
            }

            void XMLCharData(ElementParse *ep,const XML_Char *str,int len)
            {
                ep->CharData((const u8char *)str,len);
            }

            void XMLEndElement(ElementParse *ep,const XML_Char *name)
            {
                ep->End((const u8char *)name);
            }
        }//namespace

        XMLParse::XMLParse(ElementParse *ep,const int size)
        {
            element_parse=ep;
            xml=nullptr;

            if(size<=0)
                buffer_size=XML_PARSE_BUFFER_SIZE;
            else
                buffer_size=size;

            buffer=new char[buffer_size];
        }

        XMLParse::~XMLParse()
        {
            delete[] buffer;

            if(!xml)return;

            XML_ParserFree(xml);
        }

        void XMLParse::StartParse()
        {
            XML_SetElementHandler(xml,(XML_StartElementHandler)XMLStartElement,(XML_EndElementHandler)XMLEndElement);
            XML_SetCharacterDataHandler(xml,(XML_CharacterDataHandler)XMLCharData);
        }

        /**
        * 重新开始一次解晰
        */
        void XMLParse::Start(const char *charset)
        {
            if(xml)
            {
                XML_ParserReset(xml,charset);
            }
            else
            {
                xml=XML_ParserCreate(charset);

                XML_SetUserData(xml,element_parse);

                StartParse();
            }
        }

        /**
        * 解晰一段xml文本
        * @param buf 文本缓冲区
        * @param len 文本长度
        * @param isFin 是否结束
        * @return 此次解晰是否成功
        */
        bool XMLParse::Parse(const char *buf,int len,bool isFin)
        {
            if(!xml)return(false);

            return XML_Parse(xml,buf,len,isFin);
        }

        bool XMLParse::Parse(io::InputStream *is, bool isFin)
        {
            if(!is)return(false);

            if(is->CanSize()&&is->GetSize()<=buffer_size)        //可以取长度的，并且<=指定长度的一次读完
            {
                int full_size=is->Available();

                int pos=0;
                int size;

                bool result;

                while(pos<full_size)
                {
                    size=is->ReadFully(buffer,full_size);

                    if(size<0)
                        return(false);

                    result=Parse(buffer,size,pos+size>=full_size);

                    if(!result)
                        return(false);

                    pos+=size;
                }

                return(true);
            }
            else                    //不能取长度或是大于指定长度的
            {
                int size;
                bool result;

                for(;;)
                {
                    size=is->Available();

                    if(size<=0)break;

                    if(size>buffer_size)
                    {
                        size=is->Read(buffer,buffer_size);
                        result=Parse(buffer,buffer_size,false);
                    }
                    else
                    {
                        size=is->Read(buffer,size);
                        result=Parse(buffer,size,true);
                    }

                    if(!result)return(false);
                }

                return(true);
            }
        }

        void XMLParse::GetError(int *err_code,int *row,int *col)
        {
            *err_code=XML_GetErrorCode(xml);

            *row=XML_GetErrorLineNumber(xml);
            *col=XML_GetErrorColumnNumber(xml);
        }
        
        /**
         * 解晰一个XML文件
         */
        bool XMLParseFile(XMLParse *xml,const OSString &filename)
        {
            if(!xml)return(false);
            if(filename.IsEmpty())return(false);
            if(!filesystem::FileCanRead(filename))return(false);

            io::OpenFileInputStream fis(filename);

            return xml->Parse(&fis);
        }
    }//namespace xml
}//namespace hgl
