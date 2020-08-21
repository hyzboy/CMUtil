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
            void XMLStartElement(ElementParse *ep,const XML_Char *name,const XML_Char **atts)
            {
                if(!ep->Start(name))
                    return;

                const char *flag;
                const char *info;

                while(*atts)
                {
                    flag=*atts;++atts;
                    info=*atts;++atts;
                    
                    ep->Attr(flag,info);
                }
            }

            void XMLCharData(ElementParse *ep,const XML_Char *str,int len)
            {
                ep->CharData(str,len);
            }

            void XMLEndElement(ElementParse *ep,const XML_Char *name)
            {
                ep->End(name);
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
