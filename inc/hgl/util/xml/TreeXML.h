#pragma once

#include<hgl/type/UnorderedMap.h>
#include<hgl/type/String.h>
#include<hgl/type/StringView.h>
#include<hgl/type/Pair.h>

namespace hgl
{
    namespace xml
    {
        //TreeXML可以直接将整个XML解晰到一个树形结构中
        //对于访问解晰非常的友好

        //但由于要一次性保存整个树形结构，所以对内存消耗较大，且必须等到整个XML解晰完才可以访问。
        //所以TreeXML仅限于对小型XML文件的解晰，对于大型XML文件，还是使用XMLParse进行流式解晰比较好。

        struct TreeXMLData
        {
            using XSVList=ValueArray<U8StringView>;

        public:

            U8StringView xml_raw_data;          ///<XML原始数据

            XSVList ElementNameList;            ///<所有元素点名字文本视图
            XSVList AttsList;                   ///<所有属性点名字文本视图
            XSVList InfoList;                   ///<所有属性点信息文本视图
            XSVList DataList;                   ///<数据文本视图
        };

        class TreeXMLNode
        {
            /**
                <node number="123456">
                    abcdefg
                </root>

                name    root
                atts    number=123456
                data    abcdefg
            */

            TreeXMLData *   xml_raw_data;

            int             name;               ///<元素点名字视图
            Map<int,int>    atts;              ///<属性点文字视图
            int             data;              ///<数据文本视图

        private:

            TreeXMLNode(TreeXMLData *,int);

            void AddAtts(int,int);
            void SetData(int);

        public:

            const U8StringView *GetElementName()const;

            const U8StringView *GetAtts(const U8String &);
            const U8StringView *GetAtts(const U8StringView &);

            const U8StringView *GetData()const;
        };

        TreeXMLNode *ParseXMLToTree(U8StringView);
    }//namespace xml
}//namespace hgl
