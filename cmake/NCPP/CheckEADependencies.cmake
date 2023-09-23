
message(STATUS "<NCPP::Dependencies> Start checking EA dependencies")



include(NCPP/GitUtils)



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
    else()
        git_clone(
            PROJECT_NAME ${PARGS_NAME}
            GIT_URL ${PARGS_GIT_URL}
            GIT_BRANCH "master"
            DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies"
        )
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



message(STATUS "<NCPP::Dependencies> Check EA dependencies done")