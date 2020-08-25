#include<hgl/util/xml/ElementParseCreater.h>

namespace hgl
{
    namespace xml
    {
        bool ElementCreater::Registry(ElementCreater *ec)
        {
            if(!ec)return(false);

            const UTF8String &name=ec->GetElementName();

            if(name.IsEmpty())return(false);
            if(ecs_map.KeyExist(name))return(false);

            ecs_map.Add(name,ec);
            return(true);
        }
            
        ElementCreater *ElementCreater::GetSubElementCreater(const UTF8String &sub_name)
        {
            if(sub_name.IsEmpty())return(nullptr);

            ElementCreater *ec;

            if(!ecs_map.Get(sub_name,ec))
                return(nullptr);

            return ec;
        }
    }//namespace xml
}//namespace hgl
