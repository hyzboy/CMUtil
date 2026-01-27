#include <hgl/util/geo/GeoLocation.h>
#include <cmath>

namespace hgl::geo
{
    namespace
    {
        // 以下所有数据均来自于Github Copilot自动生成，仅供参考。若有错误，概不负责，请自行修正。

        static const CountryInfo kCountries[] =
        {
#define GEO_COUNTRY_INFO(country,continent,capital,eng_name,chs_name) { CountryID::country, Continent::continent, CityID::capital, U16_TEXT(eng_name), U16_TEXT(chs_name) }

            GEO_COUNTRY_INFO(PRC,       Asia,         BeiJing,        "China",                   "中国"                ),
            GEO_COUNTRY_INFO(USA,       NorthAmerica, WashingtonDC,   "United States",           "美国"                ),
            GEO_COUNTRY_INFO(UK,        Europe,       London,         "United Kingdom",          "英国"                ),

            GEO_COUNTRY_INFO(CAN,       NorthAmerica, Ottawa,         "Canada",                  "加拿大"              ),
            GEO_COUNTRY_INFO(DEU,       Europe,       Berlin,         "Germany",                 "德国"                ),
            GEO_COUNTRY_INFO(FRA,       Europe,       Paris,          "France",                  "法国"                ),
            GEO_COUNTRY_INFO(JPN,       Asia,         Tokyo,          "Japan",                   "日本"                ),
            GEO_COUNTRY_INFO(KOR,       Asia,         Seoul,          "South Korea",             "韩国"                ),
            GEO_COUNTRY_INFO(IND,       Asia,         Delhi,          "India",                   "印度"                ),
            GEO_COUNTRY_INFO(RUS,       Europe,       Moscow,         "Russia",                  "俄罗斯"              ),
            GEO_COUNTRY_INFO(AUS,       Oceania,      Canberra,       "Australia",               "澳大利亚"            ),
            GEO_COUNTRY_INFO(NZL,       Oceania,      Wellington,     "New Zealand",             "新西兰"              ),
            GEO_COUNTRY_INFO(BRA,       SouthAmerica, Brasilia,       "Brazil",                  "巴西"                ),
            GEO_COUNTRY_INFO(MEX,       NorthAmerica, MexicoCity,     "Mexico",                  "墨西哥"              ),
            GEO_COUNTRY_INFO(ESP,       Europe,       Madrid,         "Spain",                   "西班牙"              ),
            GEO_COUNTRY_INFO(ITA,       Europe,       Rome,           "Italy",                   "意大利"              ),
            GEO_COUNTRY_INFO(NLD,       Europe,       Unknow,         "Netherlands",             "荷兰"                ),
            GEO_COUNTRY_INFO(SWE,       Europe,       Unknow,         "Sweden",                  "瑞典"                ),
            GEO_COUNTRY_INFO(NOR,       Europe,       Unknow,         "Norway",                  "挪威"                ),
            GEO_COUNTRY_INFO(DNK,       Europe,       Unknow,         "Denmark",                 "丹麦"                ),
            GEO_COUNTRY_INFO(FIN,       Europe,       Unknow,         "Finland",                 "芬兰"                ),
            GEO_COUNTRY_INFO(POL,       Europe,       Unknow,         "Poland",                  "波兰"                ),
            GEO_COUNTRY_INFO(CZE,       Europe,       Unknow,         "Czechia",                 "捷克"                ),
            GEO_COUNTRY_INFO(AUT,       Europe,       Unknow,         "Austria",                 "奥地利"              ),
            GEO_COUNTRY_INFO(CHE,       Europe,       Unknow,         "Switzerland",             "瑞士"                ),
            GEO_COUNTRY_INFO(BEL,       Europe,       Unknow,         "Belgium",                 "比利时"              ),
            GEO_COUNTRY_INFO(PRT,       Europe,       Unknow,         "Portugal",                "葡萄牙"              ),
            GEO_COUNTRY_INFO(TUR,       Asia,         Ankara,         "Turkey",                  "土耳其"              ),
            GEO_COUNTRY_INFO(GRC,       Europe,       Athens,         "Greece",                  "希腊"                ),
            GEO_COUNTRY_INFO(EGY,       Africa,       Cairo,          "Egypt",                   "埃及"                ),
            GEO_COUNTRY_INFO(ZAF,       Africa,       CapeTown,       "South Africa",            "南非"                ),
            GEO_COUNTRY_INFO(NGA,       Africa,       Abuja,          "Nigeria",                 "尼日利亚"            ),
            GEO_COUNTRY_INFO(GHA,       Africa,       Accra,          "Ghana",                   "加纳"                ),
            GEO_COUNTRY_INFO(KEN,       Africa,       Nairobi,        "Kenya",                   "肯尼亚"              ),
            GEO_COUNTRY_INFO(MAR,       Africa,       Rabat,          "Morocco",                 "摩洛哥"              ),
            GEO_COUNTRY_INFO(SAU,       Asia,         Riyadh,         "Saudi Arabia",            "沙特阿拉伯"          ),
            GEO_COUNTRY_INFO(ARE,       Asia,         AbuDhabi,       "United Arab Emirates",    "阿联酋"              ),
            GEO_COUNTRY_INFO(ISR,       Asia,         Jerusalem,      "Israel",                  "以色列"              ),
            GEO_COUNTRY_INFO(IRN,       Asia,         Tehran,         "Iran",                    "伊朗"                ),
            GEO_COUNTRY_INFO(IRQ,       Asia,         Baghdad,        "Iraq",                    "伊拉克"              ),
            GEO_COUNTRY_INFO(PAK,       Asia,         Islamabad,      "Pakistan",                "巴基斯坦"            ),
            GEO_COUNTRY_INFO(IDN,       Asia,         Jakarta,        "Indonesia",               "印度尼西亚"          ),
            GEO_COUNTRY_INFO(VNM,       Asia,         Hanoi,          "Vietnam",                 "越南"                ),
            GEO_COUNTRY_INFO(THA,       Asia,         Bangkok,        "Thailand",                "泰国"                ),
            GEO_COUNTRY_INFO(MYS,       Asia,         KualaLumpur,    "Malaysia",                "马来西亚"            ),
            GEO_COUNTRY_INFO(SGP,       Asia,         Singapore,      "Singapore",               "新加坡"              ),
            GEO_COUNTRY_INFO(PHL,       Asia,         Manila,         "Philippines",             "菲律宾"              ),
            GEO_COUNTRY_INFO(KHM,       Asia,         PhnomPenh,      "Cambodia",                "柬埔寨"              ),
            GEO_COUNTRY_INFO(LAO,       Asia,         Vientiane,      "Laos",                    "老挝"                ),
            GEO_COUNTRY_INFO(MMR,       Asia,         Yangon,         "Myanmar",                 "缅甸"                ),
            GEO_COUNTRY_INFO(NPL,       Asia,         Kathmandu,      "Nepal",                   "尼泊尔"              ),
            GEO_COUNTRY_INFO(BGD,       Asia,         Dhaka,          "Bangladesh",              "孟加拉国"            ),
            GEO_COUNTRY_INFO(LKA,       Asia,         Colombo,        "Sri Lanka",               "斯里兰卡"            ),
            GEO_COUNTRY_INFO(QAT,       Asia,         Doha,           "Qatar",                   "卡塔尔"              ),
            GEO_COUNTRY_INFO(KWT,       Asia,         KuwaitCity,     "Kuwait",                  "科威特"              ),
            GEO_COUNTRY_INFO(OMN,       Asia,         Muscat,         "Oman",                    "阿曼"                ),
            GEO_COUNTRY_INFO(JOR,       Asia,         Amman,          "Jordan",                  "约旦"                ),
            GEO_COUNTRY_INFO(LBN,       Asia,         Beirut,         "Lebanon",                 "黎巴嫩"              ),
            GEO_COUNTRY_INFO(SDN,       Africa,       Khartoum,       "Sudan",                   "苏丹"                ),
            GEO_COUNTRY_INFO(ETH,       Africa,       AddisAbaba,     "Ethiopia",                "埃塞俄比亚"          ),
            GEO_COUNTRY_INFO(DZA,       Africa,       Algiers,        "Algeria",                 "阿尔及利亚"          ),
            GEO_COUNTRY_INFO(TUN,       Africa,       Tunis,          "Tunisia",                 "突尼斯"              ),
            GEO_COUNTRY_INFO(ARG,       SouthAmerica, BuenosAires,    "Argentina",               "阿根廷"              ),
            GEO_COUNTRY_INFO(CHL,       SouthAmerica, Santiago,       "Chile",                   "智利"                ),
            GEO_COUNTRY_INFO(COL,       SouthAmerica, Bogota,         "Colombia",                "哥伦比亚"            ),
            GEO_COUNTRY_INFO(PER,       SouthAmerica, Lima,           "Peru",                    "秘鲁"                ),
            GEO_COUNTRY_INFO(VEN,       SouthAmerica, Caracas,        "Venezuela",               "委内瑞拉"            ),
            GEO_COUNTRY_INFO(URY,       SouthAmerica, Montevideo,     "Uruguay",                 "乌拉圭"              ),
            GEO_COUNTRY_INFO(PRY,       SouthAmerica, Asuncion,       "Paraguay",                "巴拉圭"              ),
            GEO_COUNTRY_INFO(BOL,       SouthAmerica, LaPaz,          "Bolivia",                 "玻利维亚"            ),
            GEO_COUNTRY_INFO(ECU,       SouthAmerica, Quito,          "Ecuador",                 "厄瓜多尔"            ),
            GEO_COUNTRY_INFO(CRI,       NorthAmerica, Unknow,         "Costa Rica",              "哥斯达黎加"          ),
            GEO_COUNTRY_INFO(PAN,       NorthAmerica, Unknow,         "Panama",                  "巴拿马"              ),
            GEO_COUNTRY_INFO(CUB,       NorthAmerica, Unknow,         "Cuba",                    "古巴"                ),
            GEO_COUNTRY_INFO(DOM,       NorthAmerica, Unknow,         "Dominican Republic",      "多米尼加"            ),
            GEO_COUNTRY_INFO(JAM,       NorthAmerica, Unknow,         "Jamaica",                 "牙买加"              ),
            GEO_COUNTRY_INFO(ISL,       Europe,       Reykjavik,      "Iceland",                 "冰岛"                ),
            GEO_COUNTRY_INFO(IRL,       Europe,       Dublin,         "Ireland",                 "爱尔兰"              ),
            GEO_COUNTRY_INFO(UKR,       Europe,       Kyiv,           "Ukraine",                 "乌克兰"              ),
            GEO_COUNTRY_INFO(BLR,       Europe,       Minsk,          "Belarus",                 "白俄罗斯"            ),
            GEO_COUNTRY_INFO(ROU,       Europe,       Bucharest,      "Romania",                 "罗马尼亚"            ),
            GEO_COUNTRY_INFO(BGR,       Europe,       Sofia,          "Bulgaria",                "保加利亚"            ),
            GEO_COUNTRY_INFO(HUN,       Europe,       Budapest,       "Hungary",                 "匈牙利"              ),
            GEO_COUNTRY_INFO(SRB,       Europe,       Belgrade,       "Serbia",                  "塞尔维亚"            ),
            GEO_COUNTRY_INFO(HRV,       Europe,       Zagreb,         "Croatia",                 "克罗地亚"            ),
            GEO_COUNTRY_INFO(SVN,       Europe,       Ljubljana,      "Slovenia",                "斯洛文尼亚"          ),
            GEO_COUNTRY_INFO(SVK,       Europe,       Bratislava,     "Slovakia",                "斯洛伐克"            ),
            GEO_COUNTRY_INFO(EST,       Europe,       Tallinn,        "Estonia",                 "爱沙尼亚"            ),
            GEO_COUNTRY_INFO(LVA,       Europe,       Riga,           "Latvia",                  "拉脱维亚"            ),
            GEO_COUNTRY_INFO(LTU,       Europe,       Vilnius,        "Lithuania",               "立陶宛"              ),
            GEO_COUNTRY_INFO(MLT,       Europe,       Valletta,       "Malta",                   "马耳他"              ),
            GEO_COUNTRY_INFO(CYP,       Europe,       Nicosia,        "Cyprus",                  "塞浦路斯"            ),
            GEO_COUNTRY_INFO(GEO,       Asia,         Tbilisi,        "Georgia",                 "格鲁吉亚"            ),
            GEO_COUNTRY_INFO(KAZ,       Asia,         Astana,         "Kazakhstan",              "哈萨克斯坦"          ),
            GEO_COUNTRY_INFO(UZB,       Asia,         Tashkent,       "Uzbekistan",              "乌兹别克斯坦"        ),
            GEO_COUNTRY_INFO(AZE,       Asia,         Baku,           "Azerbaijan",              "阿塞拜疆"            ),
            GEO_COUNTRY_INFO(ARM,       Asia,         Yerevan,        "Armenia",                 "亚美尼亚"            ),
            GEO_COUNTRY_INFO(MNG,       Asia,         Ulaanbaatar,    "Mongolia",                "蒙古"                ),
            GEO_COUNTRY_INFO(BHR,       Asia,         Manama,         "Bahrain",                 "巴林"                )

#undef GEO_COUNTRY_INFO
        };


