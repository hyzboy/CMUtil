option(CM_UTIL_SUPPORT_XML "Build XML Parse module." ON)

if(CM_UTIL_SUPPORT_XML)
    add_subdirectory(xml)
endif(CM_UTIL_SUPPORT_XML)

option(CM_UTIL_SUPPORT_JSON "Build JSON Parse/make module." ON)

if(CM_UTIL_SUPPORT_JSON)
    add_subdirectory(json)
endif(CM_UTIL_SUPPORT_JSON)
