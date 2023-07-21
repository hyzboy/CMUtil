#pragma once

namespace hgl
{
    namespace util
    {
        /**
        * CSV字段拆分工具<br>
        * 支持逗号分隔与tab分隔以及使用引号包裹的字符串
        */
        class CSVFieldSplite
        {
            const char *str;
            int str_length;

            const char *sp;
            const char *end;

        public:

            CSVFieldSplite(const char *s,const int length);
            ~CSVFieldSplite()=default;

            const char *next_field(int *len);
        };//class CSVFieldSplite
    }//namespace util
}//namespace hgl
