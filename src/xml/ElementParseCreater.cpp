#include<hgl/util/xml/ElementParseCreater.h>

namespace hgl
{
    namespace xml
    {
        bool ElementParseCreater::Start (const char *element_name)
        {
            if(!element_name||!*element_name)return(false);

            if(!cur_ec)
                return(false);

            ElementCreater *ec=cur_ec->GetSubElementCreater(element_name);

            ecs_stack.Push(cur_ec);
            
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

        void ElementParseCreater::Attr(const char *flag,const char *info)
        {
            if(!cur_ec)return;

            cur_ec->Attr(flag,info);
        }

        void ElementParseCreater::CharData(const char *str,const int str_length)
        {
            if(!cur_ec)return;

            cur_ec->CharData(str,str_length);
        }

        void ElementParseCreater::End(const char *element_name)
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
