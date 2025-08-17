cmake_minimum_required(VERSION 3.10)

project(CMUtil)

include(path_config.cmake)
CMUtilSetup(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMUTIL_ROOT_SOURCE_PATH})
