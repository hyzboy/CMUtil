cmake_minimum_required(VERSION 3.28)

project(CMUtil LANGUAGES C CXX)

include(path_config.cmake)
CMUtilSetup(${CMAKE_CURRENT_SOURCE_DIR})

# 添加 BLAKE3 库
if(CMAKE_VERSION VERSION_LESS 3.25)
    set(BLAKE3_TESTING OFF CACHE BOOL "Build BLAKE3 tests" FORCE)
    set(BLAKE3_EXAMPLES OFF CACHE BOOL "Build BLAKE3 examples" FORCE)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdpty/BLAKE3/c)

add_subdirectory(${CMUTIL_ROOT_SOURCE_PATH})

add_subdirectory(examples)
