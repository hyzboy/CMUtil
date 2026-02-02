#pragma once

#include<hgl/util/plist/PAttrib.h>
#include<hgl/io/FileOutputStream.h>
#include<hgl/io/TextOutputStream.h>

namespace hgl
{
    using namespace io;

    /**
     * 保存PList到文本文件中
     * @param filename 文件名
     * @param pa_map 属性列表
     * @param gap_ch 分隔符
     * @return 保存的属性数量
     */
    template<typename C,ByteOrderMask BOM> static int SaveToTextFile(const OSString &filename,const PAttribMap<C> &pa_map,const C &gap_ch=C('\t'))
    {
        FileOutputStream fos;
        EndianTextOutputStream<BOM> tos(&fos);

        if(!fos.CreateTrunc(filename))return(-1);

        tos.WriteBOM();

        int count=0;
        for(auto [key, pa_obj] : pa_map)
        {
            tos.WriteString(key);
            tos.WriteChars(&gap_ch,1);
            tos.WriteString(pa_obj->MakeToString());
            tos.WriteLineEnd();
            count++;
        }

        return(count);
    }

    /**
     * 保存PList到文本文件中（PAttribSet版本）
     * @param filename 文件名
     * @param pa_set 属性集合
     * @param gap_ch 分隔符
     * @return 保存的属性数量
     */
    template<typename C,ByteOrderMask BOM> static int SaveToTextFile(const OSString &filename,const PAttribSet<C> &pa_set,const C &gap_ch=C('\t'))
    {
        return SaveToTextFile<C,BOM>(filename, static_cast<const PAttribMap<C> &>(pa_set), gap_ch);
    }
}//namespace hgl
