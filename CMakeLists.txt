cmake_minimum_required(VERSION 3.12)



#####################################################################################
#   Project NCPP
#####################################################################################
project(ncpp)



#####################################################################################
#   IDE configs
#####################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



#####################################################################################
#   CMake module
#####################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")



#####################################################################################
#   Build options
#####################################################################################
set(CMAKE_BUILD_PARALLEL_LEVEL 4)



#####################################################################################
#   Global variables
#####################################################################################
include(NCPP/Utilities/SetGlobal)
NCPP_SetGlobal(NCPP_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
NCPP_SetGlobal(NCPP_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
NCPP_SetGlobal(NCPP_SCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/scripts")
NCPP_SetGlobal(NCPP_SUBMODULES_DIR "${CMAKE_CURRENT_LIST_DIR}/submodules")
NCPP_SetGlobal(NCPP_CMAKE_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake")
NCPP_SetGlobal(NCPP_DEPENDENCIES_DIR "${CMAKE_CURRENT_BINARY_DIR}/dependencies")
NCPP_SetGlobal(NCPP_GENERATED_FILES_DIR "${CMAKE_CURRENT_BINARY_DIR}/ncpp/generated_files/ncpp")

if(NCPP_LITE) # <REPLACER::NCPP_LITE>. Replaced to ON in generated lite distribution
    NCPP_SetGlobal(NCPP_LITE ON)
else()
    NCPP_SetGlobal(NCPP_LITE OFF)
endif()



#####################################################################################
#   Version
#####################################################################################
include(NCPP/Utilities/VersionHelper)
NCPP_VersionHelper_CreateVersionMacros(
    PROJECT_NAME NCPP
    OUTPUT_FILE "${NCPP_GENERATED_FILES_DIR}/version.hpp"
    MAJOR 0
    MINOR 9
    PATCH 0
)



#####################################################################################
#   Check and configure dependencies
#####################################################################################
include(NCPP/CheckDependencies)

include(NCPP/ConfigureDependencies)



#####################################################################################
#   Create documentations target
#####################################################################################
option(NCPP_ENABLE_DOCUMENTATIONS "If enabled, creating a target being capable of generating documentations" OFF)
NCPP_SetGlobal(
    NCPP_DOCUMENTATIONS_PREDEFINED
    "NCPP_WINDOWS_PLATFORM NCPP_UNIX_PLATFORM NCPP_ENABLE_RTTI NCPP_ENABLE_METADATA"
)
if(NCPP_ENABLE_DOCUMENTATIONS)
    option(NCPP_INTERNAL_DOCS "Generate docs for anything" OFF)

    include(NCPP/Utilities/DocsHelper)

    NCPP_DocsHelper_CreateTarget(
        NAME NCPP
        BRIEF "Ncoder's Game Engine Learning Aimed C++ Library."

        TARGET_NAME ncpp.documentations
        TARGET_FOLDER ncpp
        TARGET_LABEL documentations

        INPUT_DIRS 
            "${CMAKE_CURRENT_SOURCE_DIR}/ncpp/source"
            "${CMAKE_CURRENT_SOURCE_DIR}/documentations"
            "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
        STYLE_DIRS
            "${CMAKE_CURRENT_SOURCE_DIR}/documentations/styles"
        OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/documentations"
        CWD "${CMAKE_CURRENT_SOURCE_DIR}"
        INTERNAL_DOCS ${NCPP_INTERNAL_DOCS}

        PREDEFINED ${NCPP_DOCUMENTATIONS_PREDEFINED}

        MAIN_PAGE "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
    )
endif()



#####################################################################################
#   Add main directory
#####################################################################################
add_subdirectory(ncpp)



include(CPack)