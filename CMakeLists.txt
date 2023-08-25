cmake_minimum_required(VERSION 3.12)



include(cmake/Version.cmake)



project(ncpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)



set(NCPP_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")



set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#Dependencies
option(NCPP_CHECK_DEPENDENCIES "If enabled, it will automatically check the dependencies each time generating project" ON)
if(${NCPP_CHECK_DEPENDENCIES})
    include(CheckDependencies)
endif()

include(ConfigureDependencies)

#Documentations
option(NCPP_ENABLE_DOCUMENTATIONS "If enabled, creating a target being capable of generating documentations" OFF)
if(NCPP_ENABLE_DOCUMENTATIONS)
    option(NCPP_INTERNAL_DOCS "Generate docs for anything" OFF)

    include(DocsUtils)

    DocsUtils_CreateTarget(
        NAME NCPP
        BRIEF "Ncoder's Game Engine Learning Aimed C++ Library."

        TARGET_NAME ncpp.documentations
        TARGET_FOLDER ncpp
        TARGET_LABEL documentations

        INPUT_DIRS 
            "${CMAKE_CURRENT_SOURCE_DIR}/ncpp/source"
            "${CMAKE_CURRENT_SOURCE_DIR}/documentations"
        STYLE_DIRS
            "${CMAKE_CURRENT_SOURCE_DIR}/documentations/styles"
        OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/documentations"
        CWD "${CMAKE_CURRENT_SOURCE_DIR}"
        INTERNAL_DOCS ${NCPP_INTERNAL_DOCS}

        MAIN_PAGE "${CMAKE_CURRENT_SOURCE_DIR}/documentations/Overview.md"
    )
endif()




add_subdirectory(ncpp)



include(CPack)