#pragma once

#include<hgl/util/csv/CSVOutput.h>

namespace hgl
{
    namespace io
    {
        class OutputStream;
        class TextOutputStream;
    }//namespace io

    namespace util
    {
        template<typename T> class CSVOutputStream
        {
            io::OutputStream *os;

            io::TextOutputStream *tos;

            CSVOutput<T> *csv;

        public:

            CSVOutputStream(io::OutputStream *_os,io::TextOutputStream *_tos,CSVOutput<T> *_csv)
            {
                os=_os;
                tos=_tos;
                csv=_csv;
            }

            ~CSVOutputStream()
            {
                delete csv;
                delete tos;
                delete os;
            }

            void WriteString(const T *str,const int len){csv->WriteString(str,len);}
            void WriteString(const String<T> &str){csv->WriteString(str);}

            void WriteStringList(const StringList<T> &sl){return csv->WriteStringList(sl);}
            void WriteStringList(const std::initializer_list<String<T>> &sl){return csv->WriteStringList(sl);}
            void WriteStringList(const std::initializer_list<const T *> &sl){return csv->WriteStringList(sl);}

            void WriteHeader(const StringList<T>                    &sl){csv->WriteHeader(sl);}
            void WriteHeader(const std::initializer_list<String<T>> &sl){csv->WriteHeader(sl);}
            void WriteHeader(const std::initializer_list<const T *> &sl){csv->WriteHeader(sl);}

            template<typename I>
            void WriteInteger(const I &value){csv->WriteInteger(value);}

            template<typename F>
            void WriteFloat(const F &value,const uint frac){csv->WriteFloat(value,frac);}
        };//template<typename T> class CSVOutputStream

        template<typename T> inline CSVOutputStream<T> *CreateCSVOutputToStream(io::OutputStream *os,io::TextOutputStream *tos,const T fields_terminated_char=T(','),const T enclosed_char=T('"'))
        {
            CSVOutput<T> *csv=new CSVOutput<T>(tos,fields_terminated_char,enclosed_char);

            return(new CSVOutputStream<T>(os,tos,csv));
        }

        CSVOutputStream<u8char> *CreateCSVOutputToUTF8File(const OSString &filename,const u8char fields_terminated_char=U8_TEXT(','),const u8char enclosed_char=U8_TEXT('"'));
        CSVOutputStream<u16char> *CreateCSVOutputToUTF16LEFile(const OSString &filename,const u16char fields_terminated_char=U16_TEXT(','),const u16char enclosed_char=U16_TEXT('"'));
    }//namespace util
}//namespace hgl
