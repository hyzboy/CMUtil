macro(CMUtilSetup source_path)

    message("CMUTIL_ROOT_PATH: " ${source_path})

    set(CMUTIL_ROOT_INCLUDE_PATH    ${source_path}/inc)
    set(CMUTIL_ROOT_SOURCE_PATH     ${source_path}/src)

    set(CMUTIL_ROOT_3RDPTY_PATH     ${source_path}/3rdpty)

    include_directories(${CMUTIL_ROOT_INCLUDE_PATH})
endmacro()
