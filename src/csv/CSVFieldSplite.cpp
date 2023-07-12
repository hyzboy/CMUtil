#include<hgl/util/csv/CSVFieldSplite.h>
#include<hgl/type/StrChar.h>

namespace hgl
{
    namespace util
    {
        CSVFieldSplite::CSVFieldSplite(const char *s,const int length)
        {
            str=s;
            str_length=length;
            sp=str;
            end=str+str_length;
        }

        const char *CSVFieldSplite::next_field(int *len)
        {
            if(!len)return(nullptr);
            if(sp>=end)return(nullptr);

            if(*sp==','||*sp=='\t')
            {
                *len=0;
                ++sp;
                return sp;
            }

            const char *result;

            if(*sp=='"')
            {
                ++sp;

                const char *ep=hgl::strchr(sp,'"');

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

                const char *ep=sp+1;
            
                while(*ep!=','&&*ep!='\t'&&ep<end)
                    ++ep;

                *len=ep-sp;
                sp=ep+1;

                return result;
            }
        }
    }//namespace util
}//namespace hgl