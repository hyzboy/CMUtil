cmake_minimum_required(VERSION 3.0)

project(CMUtil)

include(path_config.cmake)
CMUtilSetup(${CMAKE_CURRENT_SOURCE_DIR})

if(CM_UTIL_SUPPORT_XML)
	add_definitions(-DXML_STATIC)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdpty/expat/expat)
endif()

if(CM_UTIL_SUPPORT_JSON)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdpty/jsoncpp)
endif()

add_subdirectory(${CMUTIL_ROOT_SOURCE_PATH})
