#pragma once

#include<hgl/io/TextOutputStream.h>
#include<initializer_list>

namespace hgl::util
{
    /**
    * CSV输出控制
    */
    template<typename T> class CSVOutput
    {
        io::TextOutputStream *tos;

        int FieldCount;

        T FieldsTerminatedChar;
        T EnclosedChar;

        T NullStringField[2];

    protected:

        int left_count;

        void NextField()
        {
            --left_count;

            if(!left_count)
            {
                left_count=FieldCount;
                tos->WriteLineEnd();
            }
            else
                tos->WriteChars(&FieldsTerminatedChar,1);
        }

    public:

        CSVOutput(  io::TextOutputStream *os,                   //文本输出流
                    const T fields_terminated_char=T(','),      //字段分隔符
                    const T enclosed_char=T('"'))               //字符串包裹字符
        {
            tos=os;

            FieldCount          =0;

            FieldsTerminatedChar=fields_terminated_char;

            EnclosedChar        =enclosed_char;

            NullStringField[0]  =enclosed_char;
            NullStringField[1]  =enclosed_char;

            left_count         =0;
        }

        ~CSVOutput()=default;

        void WriteString(const T *str,const int len)
        {
            if(!str||!*str||len<=0)
            {
                tos->WriteChars(NullStringField,2);
            }
            else
            {
                tos->WriteChars(&EnclosedChar,1);
                tos->WriteChars(str,len);
                tos->WriteChars(&EnclosedChar,1);
            }
            NextField();
        }

        void WriteString(const String<T> &str)
        {
            WriteString(str.c_str(),str.Length());
        }

        void WriteStringList(const StringList<T> &sl)
        {
            for(const String<T> &str:sl)
                WriteString(str);
        }

        void WriteStringList(const std::initializer_list<String<T>> &sl)
        {
            for(const String<T> &str:sl)
                WriteString(str);
        }

        void WriteStringList(const std::initializer_list<const T *> &sl)
        {
            for(const T *str:sl)
                WriteString(str);
        }

        void WriteHeader(const StringList<T>                    &sl){left_count=FieldCount=sl.GetCount();   WriteStringList(sl);}
        void WriteHeader(const std::initializer_list<String<T>> &sl){left_count=FieldCount=(int)sl.size();  WriteStringList(sl);}
        void WriteHeader(const std::initializer_list<const T *> &sl){left_count=FieldCount=(int)sl.size();  WriteStringList(sl);}

        template<typename I>
        void WriteInteger(const I &value)
        {
            tos->WriteString(String<T>::numberOf(value));

            NextField();
        }

        template<typename F>
        void WriteFloat(const F &value,const uint frac)
        {
            tos->WriteString(String<T>::floatOf(value,frac));

            NextField();
        }
    };//class CSVOutput

    using UTF8CSVOutput=CSVOutput<u8char>;
    using UTF16CSVOutput=CSVOutput<u16char>;
    using UTF32CSVOutput=CSVOutput<u32char>;

    inline CSVOutput<u8char> *   CreateUTF8CSVOutput    (io::TextOutputStream *  tos,const u8char  ftc=U8_TEXT (','),const u8char     ec=U8_TEXT ('"')){return(new UTF8CSVOutput (tos,ftc,ec));}
    inline CSVOutput<u16char> *  CreateUTF16CSVOutput   (io::TextOutputStream *  tos,const u16char ftc=U16_TEXT(','),const u16char    ec=U16_TEXT('"')){return(new UTF16CSVOutput(tos,ftc,ec));}
    inline CSVOutput<u16char> *  CreateUTF32CSVOutput   (io::TextOutputStream *  tos,const u32char ftc=U32_TEXT(','),const u32char    ec=U32_TEXT('"')){return(new UTF16CSVOutput(tos,ftc,ec));}
}//namespace hgl::util
