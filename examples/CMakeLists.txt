# CMUtil Examples
# Lightweight wrapper for cm_example_project with module-specific settings

macro(cm_example_project sub_folder project_name)
    cm_example_project_base(
        PROJECT_NAME ${project_name}
        FOLDER_PATH "Examples/CMUtil/${sub_folder}"
        SOURCES ${ARGN}
        PRIVATE_LIBRARIES CMUtil
    )
endmacro()

cm_example_project("" PAttribTest      PAttribTest.cpp)
cm_example_project("" Base64Test       base64test.cpp)
cm_example_project("" HashTest         HashTest.cpp)
