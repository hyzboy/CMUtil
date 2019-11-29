set(JSON_TOOL_HEADER_FILES ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/json/JsonTool.h)

set(JSON_TOOL_SOURCE_FILES JsonTool.cpp)
SOURCE_GROUP("JSON" FILES JsonTool.cpp)

IF(WIN32)
    SET(JSONCPP_PATH ${CMUTIL_ROOT_3RDPTY_PATH}/jsoncpp)

    include_directories(${JSONCPP_PATH}/include)
    include_directories(${JSONCPP_PATH}/src/lib_json)

    SET(JSONCPP_SOURCE  ${JSONCPP_PATH}/src/lib_json/json_reader.cpp
                        ${JSONCPP_PATH}/src/lib_json/json_value.cpp
                        ${JSONCPP_PATH}/src/lib_json/json_writer.cpp)

    SET(JSON_TOOL_SOURCE_FILES ${JSON_TOOL_SOURCE_FILES} ${JSONCPP_SOURCE})

    SOURCE_GROUP("JSON\\jsoncpp" FILES ${JSONCPP_SOURCE})
ENDIF(WIN32)

add_cm_library(CMUtil.JSON "CM/Util"	${JSON_TOOL_HEADER_FILES}
                                        ${JSON_TOOL_SOURCE_FILES})
