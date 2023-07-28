﻿#pragma once

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
    template<typename C,ByteOrderMask BOM> static int SaveToTextFile(const OSString &filename,const PAttribMap<C> &pa_map,const String<C> &gap_ch=String<C>("\t"))
    {
        FileOutputStream fos;
        EndianTextOutputStream<BOM> tos(&fos);

        if(!fos.CreateTrunc(filename))return(-1);

        tos.WriteBOM();

        const int count=pa_map.GetCount();
        auto **pa_obj=pa_map.GetDataList();

        for(int i=0;i<count;i++)
        {
            tos.WriteString((*pa_obj)->key);
            tos.WriteString(gap_ch);
            tos.WriteString((*pa_obj)->value->MakeToString());
            tos.WriteLineEnd();

            ++pa_obj;
        }

        return(count);
    }
}//namespace hgl
