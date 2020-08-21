#include<hgl/util/xml/ElementParseCreater.h>

namespace hgl
{
    namespace xml
    {
        bool ElementCreater::Registry(const AnsiString &name,ElementCreater *ec)
        {
            if(name.Length()<=0||!ec)return(false);
            if(ecs_map.KeyExist(name))return(false);

            ecs_map.Add(name,ec);
            return(true);
        }
            
        ElementCreater *ElementCreater::GetSubElementCreater(const AnsiString &sub_name)
        {
            if(sub_name.IsEmpty())return(nullptr);

            ElementCreater *ec;

            if(!ecs_map.Get(sub_name,ec))
                return(nullptr);

            return ec;
        }
    }//namespace xml
}//namespace hgl
