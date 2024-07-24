#pragma once

#include<hgl/type/String.h>
#include<hgl/io/LoadStringList.h>
#include<hgl/type/Map.h>
#include<hgl/io/FileOutputStream.h>
#include<hgl/io/TextOutputStream.h>

namespace hgl
{
    using namespace io;

    template<typename C> class PAttribBase
    {
    public:

        PAttribBase()=default;
        virtual ~PAttribBase()=default;

        virtual const bool ParseFromString(const String<C> &str)=0;
        virtual String<C> MakeToString()const=0;
    };

    template<typename C,typename T> class PAttrib:public PAttribBase<C>
    {
    protected:

        String<C> name;
        T value;
        T default_value;

    public:

        PAttrib(const String<C> &n,const T &v)
        {
            name=n;
            value=v;
            default_value=v;
        }

        virtual ~PAttrib()=default;

        virtual const bool ParseFromString(const String<C> &str)=0;
        virtual String<C> MakeToString()const=0;

        virtual const T &Get(){return value;}
        virtual void Set(const T &v){value=v;}
    };//template<typename C,typename T> class PAttrib

    template<typename C,typename T> class PNumberAttrib:public PAttrib<C,T>
    {
    protected:

        T min_value,max_value;

    public:

        PNumberAttrib(const String<C> &n,const T &dv,const T &min_v,const T &max_v):PAttrib<C,T>(n,dv)
        {
            min_value=min_v;
            max_value=max_v;
        }

        virtual ~PNumberAttrib()=default;

        const bool ParseFromString(const String<C> &str) override
        {
            if(ToNumber(str,this->value))
            {
                if(this->value>=min_value&&this->value<=max_value)
                    return(true);
            }

            this->value=this->default_value;
            return(false);
        }

        String<C> MakeToString() const override
        {
            return String<C>::numberOf(this->value);
        }
    };//class PNumberAttrib:public PAttrib<C,uint>

    template<typename C> using PIntAttrib   =PNumberAttrib<C,int    >;
    template<typename C> using PUintAttrib  =PNumberAttrib<C,uint   >;

    template<typename C,typename T> class PFloatNumberAttrib:public PAttrib<C,T>
    {
    protected:

        T min_value,max_value;

        uint frac;

    public:

        PFloatNumberAttrib(const String<C> &n,const T &dv,const T &min_v,const T &max_v,const int f):PAttrib<C,T>(n,dv)
        {
            min_value=min_v;
            max_value=max_v;

            frac=f;
        }

        virtual ~PFloatNumberAttrib()=default;

        const bool ParseFromString(const String<C> &str) override
        {
            if(ToNumber(str,this->value))
            {
                if(this->value>=min_value&&this->value<=max_value)
                    return(true);
            }

            this->value=this->default_value;
            return(false);
        }

        void SetFrac(uint f){frac=f;}

        String<C> MakeToString() const override
        {
            return String<C>::floatOf(this->value,frac);
        }
    };//class PFloatNumberAttrib:public PAttrib<C,uint>

    template<typename C> using PFloatAttrib =PFloatNumberAttrib<C,float  >;
    template<typename C> using PDoubleAttrib=PFloatNumberAttrib<C,double >;

    template<typename C> class PBoolAttrib:public PAttrib<C,bool>
    {
    public:

        using PAttrib<C,bool>::PAttrib;

        const bool ParseFromString(const String<C> &str)
        {
            if(str.ToBool(this->value))
                return(true);

            this->value=this->default_value;
            return(false);
        }

        String<C> MakeToString() const override
        {
            return(this->value?"true":"false");
        }
    };

    template<typename C> class PStringAttrib:public PAttrib<C,String<C>>
    {
    public:

        using PAttrib<C,String<C>>::PAttrib;

        const bool ParseFromString(const String<C> &str) override
        {
            this->value=str;
            return(true);
        }

        String<C> MakeToString() const override
        {
            return this->value;
        }
    };

    template<typename C> using PAttribMap=Map<String<C>,PAttribBase<C> *>;

    /**
     * 向属性列表中写入一个属性
     */
    template<typename C> static bool Add(PAttribMap<C> &pa_map,const String<C> &str)
    {
        String<C> name;
        C *value;
        int off;

        if(str.Length()<2)return(false);

        if(((off=str.FindChar(C('\t')))==-1)
         &&((off=str.FindChar(C(' '))) ==-1)
         &&((off=str.FindChar(C('='))) ==-1)
         &&((off=str.FindChar(C(':'))) ==-1))
            return(false);

        name.Strcpy(str,off);
        off++;

        value=str.c_str()+off;

        while(true)
        {
            if(*value == C('\t')
             ||*value == C('=')
             ||*value == C(' ')
             ||*value == C(':'))
            {
                value++;
                continue;
            }

            break;
        }

        PAttribBase<C> *attr=GetObjectFromList(pa_map,name);

        if(attr)
            attr->ParseFromString(value);

        return(true);
    }

    template<typename C> class PAttribSet
    {
        using PString=String<C>;
        using PStringList=StringList<PString>;

        PAttribMap<C> pa_map;

    public:

        operator        PAttribMap<C> &()       {return pa_map;}
        operator const  PAttribMap<C> &()const  {return pa_map;}

    public:

        template<typename T>
        PNumberAttrib<C,T> *CreateNumberAttrib(const PString &name,const T &dv,const T &min_v,const T &max_v)
        {
            PNumberAttrib<C,T> *obj=new PNumberAttrib<C,T>(name,dv,min_v,max_v);

            pa_map.Add(name,obj);

            return obj;
        }

        /**
        * 创建一个浮点数属性
        * @param name 属性名称
        * @param dv 默认值
        * @param min_v 最小值
        * @param max_v 最大值
        * @param frac 小数点后位数
        * @return 属性对象
        */
        template<typename T>
        PFloatNumberAttrib<C,T> *CreateFloatAttrib(const PString &name,const T &dv,const T &min_v,const T &max_v,const int frac)
        {
            PFloatNumberAttrib<C,T> *obj=new PFloatNumberAttrib<C,T>(name,dv,min_v,max_v,frac);

            pa_map.Add(name,obj);

            return obj;
        }

        PBoolAttrib<C> *CreateBoolAttrib(const PString &name,const bool &dv)
        {
            PBoolAttrib<C> *obj=new PBoolAttrib<C>(name,dv);

            pa_map.Add(name,obj);

            return obj;
        }

        PStringAttrib<C> *CreateStringAttrib(const PString &name,const PString &dv)
        {
            PStringAttrib<C> *obj=new PStringAttrib<C>(name,dv);

            pa_map.Add(name,obj);

            return obj;
        }

    public:

        bool Add(const PString &name,PAttribBase<C> *attr)
        {
            return pa_map.Add(name,attr);
        }

        //bool Add(const PString &str)
        //{
        //    return Add(pa_name,str);
        //}

        PAttribBase<C> *Get(const PString &name){return GetObjectFromList(pa_map,name);}

        void Delete(const PString &name){pa_map.DeleteByKey(name);}

        void Clear(){pa_map.Clear();}
        void ClearData(){pa_map.ClearData();}

        void Enum(void (*enum_func)(const String<C> &key,PAttribBase<C> * &value))
        {
            pa_map.Enum(enum_func);
        };
    };//template<typename C> class PAttribSet

    using UTF8PAttribSet    =PAttribSet<u8char>;
    using UTF16PAttribSet   =PAttribSet<u16char>;
    using WidePAttribSet    =PAttribSet<wchar_t>;
    using OSPAttribSet      =PAttribSet<os_char>;
}//namespace hgl
