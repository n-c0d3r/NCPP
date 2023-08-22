
message(STATUS "NCPP Check EA dependencies")



include(GitUtils)



set(BUILD_DEPENDENCIES_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if(NOT EXISTS ${BUILD_DEPENDENCIES_DIRECTORY})
    file(MAKE_DIRECTORY ${BUILD_DEPENDENCIES_DIRECTORY})
endif()

function(EARepository_Download)   
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;GIT_URL;CUSTOM_DIRECTORY"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(PARGS_CUSTOM_DIRECTORY)
        git_clone(
            PROJECT_NAME ${PARGS_NAME}
            GIT_URL ${PARGS_GIT_URL}
            GIT_BRANCH "master"
            DIRECTORY "${PARGS_CUSTOM_DIRECTORY}"
        )
        set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PARGS_CUSTOM_DIRECTORY}/${PARGS_NAME}/scripts/CMake" PARENT_SCOPE)
    else()
        git_clone(
            PROJECT_NAME ${PARGS_NAME}
            GIT_URL ${PARGS_GIT_URL}
            GIT_BRANCH "master"
            DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies"
        )
        set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}/scripts/CMake" PARENT_SCOPE)
    endif()
endfunction()

function(EARepository_Add)    
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;GIT_URL"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(NOT TARGET ${PARGS_NAME})
        add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}")
    endif()
endfunction()



# Download EA repositories
EARepository_Download(
    NAME EASTL
    GIT_URL "https://github.com/electronicarts/EASTL.git"
)
EARepository_Download(
    NAME EAStdC
    GIT_URL "https://github.com/electronicarts/EAStdC.git"
)
EARepository_Download(
    NAME EAAssert
    GIT_URL "https://github.com/electronicarts/EAAssert.git"
)
EARepository_Download(
    NAME EAThread
    GIT_URL "https://github.com/electronicarts/EAThread.git"
)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase/CMakeLists.txt")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase")
endif()

EARepository_Download(
    NAME EABase
    GIT_URL "https://github.com/electronicarts/EABase.git"
    CUSTOM_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages"
)



# Add EA repositories as sub directories
EARepository_Add(
    NAME EAThread
)
EARepository_Add(
    NAME EASTL
)
EARepository_Add(
    NAME EAStdC
)
EARepository_Add(
    NAME EAAssert
)


# Setup folder
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

message(STATUS "NCPP Check EA dependencies done")