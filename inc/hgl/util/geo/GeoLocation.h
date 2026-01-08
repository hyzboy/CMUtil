#pragma once

#include<hgl/type/String.h>
#include<hgl/time/DateTime.h>

namespace hgl::geo
{
    /**
    * 洲
    */
    enum class Continent:uint8
    {
        Africa,             ///<非洲
        Antarctica,         ///<南极洲
        Asia,               ///<亚洲
        Europe,             ///<欧洲
        NorthAmerica,       ///<北美洲
        Oceania,            ///<大洋洲
        SouthAmerica        ///<南美洲
    };

    enum class CountryID:uint16
    {
        Unknow,

        PRC,        // China
        USA,        // United States
        UK,         // United Kingdom

        CAN,        // Canada
        DEU,        // Germany
        FRA,        // France
        JPN,        // Japan
        KOR,        // South Korea
        IND,        // India
        RUS,        // Russia
        AUS,        // Australia
        NZL,        // New Zealand
        BRA,        // Brazil
        MEX,        // Mexico
        ESP,        // Spain
        ITA,        // Italy
        NLD,        // Netherlands
        SWE,        // Sweden
        NOR,        // Norway
        DNK,        // Denmark
        FIN,        // Finland
        POL,        // Poland
        CZE,        // Czechia
        AUT,        // Austria
        CHE,        // Switzerland
        BEL,        // Belgium
        PRT,        // Portugal
        TUR,        // Turkey
        GRC,        // Greece
        EGY,        // Egypt
        ZAF,        // South Africa
        NGA,        // Nigeria
        GHA,        // Ghana
        KEN,        // Kenya
        MAR,        // Morocco
        SAU,        // Saudi Arabia
        ARE,        // United Arab Emirates
        ISR,        // Israel
        IRN,        // Iran
        IRQ,        // Iraq
        PAK,        // Pakistan
        IDN,        // Indonesia
        VNM,        // Vietnam
        THA,        // Thailand
        MYS,        // Malaysia
        SGP,        // Singapore
        PHL,        // Philippines
        KHM,        // Cambodia
        LAO,        // Laos
        MMR,        // Myanmar
        NPL,        // Nepal
        BGD,        // Bangladesh
        LKA,        // Sri Lanka
        QAT,        // Qatar
        KWT,        // Kuwait
        OMN,        // Oman
        JOR,        // Jordan
        LBN,        // Lebanon
        SDN,        // Sudan
        ETH,        // Ethiopia
        DZA,        // Algeria
        TUN,        // Tunisia
        ARG,        // Argentina
        CHL,        // Chile
        COL,        // Colombia
        PER,        // Peru
        VEN,        // Venezuela
        URY,        // Uruguay
        PRY,        // Paraguay
        BOL,        // Bolivia
        ECU,        // Ecuador
        CRI,        // Costa Rica
        PAN,        // Panama
        CUB,        // Cuba
        DOM,        // Dominican Republic
        JAM,        // Jamaica
        ISL,        // Iceland
        IRL,        // Ireland
        UKR,        // Ukraine
        BLR,        // Belarus
        ROU,        // Romania
        BGR,        // Bulgaria
        HUN,        // Hungary
        SRB,        // Serbia
        HRV,        // Croatia
        SVN,        // Slovenia
        SVK,        // Slovakia
        EST,        // Estonia
        LVA,        // Latvia
        LTU,        // Lithuania
        MLT,        // Malta
        CYP,        // Cyprus
        GEO,        // Georgia
        KAZ,        // Kazakhstan
        UZB,        // Uzbekistan
        AZE,        // Azerbaijan
        ARM,        // Armenia
        MNG,        // Mongolia
        SAU_BH,     // Bahrain (legacy alias)
        BHR,        // Bahrain
        UAE_AJ,     // Ajman (emirate alias)

        ENUM_CLASS_RANGE(Unknow,UAE_AJ)
    };

    enum class CityID:uint32
    {
        Unknow,

        // China
        BeiJing,
        ShangHai,
        TianJin,
        ChongQing,

        GuangZhou,
        ShenZhen,
        ChengDu,
        HangZhou,
        NanJing,
        WuHan,
        XiAn,
        SuZhou,
        QingDao,
        JiNan,
        HeFei,
        ChangSha,
        NanChang,
        FuZhou,
        Xiamen,
        KunMing,
        GuiYang,
        LanZhou,
        Urumqi,
        HarBin,
        ChangChun,
        Shenyang,
        NingBo,
        Wuxi,

        // Added provincial capitals and famous cities
        ShiJiaZhuang,
        TaiYuan,
        HuHeHaoTe,
        ZhengZhou,
        NanNing,
        HaiKou,
        LaSa,
        XiNing,
        YinChuan,
        GuiLin,
        DaLian,
        ZhuHai,
        SanYa,
        LiJiang,

        // USA
        NewYork,
        LosAngeles,
        SanFrancisco,
        Seattle,
        Chicago,
        Boston,
        WashingtonDC,
        Houston,
        Dallas,
        Miami,
        Atlanta,
        Austin,
        SanDiego,
        Phoenix,
        Denver,
        Philadelphia,
        LasVegas,

