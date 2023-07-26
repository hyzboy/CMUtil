#pragma once

#include<hgl/util/csv/CSVOutputStream.h>
#include<hgl/io/FileOutputStream.h>
#include<hgl/io/TextOutputStream.h>

namespace hgl
{
    namespace util
    {
        CSVOutputStream<char> *CreateCSVOutputToUTF8File(const OSString &filename,const uint field_count,const u8char fields_terminated_char,const u8char enclosed_char)
        {
            io::FileOutputStream *fos=io::CreateFileOutputStream(filename);

            if(!fos)return(nullptr);

            return CreateCSVOutputToStream<u8char>(fos,new io::UTF8TextOutputStream(fos),field_count,fields_terminated_char,enclosed_char);
        }

        CSVOutputStream<u16char> *CreateCSVOutputToUTF16LEFile(const OSString &filename,const uint field_count,const u16char fields_terminated_char,const u16char enclosed_char)
        {
            io::FileOutputStream *fos=io::CreateFileOutputStream(filename);

            if(!fos)return(nullptr);

            return CreateCSVOutputToStream<u16char>(fos,new io::UTF16LETextOutputStream(fos),field_count,fields_terminated_char,enclosed_char);
        }
    }//namespace util
}//namespace hgl
