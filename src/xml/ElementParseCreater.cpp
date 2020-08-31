#include<hgl/util/xml/ElementParseCreater.h>

namespace hgl
{
    namespace xml
    {
        bool ElementParseCreater::Registry(ElementCreater *ec)
        {
            if(!ec)return(false);

            return ecs_map.Add(ec->GetElementName(),ec);
        }

        bool ElementParseCreater::Start (const u8char *element_name)
        {
            if(!element_name||!*element_name)return(false);

            ElementCreater *ec=nullptr;

            if(ecs_stack.GetCount()==0)     //根
            {
                if(!ecs_map.Get(element_name,ec))
                    return(false);
            }
            else
            {
                if(!cur_ec)
                    return(false);

                ec=cur_ec->GetSubElementCreater(element_name);
                ecs_stack.Push(cur_ec);
            }

            cur_ec=nullptr;            

            if(ec)
            {
                if(ec->Start())
                    cur_ec=ec;
                else
                    delete ec;
            }

            return(cur_ec);
        }

        void ElementParseCreater::Attr(const u8char *flag,const u8char *info)
        {
            if(!cur_ec)return;

            cur_ec->Attr(flag,info);
        }

        void ElementParseCreater::CharData(const u8char *str,const int str_length)
        {
            if(!cur_ec)return;

            cur_ec->CharData(str,str_length);
        }

        void ElementParseCreater::End(const u8char *element_name)
        {
            if(cur_ec)
            {
                cur_ec->End();
                cur_ec=nullptr;
            }

            ecs_stack.Pop(cur_ec);
        }
    }//namespace xml
}//namespace hgl
