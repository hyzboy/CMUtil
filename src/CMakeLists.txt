option(CM_UTIL_SUPPORT_XML "Build XML Parse module." ON)

if(CM_UTIL_SUPPORT_XML)
    add_subdirectory(xml)
endif(CM_UTIL_SUPPORT_XML)

option(CM_UTIL_SUPPORT_JSON "Build JSON Parse/make module." ON)

if(CM_UTIL_SUPPORT_JSON)
    add_subdirectory(json)
endif(CM_UTIL_SUPPORT_JSON)

SET(CMD_SOURCE  ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/cmd/CmdParse.h
                cmd/CmdParse.cpp)

#SET(TIME_SOURCE ${CMUTIL_ROOT_INCLUDE_PATH}/hgl/util/time/Timer.h
#                time/Timer.cpp)

SOURCE_GROUP("Command Line" FILES ${CMD_SOURCE})
#SOURCE_GROUP("Time" FILES ${TIME_SOURCE})

add_cm_library(CMUtil "CM/Util" ${CMD_SOURCE} 
#								${TIME_SOURCE}
								)
