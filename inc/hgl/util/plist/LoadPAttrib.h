#pragma once

#include<hgl/util/plist/PAttrib.h>
#include<hgl/io/LoadStringList.h>

namespace hgl
{
    using namespace io;

    /**
     * 从文本文件中加载PList
     * @param filename 文件名
     * @param pa_map 属性列表
     * @return 是否加载成功
     */
    template<typename C> static int LoadFromTextFile(const OSString &filename,PAttribMap<C> &pa_map)
    {
        StringList<C> sl;

        if(LoadStringListFromTextFile(sl,filename)<=0)
            return(false);

        int n=sl.GetCount();

        while(n--)
            Add(pa_map,sl[n]);

        return(true);
    }

    /**
     * 从文本文件中加载PList（PAttribSet版本）
     * @param filename 文件名
     * @param pa_set 属性集合
     * @return 是否加载成功
     */
    template<typename C> static int LoadFromTextFile(const OSString &filename,PAttribSet<C> &pa_set)
    {
        return LoadFromTextFile<C>(filename, static_cast<PAttribMap<C> &>(pa_set));
    }
}//namespace hgl