        static CityInfo kCities[] =
        {
#define GEO_CITY_INFO(country,continent,city,eng_name,chs_name,lat,lon,alt,tz) { CountryID::country, Continent::continent, CityID::city, U16_TEXT(eng_name), U16_TEXT(chs_name), lat, lon, alt, tz }

            // China - major cities (all UTC+8 => 480 minutes)
            GEO_CITY_INFO(PRC,  Asia, BeiJing,       "Beijing",       "北京",        39.9042f, 116.4074f, 44.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, ShangHai,      "Shanghai",      "上海",        31.2304f, 121.4737f, 4.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, TianJin,       "Tianjin",       "天津",        39.3434f, 117.3616f, 5.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, ChongQing,     "Chongqing",     "重庆",        29.5630f, 106.5516f, 350.0f,  480),

            GEO_CITY_INFO(PRC,  Asia, GuangZhou,     "Guangzhou",     "广州",        23.1291f, 113.2644f, 21.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, ShenZhen,      "Shenzhen",      "深圳",        22.5431f, 114.0579f, 6.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, ChengDu,       "Chengdu",       "成都",        30.5728f, 104.0668f, 500.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, HangZhou,      "Hangzhou",      "杭州",        30.2741f, 120.1551f, 9.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, NanJing,       "Nanjing",       "南京",        32.0603f, 118.7969f, 20.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, WuHan,         "Wuhan",         "武汉",        30.5928f, 114.3055f, 37.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, XiAn,          "Xi'an",         "西安",        34.3416f, 108.9398f, 400.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, SuZhou,        "Suzhou",        "苏州",        31.2989f, 120.5853f, 5.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, QingDao,       "Qingdao",       "青岛",        36.0671f, 120.3826f, 77.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, JiNan,         "Jinan",         "济南",        36.6512f, 117.1201f, 23.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, HeFei,         "Hefei",         "合肥",        31.8206f, 117.2272f, 22.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, ChangSha,      "Changsha",      "长沙",        28.2282f, 112.9388f, 44.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, NanChang,      "Nanchang",      "南昌",        28.6829f, 115.8582f, 24.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, FuZhou,        "Fuzhou",        "福州",        26.0745f, 119.2965f, 14.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, Xiamen,        "Xiamen",        "厦门",        24.4798f, 118.0894f, 10.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, KunMing,       "Kunming",       "昆明",        25.0389f, 102.7183f, 1892.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, GuiYang,       "Guiyang",       "贵阳",        26.6470f, 106.6302f, 1100.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, LanZhou,       "Lanzhou",       "兰州",        36.0611f, 103.8343f, 1518.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, Urumqi,        "Ürümqi",        "乌鲁木齐",    43.8256f,  87.6168f, 800.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, HarBin,        "Harbin",        "哈尔滨",      45.8038f, 126.5349f, 150.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, ChangChun,     "Changchun",     "长春",        43.8171f, 125.3235f, 222.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, Shenyang,      "Shenyang",      "沈阳",        41.8057f, 123.4315f, 55.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, NingBo,        "Ningbo",        "宁波",        29.8683f, 121.5440f, 4.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, Wuxi,          "Wuxi",          "无锡",        31.4912f, 120.3119f, 5.0f,    480),

            GEO_CITY_INFO(PRC,  Asia, ShiJiaZhuang,  "Shijiazhuang",  "石家庄",      38.0428f, 114.5149f, 83.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, TaiYuan,       "Taiyuan",       "太原",        37.8706f, 112.5489f, 800.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, HuHeHaoTe,     "Hohhot",        "呼和浩特",    40.8426f, 111.7490f, 1065.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, ZhengZhou,     "Zhengzhou",     "郑州",        34.7466f, 113.6254f, 110.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, NanNing,       "Nanning",       "南宁",        22.8170f, 108.3669f, 80.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, HaiKou,        "Haikou",        "海口",        20.0440f, 110.1983f, 4.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, LaSa,          "Lhasa",         "拉萨",        29.6520f,  91.1721f, 3650.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, XiNing,        "Xining",        "西宁",        36.6171f, 101.7782f, 2275.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, YinChuan,      "Yinchuan",      "银川",        38.4872f, 106.2309f, 1110.0f, 480),
            GEO_CITY_INFO(PRC,  Asia, GuiLin,        "Guilin",        "桂林",        25.2742f, 110.2950f, 152.0f,  480),
            GEO_CITY_INFO(PRC,  Asia, DaLian,        "Dalian",        "大连",        38.9140f, 121.6147f, 29.0f,   480),
            GEO_CITY_INFO(PRC,  Asia, ZhuHai,        "Zhuhai",        "珠海",        22.2707f, 113.5767f, 6.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, SanYa,         "Sanya",         "三亚",        18.2528f, 109.5119f, 7.0f,    480),
            GEO_CITY_INFO(PRC,  Asia, LiJiang,       "Lijiang",       "丽江",        26.8721f, 100.2382f, 2418.0f, 480),

            // Capitals and notable cities
            GEO_CITY_INFO(USA,  NorthAmerica, WashingtonDC,  "Washington, D.C.", "华盛顿",        38.9072f,  -77.0369f, 7.0f,   -300),
            GEO_CITY_INFO(UK,   Europe,       London,        "London",            "伦敦",         51.5072f,   -0.1276f, 11.0f,   0),
            GEO_CITY_INFO(FRA,  Europe,       Paris,         "Paris",             "巴黎",         48.8566f,    2.3522f, 35.0f,   60),
            GEO_CITY_INFO(DEU,  Europe,       Berlin,        "Berlin",            "柏林",         52.5200f,   13.4050f, 34.0f,   60),
            GEO_CITY_INFO(ITA,  Europe,       Rome,          "Rome",              "罗马",         41.9028f,   12.4964f, 21.0f,   60),
            GEO_CITY_INFO(ESP,  Europe,       Madrid,        "Madrid",            "马德里",       40.4168f,   -3.7038f, 667.0f,  60),
            GEO_CITY_INFO(JPN,  Asia,         Tokyo,         "Tokyo",             "东京",         35.6762f,  139.6503f, 40.0f,  540),
            GEO_CITY_INFO(KOR,  Asia,         Seoul,         "Seoul",             "首尔",         37.5665f,  126.9780f, 38.0f,  540),
            GEO_CITY_INFO(IND,  Asia,         Delhi,         "New Delhi",         "新德里",       28.6139f,   77.2090f, 216.0f, 330),
            GEO_CITY_INFO(RUS,  Europe,       Moscow,        "Moscow",            "莫斯科",       55.7558f,   37.6173f, 156.0f, 180),
            GEO_CITY_INFO(CAN,  NorthAmerica, Ottawa,        "Ottawa",            "渥太华",       45.4215f,  -75.6972f, 70.0f,  -300),
            GEO_CITY_INFO(AUS,  Oceania,      Canberra,      "Canberra",          "堪培拉",       -35.2809f, 149.1300f, 577.0f, 600),
            GEO_CITY_INFO(NZL,  Oceania,      Wellington,    "Wellington",        "惠灵顿",       -41.2866f, 174.7756f, 12.0f,  720),
            GEO_CITY_INFO(BRA,  SouthAmerica, Brasilia,      "Brasilia",          "巴西利亚",     -15.7939f, -47.8828f, 1172.0f,-180),
            GEO_CITY_INFO(MEX,  NorthAmerica, MexicoCity,    "Mexico City",       "墨西哥城",     19.4326f,  -99.1332f, 2240.0f,-360),
            GEO_CITY_INFO(TUR,  Asia,         Ankara,        "Ankara",            "安卡拉",       39.9334f,   32.8597f, 938.0f,  180),
            GEO_CITY_INFO(GRC,  Europe,       Athens,        "Athens",            "雅典",         37.9838f,   23.7275f, 70.0f,  120),
            GEO_CITY_INFO(EGY,  Africa,       Cairo,         "Cairo",             "开罗",         30.0444f,   31.2357f, 23.0f,  120),
            GEO_CITY_INFO(ZAF,  Africa,       Pretoria,      "Pretoria",          "比勒陀利亚",   -25.7479f,  28.2293f, 1350.0f,120),
            GEO_CITY_INFO(ZAF,  Africa,       CapeTown,      "Cape Town",         "开普敦",       -33.9249f,  18.4241f, 25.0f,  120),
            GEO_CITY_INFO(SAU,  Asia,         Riyadh,        "Riyadh",            "利雅得",       24.7136f,   46.6753f, 612.0f, 180),
            GEO_CITY_INFO(ARE,  Asia,         AbuDhabi,      "Abu Dhabi",         "阿布扎比",     24.4539f,   54.3773f, 5.0f,   240),
            GEO_CITY_INFO(ISR,  Asia,         Jerusalem,     "Jerusalem",         "耶路撒冷",     31.7683f,   35.2137f, 754.0f, 120),
            GEO_CITY_INFO(IRN,  Asia,         Tehran,        "Tehran",            "德黑兰",       35.6892f,   51.3890f, 1191.0f,210),
            GEO_CITY_INFO(IRQ,  Asia,         Baghdad,       "Baghdad",           "巴格达",       33.3152f,   44.3661f, 34.0f,  180),
            GEO_CITY_INFO(PAK,  Asia,         Islamabad,     "Islamabad",         "伊斯兰堡",     33.6844f,   73.0479f, 540.0f, 300),
            GEO_CITY_INFO(IDN,  Asia,         Jakarta,       "Jakarta",           "雅加达",       -6.2088f,  106.8456f, 8.0f,   420),
            GEO_CITY_INFO(VNM,  Asia,         Hanoi,         "Hanoi",             "河内",         21.0278f,  105.8342f, 16.0f,  420),
            GEO_CITY_INFO(THA,  Asia,         Bangkok,       "Bangkok",           "曼谷",         13.7563f,  100.5018f, 2.0f,   420),
            GEO_CITY_INFO(MYS,  Asia,         KualaLumpur,   "Kuala Lumpur",      "吉隆坡",       3.1390f,   101.6869f, 21.0f,  480),
            GEO_CITY_INFO(SGP,  Asia,         Singapore,     "Singapore",         "新加坡",       1.3521f,   103.8198f, 15.0f,  480),
            GEO_CITY_INFO(PHL,  Asia,         Manila,        "Manila",            "马尼拉",       14.5995f,  120.9842f, 16.0f,  480),
            GEO_CITY_INFO(PRC,  Asia,         Taipei,        "Taipei",            "台北",         25.0330f,  121.5654f, 10.0f,  480),
            GEO_CITY_INFO(PRC,  Asia,         HongKong,      "Hong Kong",         "香港",         22.3193f,  114.1694f, 9.0f,   480),
            GEO_CITY_INFO(KHM,  Asia,         PhnomPenh,     "Phnom Penh",        "金边",         11.5564f,  104.9282f, 12.0f,  420),
            GEO_CITY_INFO(LAO,  Asia,         Vientiane,     "Vientiane",         "万象",         17.9757f,  102.6331f, 174.0f, 420),
            GEO_CITY_INFO(MMR,  Asia,         Yangon,        "Yangon",            "仰光",         16.8409f,   96.1735f, 23.0f,  390),
            GEO_CITY_INFO(NPL,  Asia,         Kathmandu,     "Kathmandu",         "加德满都",     27.7172f,   85.3240f, 1400.0f,345),
            GEO_CITY_INFO(BGD,  Asia,         Dhaka,         "Dhaka",             "达卡",         23.8103f,   90.4125f, 4.0f,   360),
            GEO_CITY_INFO(LKA,  Asia,         Colombo,       "Colombo",           "科伦坡",       6.9271f,    79.8612f, 1.0f,   330),
            GEO_CITY_INFO(QAT,  Asia,         Doha,          "Doha",              "多哈",         25.2769f,   51.5210f, 10.0f,  180),
            GEO_CITY_INFO(KWT,  Asia,         KuwaitCity,    "Kuwait City",       "科威特城",     29.3759f,   47.9774f, 15.0f,  180),
            GEO_CITY_INFO(OMN,  Asia,         Muscat,        "Muscat",            "马斯喀特",     23.5880f,   58.3829f, 15.0f,  240),
            GEO_CITY_INFO(JOR,  Asia,         Amman,         "Amman",             "安曼",         31.9454f,   35.9284f, 777.0f,  120),
            GEO_CITY_INFO(LBN,  Asia,         Beirut,        "Beirut",            "贝鲁特",       33.8938f,   35.5018f, 40.0f,  120),
            GEO_CITY_INFO(DZA,  Africa,       Algiers,       "Algiers",           "阿尔及尔",     36.7538f,    3.0588f, 0.0f,   60),
            GEO_CITY_INFO(TUN,  Africa,       Tunis,         "Tunis",             "突尼斯",       36.8065f,   10.1815f, 4.0f,   60),
            GEO_CITY_INFO(ARG,  SouthAmerica, BuenosAires,   "Buenos Aires",      "布宜诺斯艾利斯", -34.6037f, -58.3816f, 25.0f, -180),
            GEO_CITY_INFO(CHL,  SouthAmerica, Santiago,      "Santiago",          "圣地亚哥",     -33.4489f, -70.6693f, 570.0f, -240),
            GEO_CITY_INFO(COL,  SouthAmerica, Bogota,        "Bogota",            "波哥大",       4.7110f,   -74.0721f, 2640.0f,-300),
            GEO_CITY_INFO(PER,  SouthAmerica, Lima,          "Lima",              "利马",         -12.0464f, -77.0428f, 154.0f, -300),
            GEO_CITY_INFO(VEN,  SouthAmerica, Caracas,       "Caracas",           "加拉加斯",     10.4806f,  -66.9036f, 900.0f, -240),
            GEO_CITY_INFO(URY,  SouthAmerica, Montevideo,    "Montevideo",        "蒙得维的亚",   -34.9011f, -56.1645f, 43.0f,  -180),
            GEO_CITY_INFO(PRY,  SouthAmerica, Asuncion,      "Asuncion",          "亚松森",       -25.2637f, -57.5759f, 43.0f,  -240),
            GEO_CITY_INFO(BOL,  SouthAmerica, LaPaz,         "La Paz",            "拉巴斯",       -16.4897f, -68.1193f, 3640.0f,-240),
            GEO_CITY_INFO(ECU,  SouthAmerica, Quito,         "Quito",             "基多",         -0.1807f,   -78.4678f, 2850.0f,-300),
            GEO_CITY_INFO(ISL,  Europe,       Reykjavik,     "Reykjavik",         "雷克雅未克",   64.1466f,  -21.9426f, 61.0f,   0),
            GEO_CITY_INFO(IRL,  Europe,       Dublin,        "Dublin",            "都柏林",       53.3498f,   -6.2603f, 20.0f,   0),
            GEO_CITY_INFO(UKR,  Europe,       Kyiv,          "Kyiv",              "基辅",         50.4501f,   30.5234f, 179.0f, 120),
            GEO_CITY_INFO(BLR,  Europe,       Minsk,         "Minsk",             "明斯克",       53.9006f,   27.5590f, 220.0f, 180),
            GEO_CITY_INFO(ROU,  Europe,       Bucharest,     "Bucharest",         "布加勒斯特",   44.4268f,   26.1025f, 70.0f,  120),
            GEO_CITY_INFO(BGR,  Europe,       Sofia,         "Sofia",             "索非亚",       42.6977f,   23.3219f, 550.0f, 120),
            GEO_CITY_INFO(HUN,  Europe,       Budapest,      "Budapest",          "布达佩斯",     47.4979f,   19.0402f, 96.0f,  60),
            GEO_CITY_INFO(SRB,  Europe,       Belgrade,      "Belgrade",          "贝尔格莱德",   44.7866f,   20.4489f, 117.0f, 60),
            GEO_CITY_INFO(HRV,  Europe,       Zagreb,        "Zagreb",            "萨格勒布",     45.8150f,   15.9819f, 158.0f, 60),
            GEO_CITY_INFO(SVN,  Europe,       Ljubljana,     "Ljubljana",         "卢布尔雅那",   46.0569f,   14.5058f, 295.0f, 60),
            GEO_CITY_INFO(SVK,  Europe,       Bratislava,    "Bratislava",        "布拉迪斯拉发", 48.1486f,   17.1077f, 134.0f, 60),
            GEO_CITY_INFO(EST,  Europe,       Tallinn,       "Tallinn",           "塔林",         59.4370f,   24.7536f, 9.0f,   120),
            GEO_CITY_INFO(LVA,  Europe,       Riga,          "Riga",              "里加",         56.9496f,   24.1052f, 10.0f,  120),
            GEO_CITY_INFO(LTU,  Europe,       Vilnius,       "Vilnius",           "维尔纽斯",     54.6872f,   25.2797f, 112.0f, 120),
            GEO_CITY_INFO(MLT,  Europe,       Valletta,      "Valletta",          "瓦莱塔",       35.8989f,   14.5146f, 56.0f,  60),
            GEO_CITY_INFO(CYP,  Europe,       Nicosia,       "Nicosia",           "尼科西亚",     35.1856f,   33.3823f, 220.0f, 120),
            GEO_CITY_INFO(GEO,  Asia,         Tbilisi,       "Tbilisi",           "第比利斯",     41.7151f,   44.8271f, 380.0f, 240),
            GEO_CITY_INFO(KAZ,  Asia,         Astana,        "Astana",            "阿斯塔纳",     51.1605f,   71.4704f, 347.0f, 360),
            GEO_CITY_INFO(UZB,  Asia,         Tashkent,      "Tashkent",          "塔什干",       41.2995f,   69.2401f, 455.0f, 300),
            GEO_CITY_INFO(AZE,  Asia,         Baku,          "Baku",              "巴库",         40.4093f,   49.8671f, 28.0f,  240),
            GEO_CITY_INFO(ARM,  Asia,         Yerevan,       "Yerevan",           "埃里温",       40.1792f,   44.4991f, 990.0f, 240),
            GEO_CITY_INFO(MNG,  Asia,         Ulaanbaatar,   "Ulaanbaatar",       "乌兰巴托",     47.8864f,  106.9057f, 1350.0f,480),
            GEO_CITY_INFO(BHR,  Asia,         Manama,        "Manama",            "麦纳麦",       26.2285f,   50.5860f, 10.0f,  180),

            // Additional capitals in Africa
            GEO_CITY_INFO(NGA,  Africa,       Abuja,         "Abuja",             "阿布贾",       9.0765f,    7.3986f, 840.0f, 60),
            GEO_CITY_INFO(KEN,  Africa,       Nairobi,       "Nairobi",           "内罗毕",       -1.2921f,   36.8219f, 1795.0f,180),
            GEO_CITY_INFO(MAR,  Africa,       Rabat,         "Rabat",             "拉巴特",       34.0209f,   -6.8416f, 75.0f,  0),
            GEO_CITY_INFO(GHA,  Africa,       Accra,         "Accra",             "阿克拉",       5.6037f,   -0.1870f, 61.0f,  0),
            GEO_CITY_INFO(ETH,  Africa,       AddisAbaba,    "Addis Ababa",       "亚的斯亚贝巴", 8.9806f,   38.7578f, 2355.0f,180),
            GEO_CITY_INFO(SDN,  Africa,       Khartoum,      "Khartoum",          "喀土穆",       15.5007f,  32.5599f, 382.0f, 120),

            // Famous non-capital cities (selection)
            GEO_CITY_INFO(USA,  NorthAmerica, NewYork,       "New York",         "纽约",         40.7128f,  -74.0060f, 10.0f, -300),
            GEO_CITY_INFO(USA,  NorthAmerica, LosAngeles,    "Los Angeles",      "洛杉矶",       34.0522f, -118.2437f, 71.0f, -480),

#undef GEO_CITY_INFO
        };

