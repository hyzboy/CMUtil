#include<hgl/util/xml/ElementParseCreater.h>

namespace hgl::xml
{
    bool ElementCreater::Register(ElementCreater *ec)
    {
        if(!ec)return(false);

        const U8String &name=ec->GetElementName().ToLowerCase();

        if(name.IsEmpty())return(false);
        if(ecs_map.ContainsKey(name))return(false);

        ecs_map.Add(name,ec);
        return(true);
    }

    ElementCreater *ElementCreater::GetSubElementCreater(const U8String &sub_name)
    {
        if(sub_name.IsEmpty())return(nullptr);

        ElementCreater *ec;

        const U8String &sn=sub_name.ToLowerCase();

        if(!ecs_map.Get(sn,ec))
            return(nullptr);

        return ec;
    }
}//namespace hgl::xml
