SET(XML_PARSE_SOURCE XMLParseClass.cpp)

SOURCE_GROUP("XML" FILES XMLParseClass.cpp)

IF(WIN32)
    SET(EXPAT_SOURCE_PATH ${CMUTIL_ROOT_3RDPTY_PATH}/expat/expat/lib)

    include_directories(${EXPAT_SOURCE_PATH})

    SET(EXPAT_SOURCE
        ${EXPAT_SOURCE_PATH}/xmlparse.c
        ${EXPAT_SOURCE_PATH}/xmlrole.c
        ${EXPAT_SOURCE_PATH}/xmltok.c
        ${EXPAT_SOURCE_PATH}/xmltok_impl.c
        ${EXPAT_SOURCE_PATH}/xmltok_ns.c)

    SET(XML_PARSE_SOURCE ${XML_PARSE_SOURCE} ${EXPAT_SOURCE})

    SOURCE_GROUP("XML\\Expat" FILES ${EXPAT_SOURCE})
ENDIF(WIN32)

add_cm_library(CMUtil.XML "CM/Util" ${XML_PARSE_SOURCE})