        static int next_normalized_ascii_letter(const u16char **p)
        {
            const u16char *s = (const u16char *)*p;

            while (*s)
            {
                u16char c = *s;

                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                {
                    u16char lower = (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;

                    s++;
                    *p = (const u16char *)s;

                    return (int)lower;
                }
                s++;
            }

            *p = (const u16char *)s;
            return 0; /* end */
        }

        static int compare_names(const u16char *a, const u16char *b)
        {
            const u16char *pa = a;
            const u16char *pb = b;
            int ca, cb;

            for (;;)
            {
                ca = next_normalized_ascii_letter(&pa);
                cb = next_normalized_ascii_letter(&pb);

                if (ca == 0 && cb == 0) return 0;
                if (ca == 0) return -1;
                if (cb == 0) return 1;
                if (ca < cb) return -1;
                if (ca > cb) return 1;
            }
        }
    } // namespace

    const CountryInfo *GetCountryInfo(CountryID id)
    {
        for(const auto &ci:kCountries)
            if (ci.country_id==id)
                return &ci;

        return nullptr;
    }

    const CityInfo *GetCityInfo(CityID id)
    {
        for(const auto &ci:kCities)
        {
            if(ci.city_id==id)
                return &ci;
        }

        return nullptr;
    }

    const CountryInfo *GetCountryInfoByEngName(const U16String &eng_name)
    {
        for(const auto &ci:kCountries)
            if (!compare_names(eng_name.c_str(),ci.eng_name))
                return &ci;

        return nullptr;
    }

