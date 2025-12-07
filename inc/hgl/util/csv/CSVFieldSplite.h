#pragma once

#include<hgl/type/StrChar.h>

namespace hgl::util
{
    /**
    * CSV字段拆分工具<br>
    * 支持逗号分隔与tab分隔以及使用引号包裹的字符串
    */
    template<typename T> class CSVFieldSplite
    {
        const T *str;
        int str_length;

        const T *sp;
        const T *end;

    public:

        CSVFieldSplite()
        {
            str=nullptr;
            str_length=0;
            sp=nullptr;
            end=nullptr;
        }

        CSVFieldSplite(const T *s,const int length){Start(s,length);}
        ~CSVFieldSplite()=default;

        void Start(const T *s,const int length)
        {
            str=s;
            str_length=length;
            sp=str;
            end=str+str_length;
        }

        const T *next_field(int *len)
        {
            if(!len)return(nullptr);
            if(sp>=end)return(nullptr);

            if(*sp==','||*sp=='\t')
            {
                *len=0;
                ++sp;
                return sp;
            }

            const T *result;

            if(*sp=='"')
            {
                ++sp;

                const T *ep=hgl::strchr(sp,T('"'));

                if(!ep)
                    return nullptr;

                result=sp;

                *len=ep-sp;
                sp=ep+2;
                return result;
            }
            else
            {
                result=sp;

                const T *ep=sp+1;
            
                while(*ep!=','&&*ep!='\t'&&ep<end)
                    ++ep;

                *len=ep-sp;

                sp=ep+1;

                return result;
            }
        }
    };//class CSVFieldSplite
}//namespace hgl::util
