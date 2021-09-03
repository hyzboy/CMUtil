option(CM_UTIL_SUPPORT_XML "Build XML Parse module." ON)

SET(CM_XML_INCLUDE_PATH ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml)

if(CM_UTIL_SUPPORT_XML)

    SET(XML_ELEMENT_PARSE_KV    ${CM_XML_INCLUDE_PATH}/ElementParseKV.h
                                xml/ElementParseKV.cpp)

    SET(XML_ELEMENT_PARSE_CREATER   ${CM_XML_INCLUDE_PATH}/ElementParseCreater.h
                                    xml/ElementParseCreater.cpp
                                    xml/ElementCreater.cpp)

    SET(XML_ELEMENT_PARSE_SOURCE    ${CM_XML_INCLUDE_PATH}/ElementParse.h)

    SET(XML_PARSE_CLASS_SOURCE  ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml/XMLParse.h
                                xml/XMLParseClass.cpp)

    SET(XML_PARSE_SOURCE    ${XML_ELEMENT_PARSE_KV}
                            ${XML_ELEMENT_PARSE_CREATER}
                            ${XML_ELEMENT_PARSE_SOURCE}

                            ${XML_PARSE_CLASS_SOURCE})

    SOURCE_GROUP("XML\\ElementParse\\KV" FILES ${XML_ELEMENT_PARSE_KV})
    SOURCE_GROUP("XML\\ElementParse\\Creater" FILES ${XML_ELEMENT_PARSE_CREATER})
    SOURCE_GROUP("XML\\ElementParse" FILES ${XML_ELEMENT_PARSE_SOURCE})
    SOURCE_GROUP("XML" FILES ${XML_PARSE_CLASS_SOURCE})

    IF(WIN32)
        SET(EXPAT_SOURCE_PATH ${CMUTIL_ROOT_3RDPTY_PATH}/expat/expat/lib)

        include_directories(${CMUTIL_ROOT_3RDPTY_PATH}/expat/expat)
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


option(CM_UTIL_SUPPORT_HASH "Build HASH module" ON)

IF(CM_UTIL_SUPPORT_HASH)
    SET(HASH_HEADER_FILES   ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/hash/Hash.h
                            ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/hash/SHA1LE.h)

    SET(HASH_SOURCE_FILES   hash/adler32.cpp
                            hash/crc32.cpp
                            hash/Hash.cpp
                            hash/md4.cpp
                            hash/md5.cpp
                            hash/sha1.cpp
                            hash/sha1le.cpp
                            hash/sha256.cpp
                            hash/sha512.cpp)

    SOURCE_GROUP("HASH" FILES ${HASH_HEADER_FILES} ${HASH_SOURCE_FILES})
ENDIF(CM_UTIL_SUPPORT_HASH)

add_cm_library(CMUtil "CM"	${CMD_SOURCE}
#							${TIME_SOURCE}

                            ${XML_PARSE_SOURCE}
                            ${JSON_TOOL_SOURCE}

                            ${HASH_HEADER_FILES}
                            ${HASH_SOURCE_FILES}
                           )
