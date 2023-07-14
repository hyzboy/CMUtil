#ifndef HGL_PLIST_INCLUDE
#define HGL_PLIST_INCLUDE

#include<hgl/type/Map.h>
#include<hgl/io/LoadStringList.h>
#include<hgl/io/FileOutputStream.h>
#include<hgl/io/TextOutputStream.h>
namespace hgl
{
    using namespace io;

    /**
    * 属性列表,类似INI的管理类
    */
    template<typename C> class PList:public Map<String<C>,String<C>>                        ///属性列表
    {
    public:

        using PString=String<C>;
        using PStringList=StringList<C>;
        using PMap=Map<PString,PString>;

    protected:

        void ReadData(const PStringList &sl)
        {
            int n=sl.GetCount();

            while(n--)
                Add(sl[n]);
        }

    public:

        virtual ~PList()=default;

        virtual bool Add(const PString &key)                                                  ///<向列表中增加一项
        {
            PString name;
            C *value;
            int off;

            if(key.Length()<2)return(false);

            if(((off=key.FindChar(C('\t')))==-1)
             &&((off=key.FindChar(C(' ' )))==-1)
             &&((off=key.FindChar(C('=' )))==-1)
             &&((off=key.FindChar(C(':' )))==-1))
                return(false);

            name.Strcpy(key,off);
            off++;

            value=key.c_str()+off;

            while(true)
            {
                if(*value == C('\t')
                ||*value == C('=')
                ||*value == C(' ')
                ||*value == C(':'))
                    value++;
                else
                {
                    PString str=value;

                    PMap::Add(name,str);

                    return(true);
                }
            }
        }//bool PList::Add

        virtual bool Add(const PString &key,const PString &value)                                   ///<向列表中增加一项
        {
            return PMap::Add(key,value);
        }

        /**
         * 从文本文件中加载
         */
        virtual bool LoadFromTextFile(const OSString &filename,const CharSet &cs=OSCharSet)         ///<从文件中加载列表
        {
            PStringList sl;

            if(LoadStringListFromTextFile(sl,filename,cs)<=0)
                return(false);

            ReadData(sl);

            return(true);
        }

        /**
        * 保存到文本文件中
        */
        template<ByteOrderMask BOM>
        bool SaveToTextFile(const OSString &filename,const C &gap_ch='\t')             ///<保存列表到文件
        {
            FileOutputStream fos;
            EndianTextOutputStream<BOM> tos(&fos);

            if(!fos.CreateTrunc(filename))return(false);

            PString gap_str=PString::charOf(gap_ch);

            int n=this->data_list.GetCount();

            tos.WriteBOM();

            while(n--)
            {
                PString f,s;

                if(GetBySerial(n,f,s))
                    tos.WriteLine(f+gap_str+s);
            }

            return(true);
        }
    };//class PList

    using UTF8PList =PList<char   >;
    using UTF16PList=PList<u16char>;
    using WidePList =PList<wchar_t>;
    using OSPList   =PList<os_char>;
}//namespace hgl
#endif//HGL_PLIST_INCLUDE
