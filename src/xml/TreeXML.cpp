#include<hgl/util/xml/TreeXML.h>
#include<hgl/type/Stack.h>
#include<expat.h>

namespace hgl
{
    namespace xml
    {
        TreeXML::TreeXML(char *data,int size)
        {
            xml_raw_data=data;
            xml_raw_size=size;
        }

        namespace
        {
            constexpr const char XML_UTF8_Charset[]="utf-8";

            class XMLTreeParse
            {
                TreeXML *root;

                Stack<TreeXML *> tree_stack;

                TreeXML *current;
            };

            void TreeXMLStartElement(XMLTreeParse *xtp,const XML_Char *name,const XML_Char **atts)
            {
            }

            void TreeXMLCharData(XMLTreeParse *xtp,const XML_Char *str,int len)
            {
            }

            void TreeXMLEndElement(XMLTreeParse *xtp,const XML_Char *name)
            {
            }
        }//namespace

        TreeXML *ParseXMLToTree(char *xml_raw_text,int xml_raw_size)
        {
            if(!xml_raw_text||xml_raw_size<=0)return(nullptr);

            XMLTreeParse xtp;

            TreeXML *root=new TreeXML(xml_raw_text,xml_raw_size);

            XML_Parser xml=XML_ParserCreate(XML_UTF8_Charset);

            XML_SetUserData(xml,(void *)&xtp);

            XML_SetElementHandler(xml,(XML_StartElementHandler)TreeXMLStartElement,(XML_EndElementHandler)TreeXMLEndElement);
            XML_SetCharacterDataHandler(xml,(XML_CharacterDataHandler)TreeXMLCharData);

            XML_Parse(xml,xml_raw_text,xml_raw_size,true);
        }
    }//namespace xml
}//namespace hgl
