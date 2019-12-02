option(CM_UTIL_SUPPORT_XML "Build XML Parse module." ON)

if(CM_UTIL_SUPPORT_XML)
    SET(XML_PARSE_SOURCE    ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml/XMLParse.h
                            xml/XMLParseClass.cpp)

    SOURCE_GROUP("XML" FILES ${XML_PARSE_SOURCE})

    IF(WIN32)
        SET(EXPAT_SOURCE_PATH ${CMUTIL_ROOT_3RDPTY_PATH}/expat/expat/lib)

        include_directories(${EXPAT_SOURCE_PATH})

        SET(EXPAT_SOURCE
            ${EXPAT_SOURCE_PATH}/xmlparse.c
            ${EXPAT_SOURCE_PATH}/xmlrole.c
            ${EXPAT_SOURCE_PATH}/xmltok.c
            ${EXPAT_SOURCE_PATH}/xmltok_impl.c
            ${EXPAT_SOURCE_PATH}/xmltok_ns.c)

        SOURCE_GROUP("XML\\Expat" FILES ${EXPAT_SOURCE})

        SET(XML_PARSE_SOURCE ${XML_PARSE_SOURCE} ${EXPAT_SOURCE})
    ENDIF(WIN32)
endif(CM_UTIL_SUPPORT_XML)

option(CM_UTIL_SUPPORT_JSON "Build JSON Parse/make module." ON)

IF(CM_UTIL_SUPPORT_JSON)
    set(JSON_TOOL_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/json/JsonTool.h
                         json/JsonTool.cpp)

    SOURCE_GROUP("JSON" FILES ${JSON_TOOL_SOURCE})

    IF(WIN32)
        SET(JSONCPP_PATH ${CMUTIL_ROOT_3RDPTY_PATH}/jsoncpp)

        include_directories(${JSONCPP_PATH}/include)
        include_directories(${JSONCPP_PATH}/src/lib_json)

        SET(JSONCPP_SOURCE  ${JSONCPP_PATH}/src/lib_json/json_reader.cpp
                            ${JSONCPP_PATH}/src/lib_json/json_value.cpp
                            ${JSONCPP_PATH}/src/lib_json/json_writer.cpp)

        SOURCE_GROUP("JSON\\jsoncpp" FILES ${JSONCPP_SOURCE})

        SET(JSON_TOOL_SOURCE ${JSON_TOOL_SOURCE} ${JSONCPP_SOURCE})
    ENDIF(WIN32)
ENDIF(CM_UTIL_SUPPORT_JSON)

SET(CMD_SOURCE  ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/cmd/CmdParse.h
                cmd/CmdParse.cpp)

#SET(TIME_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/time/Timer.h
#                time/Timer.cpp)

SOURCE_GROUP("Command Line" FILES ${CMD_SOURCE})
#SOURCE_GROUP("Time" FILES ${TIME_SOURCE})

add_cm_library(CMUtil "CM"	${CMD_SOURCE}
#							${TIME_SOURCE}

                            ${XML_PARSE_SOURCE}
                            ${JSON_TOOL_SOURCE}
                           )
