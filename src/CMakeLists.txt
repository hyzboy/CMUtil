option(CM_UTIL_SUPPORT_XML "Build XML Parse module." ON)

if(CM_UTIL_SUPPORT_XML)

    find_package(expat CONFIG REQUIRED)

    SET(CM_XML_INCLUDE_PATH         ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml)

    SET(XML_ELEMENT_PARSE_KV        ${CM_XML_INCLUDE_PATH}/ElementParseKV.h
                                    xml/ElementParseKV.cpp)
                                    
    SET(XML_ELEMENT_PARSE_CREATER   ${CM_XML_INCLUDE_PATH}/ElementParseCreater.h
                                    xml/ElementParseCreater.cpp
                                    xml/ElementCreater.cpp)

    SET(XML_ELEMENT_PARSE_SOURCE    ${CM_XML_INCLUDE_PATH}/ElementParse.h)

    SET(XML_PARSE_CLASS_SOURCE      ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml/XMLParse.h
                                    xml/XMLParseClass.cpp)
                                    
    SET(XML_PARSE_SOURCE            ${XML_ELEMENT_PARSE_KV}
                                    ${XML_ELEMENT_PARSE_CREATER}
                                    ${XML_ELEMENT_PARSE_SOURCE}

                                    ${XML_PARSE_CLASS_SOURCE})

    SOURCE_GROUP("XML\\ElementParse\\KV" FILES ${XML_ELEMENT_PARSE_KV})
    SOURCE_GROUP("XML\\ElementParse\\Creater" FILES ${XML_ELEMENT_PARSE_CREATER})
    SOURCE_GROUP("XML\\ElementParse" FILES ${XML_ELEMENT_PARSE_SOURCE})
    SOURCE_GROUP("XML" FILES ${XML_PARSE_CLASS_SOURCE})

endif(CM_UTIL_SUPPORT_XML)

option(CM_UTIL_SUPPORT_JSON "Build JSON Parse/make module." ON)

IF(CM_UTIL_SUPPORT_JSON)
    find_package(jsoncpp CONFIG REQUIRED)

    set(JSON_TOOL_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/json/JsonTool.h
                         json/JsonTool.cpp)

    SOURCE_GROUP("JSON" FILES ${JSON_TOOL_SOURCE})
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

if(CM_UTIL_SUPPORT_XML)
    target_link_libraries(CMUtil PRIVATE expat::expat)
endif()

IF(CM_UTIL_SUPPORT_JSON)
    target_link_libraries(CMUtil PRIVATE jsoncpp_lib jsoncpp_object JsonCpp::JsonCpp)
ENDIF(CM_UTIL_SUPPORT_JSON)