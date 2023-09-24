
message(STATUS "<NCPP::Dependencies> Start configuring EA dependencies")



include(NCPP/GitUtils)



set(BUILD_DEPENDENCIES_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if(NOT EXISTS ${BUILD_DEPENDENCIES_DIRECTORY})
    file(MAKE_DIRECTORY ${BUILD_DEPENDENCIES_DIRECTORY})
endif()



#####################################################################################
#   Setup EA cmake modules
#####################################################################################
function(NCPP_EARepository_Decl)   
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;CUSTOM_DIRECTORY"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(PARGS_CUSTOM_DIRECTORY)
        set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PARGS_CUSTOM_DIRECTORY}/${PARGS_NAME}/scripts/CMake" PARENT_SCOPE)
    else()
        set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}/scripts/CMake" PARENT_SCOPE)
    endif()
endfunction()

#####################################################################################
#   Implement EA repo subdirectory adding
#####################################################################################
function(NCPP_EARepository_Add)    
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;GIT_URL"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(NOT TARGET ${PARGS_NAME})
        add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}" "${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}")
    endif()
endfunction()



#####################################################################################
#   Declare EA repos
#####################################################################################
NCPP_EARepository_Decl(
    NAME EASTL
)
NCPP_EARepository_Decl(
    NAME EAStdC
)
NCPP_EARepository_Decl(
    NAME EAAssert
)
NCPP_EARepository_Decl(
    NAME EAThread
)

NCPP_EARepository_Decl(
    NAME EABase
    CUSTOM_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages"
)



#####################################################################################
#   Add EA repos
#####################################################################################
NCPP_EARepository_Add(
    NAME EAThread
)
NCPP_EARepository_Add(
    NAME EASTL
)
NCPP_EARepository_Add(
    NAME EAStdC
)
NCPP_EARepository_Add(
    NAME EAAssert
)



#####################################################################################
#   Add all EA targets into EA folder
#####################################################################################
set_target_properties(EABase
    PROPERTIES 
        FOLDER "EA"
)
set_target_properties(EAThread
    PROPERTIES 
        FOLDER "EA"
)
set_target_properties(EASTL
    PROPERTIES 
        FOLDER "EA"
)
set_target_properties(EAStdC
    PROPERTIES 
        FOLDER "EA"
)
set_target_properties(EAAssert
    PROPERTIES 
        FOLDER "EA"
)



message(STATUS "<NCPP::Dependencies> Configure EA dependencies done")