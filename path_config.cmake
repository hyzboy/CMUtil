macro(CMUtilSetup CMUTIL_ROOT_PATH)
    message("CMUtil root path: " ${CMUTIL_ROOT_PATH})

    set(CMUTIL_ROOT_INCLUDE_PATH ${CMUTIL_ROOT_PATH}/inc)
    set(CMUTIL_ROOT_SOURCE_PATH ${CMUTIL_ROOT_PATH}/src)
    set(CMUTIL_ROOT_3RDPTY_PATH ${CMUTIL_ROOT_PATH}/3rdpty)

    include_directories(${CMUTIL_ROOT_INCLUDE_PATH})
endmacro()

