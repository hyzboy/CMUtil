#pragma once

#include<hgl/type/List.h>
#include<hgl/type/StringView.h>
namespace hgl
{
    namespace xml
    {
        //TreeXML可以直接将整个XML解晰到一个树形结构中
        //对于访问解晰非常的友好

        //但由于要一次性保存整个树形结构，所以对内存消耗较大，且必须等到整个XML解晰完才可以访问。
        //所以TreeXML仅限于对小型XML文件的解晰，对于大型XML文件，还是使用XMLParse进行流式解晰比较好。

        class TreeXML
        {
            char *xml_raw_data;                 ///<整体XML原始数据
            int xml_raw_size;                   ///<整体XML原始数据长度

        protected:

            using XSVList=List<U8StringView>;

        protected:

            XSVList ElementNameList;            ///<所有元素点名字文本视图
            XSVList AttsList;                   ///<所有属性点名字文本视图
            XSVList InfoList;                   ///<所有属性点信息文本视图
            XSVList DataList;                   ///<数据文本视图

        public:

            class Node
            {
                U8StringView element_name;      ///<元素点名字视图
                U8StringView atts;              ///<属性点文字视图
            };

        public:

            TreeXML(char *,int);
        };//class TreeXML

        TreeXML *ParseXMLToTree(char *,int);
    }//namespace xml
}//namespace hgl
