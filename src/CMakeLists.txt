#################################################################################################### XML
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

    SET(TREE_XML_SOURCE             ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/xml/TreeXML.h
                                    xml/TreeXML.cpp)

    SET(XML_PARSE_SOURCE            ${XML_ELEMENT_PARSE_KV}
                                    ${XML_ELEMENT_PARSE_CREATER}
                                    ${XML_ELEMENT_PARSE_SOURCE}

                                    ${XML_PARSE_CLASS_SOURCE}
                                    #${TREE_XML_SOURCE}
    )

    SOURCE_GROUP("XML\\ElementParse\\KV" FILES ${XML_ELEMENT_PARSE_KV})
    SOURCE_GROUP("XML\\ElementParse\\Creater" FILES ${XML_ELEMENT_PARSE_CREATER})
    SOURCE_GROUP("XML\\ElementParse" FILES ${XML_ELEMENT_PARSE_SOURCE})
    SOURCE_GROUP("XML\\TreeXML" FILES ${TREE_XML_SOURCE})
    SOURCE_GROUP("XML" FILES ${XML_PARSE_CLASS_SOURCE})

endif(CM_UTIL_SUPPORT_XML)

#################################################################################################### JSON

option(CM_UTIL_SUPPORT_JSON "Build JSON Parse/make module." ON)

IF(CM_UTIL_SUPPORT_JSON)
    find_package(nlohmann_json CONFIG REQUIRED)

    set(JSON_TOOL_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/json/JsonTool.h
                         json/JsonTool.cpp)

    SOURCE_GROUP("JSON" FILES ${JSON_TOOL_SOURCE})
ENDIF(CM_UTIL_SUPPORT_JSON)

#################################################################################################### HASH

option(CM_UTIL_SUPPORT_HASH "Build HASH module" ON)

IF(CM_UTIL_SUPPORT_HASH)

    SET(XXHASH_FILES    hash/xxHash/xxh3.h
                        hash/xxHash/xxhash.h
                        hash/xxHash/xxhash.c)

    SOURCE_GROUP("HASH\\xxHash" FILES ${XXHASH_FILES})

    SET(CITY_HASH_FILES hash/CityHash/CityHashConfig.h
                        hash/CityHash/city.h
                        hash/CityHash/citycrc.h
                        hash/CityHash/city.cc
                        hash/CityHash/CityHash.cpp)

    SOURCE_GROUP("HASH\\CityHash" FILES ${CITY_HASH_FILES})

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
                            hash/sha512.cpp
                            hash/blake3.cpp
                            hash/xxHash3.cpp
                            hash/FNV1a.cpp
                            hash/MurmurHash3.cpp
    )

    SOURCE_GROUP("HASH" FILES ${HASH_HEADER_FILES} ${HASH_SOURCE_FILES})
ENDIF(CM_UTIL_SUPPORT_HASH)

#################################################################################################### CRYPT

SET(CRYPT_HEADER_FILES ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/Crypt.h)

SET(CRYPT_SOURCE_FILES  crypt/aes.cpp
                        crypt/base64.cpp
                        crypt/Overflow.cpp
                        crypt/rc4.cpp
)

SOURCE_GROUP("Crypt" FILES ${CRYPT_HEADER_FILES} ${CRYPT_SOURCE_FILES})

####################################################################################################

SET(CSV_SOURCE  ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/csv/CSVFieldSplite.h
                ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/csv/CSVParse.h
                ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/csv/CSVOutput.h
                ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/csv/CSVOutputStream.h
                csv/CSVOutputStream.cpp)

SOURCE_GROUP("CSV" FILES ${CSV_SOURCE})

SET(CMD_SOURCE  ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/cmd/CmdParse.h
                cmd/CmdParse.cpp)

SOURCE_GROUP("Command Line" FILES ${CMD_SOURCE})

SET(TIME_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/time/Timer.h
                time/Timer.cpp)

SOURCE_GROUP("Time" FILES ${TIME_SOURCE})

SET(DATABLOCK_SOURCE    ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/datablock/DataBlock.h
                        datablock/DataBlock.cpp)

source_group("Data Block" FILES ${DATABLOCK_SOURCE})

SET(CM_SG_GEO_FILES     ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/geo/GeoLocation.h
                        geo/GeoLocation.cpp)

SOURCE_GROUP("Geo" FILES ${CM_SG_GEO_FILES})

add_cm_library(CMUtil "CM"  ${CMUTIL_ROOT_INCLUDE_PATH}
                            ${CMD_SOURCE}
#							${TIME_SOURCE}
#                            ${DATABLOCK_SOURCE}

                            ${XML_PARSE_SOURCE}
                            ${JSON_TOOL_SOURCE}
                            ${CSV_SOURCE}

                            ${XXHASH_FILES}
                            ${CITY_HASH_FILES}
                            ${HASH_HEADER_FILES}
                            ${HASH_SOURCE_FILES}

                            ${CRYPT_HEADER_FILES}
                            ${CRYPT_SOURCE_FILES}

                            ${CM_SG_GEO_FILES}
                           )

if(CM_UTIL_SUPPORT_HASH)
    target_link_libraries(CMUtil PRIVATE blake3)
endif()

if(CM_UTIL_SUPPORT_XML)
    target_link_libraries(CMUtil PRIVATE expat::expat)
endif()

IF(CM_UTIL_SUPPORT_JSON)
    target_link_libraries(CMUtil PRIVATE nlohmann_json::nlohmann_json)
ENDIF(CM_UTIL_SUPPORT_JSON)