        // UK
        London,
        Manchester,
        Birmingham,
        Edinburgh,
        Glasgow,
        Liverpool,
        Bristol,
        Cambridge,
        Oxford,

        // France
        Paris,
        Lyon,
        Marseille,
        Toulouse,
        Nice,

        // Germany
        Berlin,
        Munich,
        Hamburg,
        Frankfurt,
        Cologne,
        Stuttgart,

        // Japan
        Tokyo,
        Osaka,
        Kyoto,
        Yokohama,
        Sapporo,
        Nagoya,
        Fukuoka,

        // South Korea
        Seoul,
        Busan,
        Incheon,

        // India
        Mumbai,
        Delhi,
        Bangalore,
        Hyderabad,
        Chennai,
        Kolkata,

        // Pakistan
        Islamabad,

        // Russia
        Moscow,
        SaintPetersburg,
        Novosibirsk,

        // Australia
        Sydney,
        Melbourne,
        Brisbane,
        Perth,
        Adelaide,
        Canberra,

        // New Zealand
        Wellington,

        // Canada
        Toronto,
        Vancouver,
        Montreal,
        Ottawa,
        Calgary,

        // Brazil
        SaoPaulo,
        RioDeJaneiro,
        Brasilia,
        Salvador,

        // Mexico
        MexicoCity,
        Guadalajara,
        Monterrey,

        // Italy
        Rome,
        Milan,
        Venice,
        Florence,
        Naples,

        // Spain
        Madrid,
        Barcelona,
        Valencia,
        Seville,

        // Netherlands
        Amsterdam,
        Rotterdam,

        // Nordics
        Stockholm,
        Oslo,
        Copenhagen,
        Helsinki,
        Reykjavik,

        // Europe and nearby
        Warsaw,
        Prague,
        Vienna,
        Zurich,
        Geneva,
        Brussels,
        Lisbon,
        Porto,
        Athens,
        Budapest,
        Bucharest,
        Sofia,
        Belgrade,
        Zagreb,
        Ljubljana,
        Bratislava,
        Tallinn,
        Riga,
        Vilnius,
        Dublin,
        Kyiv,
        Minsk,
        Valletta,
        Nicosia,

        // Middle East
        Istanbul,
        Ankara,
        Riyadh,
        Jeddah,
        Dubai,
        AbuDhabi,
        Doha,
        KuwaitCity,
        Muscat,
        Amman,
        Beirut,
        TelAviv,
        Jerusalem,
        Tehran,
        Baghdad,
        Manama,
        Tbilisi,
        Astana,
        Tashkent,
        Baku,
        Yerevan,

        // Africa
        Cairo,
        Johannesburg,
        CapeTown,
        Lagos,
        Abuja,
        Nairobi,
        Casablanca,
        Rabat,
        Tunis,
        Algiers,
        AddisAbaba,
        Khartoum,
        Accra,
        Pretoria,

        // South America
        BuenosAires,
        Santiago,
        Bogota,
        Lima,
        Caracas,
        Montevideo,
        Asuncion,
        LaPaz,
        Quito,

        // SE Asia
        Jakarta,
        Surabaya,
        Denpasar,
        Hanoi,
        HoChiMinhCity,
        Bangkok,
        KualaLumpur,
        Singapore,
        Manila,
        PhnomPenh,
        Vientiane,
        Yangon,
        Kathmandu,
        Dhaka,
        Colombo,

        // Greater China
        Taipei,
        HongKong,
        Macau,

        // East Asia (Caucasus/Central Asia/Mongolia)
        Ulaanbaatar,

        ENUM_CLASS_RANGE(Unknow,Ulaanbaatar)
    };

    struct CountryInfo
    {
        CountryID   country_id;                             ///<国家ID
        Continent   continent;                              ///<所属洲
        CityID      capital_city_id;                        ///<首都城市ID

        const u16char * eng_name;                           ///<国家英文名
        const u16char * chs_name;                           ///<国家中文名
    };

    struct CityInfo
    {
                CountryID   country_id;
                Continent   continent;
                CityID      city_id;

        const   u16char *   eng_name;                       ///<城市英文名字
        const   u16char *   chs_name;                       ///<城市中文名字

                float       latitude_deg  = 0.0f;           ///< 纬度（度）
                float       longitude_deg = 0.0f;           ///< 经度（度）
                float       altitude_m    = 0.0f;           ///< 海拔（米）

                int         timezone_offset_minutes;        ///< 时区(分钟)，东一区为+60，西一区为-60
    };

    // Lookup API
    const CountryInfo *GetCountryInfo(CountryID id);
    const CityInfo *   GetCityInfo(CityID id);

    const CountryInfo *GetCountryInfoByEngName(const U16String &eng_name);
    const CountryInfo *GetCountryInfoByChsName(const U16String &chs_name);

    const CityInfo *   GetCityInfoByEngName(const U16String &eng_name);
    const CityInfo *   GetCityInfoByChsName(const U16String &chs_name);

    /**
    * 根据经纬度计算日出日落时间
    */
    const bool GetSunTime(float *sunrise,float *sunset,const float latitude,const float longitude,const CalendarDate &);
}//namespace hgl::geo
