#include<hgl/util/xml/TreeXML.h>
#include<hgl/type/Stack.h>
#include<expat.h>

namespace hgl
{
    namespace xml
    {
        TreeXMLNode::TreeXMLNode(TreeXMLData *xdata,int name)
        {
            xml_raw_data=xdata;
            element_name=name;

            data=-1;
        }

        void TreeXMLNode::AddAtts(int name,int info)
        {
            atts.Add(Pair<int,int>(name,info));
        }

        void TreeXMLNode::SetData(int d)
        {
            data=d;
        }

        const U8StringView *TreeXMLNode::GetElementName()const
        {
            if(!xml_raw_data||element_name<0)
                return nullptr;

            return xml_raw_data->ElementNameList.At(element_name);
        }

        const U8StringView *TreeXMLNode::GetAtts(const U8String &name)
        {
            if(!xml_raw_data||atts.IsEmpty()||name.IsEmpty())
                return nullptr;

            for(int i=0;i<atts.GetCount();i++)
            {
                if(xml_raw_data->AttsList[atts[i].left]==name)
                    return xml_raw_data->InfoList.At(atts[i].right);
            }
            return nullptr;
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

        TreeXMLNode *ParseXMLToTree(U8StringView sv)
        {
            if(sv.IsEmpty())
                return(nullptr);

            XMLTreeParse xtp;

            TreeXMLData *xml_data=new TreeXMLData;

            xml_data->xml_raw_data=sv;

            XML_Parser xml=XML_ParserCreate(XML_UTF8_Charset);

            XML_SetUserData(xml,(void *)&xtp);

            XML_SetElementHandler(xml,(XML_StartElementHandler)TreeXMLStartElement,(XML_EndElementHandler)TreeXMLEndElement);
            XML_SetCharacterDataHandler(xml,(XML_CharacterDataHandler)TreeXMLCharData);

            XML_Parse(xml,(char *)sv.c_str(),sv.length(),true);
        }
    }//namespace xml
}//namespace hgl