    const CountryInfo *GetCountryInfoByChsName(const U16String &chs_name)
    {
        for(const auto &ci:kCountries)
            if (!chs_name.Comp(ci.chs_name))
                return &ci;
        return nullptr;
    }

    const CityInfo *GetCityInfoByEngName(const U16String &eng_name)
    {
        for(const auto &ci:kCities)
            if(!compare_names(eng_name.c_str(),ci.eng_name))
                return &ci;
        return nullptr;
    }

    const CityInfo *GetCityInfoByChsName(const U16String &chs_name)
    {
        for(const auto &ci:kCities)
            if (!chs_name.Comp(ci.chs_name))
                return &ci;
        return nullptr;
    }

    static constexpr double PI_CONST = 3.14159265358979323846;
    static inline double deg2rad(double d){ return d * PI_CONST / 180.0; }
    static inline double rad2deg(double r){ return r * 180.0 / PI_CONST; }

    // Based on NOAA Solar Calculator (https://gml.noaa.gov/grad/solcalc/)
    const bool GetSunTime(float *sunrise,float *sunset,const float latitude,const float longitude,const CalendarDate &date)
    {
        if(!sunrise || !sunset) return false;

        // day of year
        int N = date.DayOfYear();

        // longitude hour value
        double lngHour = static_cast<double>(longitude) / 15.0;

        auto calc_time_utc = [&](double targetHour, double &outUT)->bool
        {
            // t for rise/set
            double t = static_cast<double>(N) + ((targetHour - lngHour) / 24.0);

            // Sun's mean anomaly
            double M = (0.9856 * t) - 3.289;

            // Sun's true longitude
            double L = M + (1.916 * sin(deg2rad(M))) + (0.020 * sin(deg2rad(2.0*M))) + 282.634;
            // normalize L to [0,360)
            L = fmod(L,360.0);
            if(L < 0) L += 360.0;

            // Sun's right ascension
            double RA = rad2deg(atan(0.91764 * tan(deg2rad(L))));
            // normalize RA to [0,360)
            RA = fmod(RA,360.0);
            if(RA < 0) RA += 360.0;

            // RA needs to be in the same quadrant as L
            double Lquadrant  = floor(L/90.0) * 90.0;
            double RAquadrant = floor(RA/90.0) * 90.0;
            RA = RA + (Lquadrant - RAquadrant);

            // RA into hours
            RA = RA / 15.0;

            // Sun's declination
            double sinDec = 0.39782 * sin(deg2rad(L));
            double cosDec = cos(asin(sinDec));

            // Sun's local hour angle
            double zenith = 90.833; // official zenith for sunrise/sunset
            double cosH = (cos(deg2rad(zenith)) - (sinDec * sin(deg2rad(latitude)))) / (cosDec * cos(deg2rad(latitude)));

            if(cosH > 1.0) return false; // sun never rises
            if(cosH < -1.0) return false; // sun never sets

            double H;
            if(targetHour <= 12.0)
            {
                // sunrise
                H = 360.0 - rad2deg(acos(cosH));
            }
            else
            {
                // sunset
                H = rad2deg(acos(cosH));
            }

            H = H / 15.0;

            // local mean time
            double T = H + RA - (0.06571 * t) - 6.622;

            // convert to UTC
            double UT = T - lngHour;
            // normalize to [0,24)
            UT = fmod(UT,24.0);
            if(UT < 0) UT += 24.0;

            outUT = UT;
            return true;
        };

        double riseUTC, setUTC;
        bool okRise = calc_time_utc(6.0, riseUTC);
        bool okSet  = calc_time_utc(18.0, setUTC);

        if(!okRise || !okSet)
        {
            // polar day/night or other issue: signal failure
            *sunrise = -1.0f;
            *sunset  = -1.0f;
            return false;
        }

        *sunrise = static_cast<float>(riseUTC);
        *sunset  = static_cast<float>(setUTC);

        return true;
    }

}
