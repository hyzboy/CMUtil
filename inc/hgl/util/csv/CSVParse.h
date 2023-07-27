#pragma once
#include<hgl/io/FileInputStream.h>
#include<hgl/io/TextInputStream.h>
#include<hgl/util/csv/CSVFieldSplite.h>

namespace hgl
{
    namespace util
    {
        template<typename T> class CSVParseCallback
        {
        public:

            virtual bool OnLine(util::CSVFieldSplite<T> &csv)=0;
        };

        template<typename T> class CSVTextParse:public io::TextInputStream::ParseCallback<T>
        {
            util::CSVFieldSplite<T> splite;

            CSVParseCallback<T> *callback;

        public:

            CSVTextParse(CSVParseCallback<T> *pcb)
            {
                callback=pcb;
            }

            bool OnLine(const T *text,const int length) override
            {
                if(!text||!*text||length<=0)
                    return(false);

                splite.Start(text,length);

                callback->OnLine(splite);

                return(true);            
            }
        };//class CSVTextParse

        template<typename T> inline bool ParseCSV(io::InputStream *is,CSVParseCallback<T> *pcb)
        {
            io::TextInputStream tis(is);

            CSVTextParse<T> parse(pcb);

            tis.SetParseCallback<T>(&parse);

            tis.Run();

            return nullptr;
        }

        template<typename T> inline bool ParseCSVFile(const OSString &filename,CSVParseCallback<T> *pcb)
        {
            io::OpenFileInputStream fis(filename);

            if(!fis)
                return false;

            return ParseCSV<T>(fis,pcb);
        }
    }//namespace util
}//namespace hgl
