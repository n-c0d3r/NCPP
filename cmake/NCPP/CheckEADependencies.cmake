
message(STATUS "<NCPP::CheckEADependencies> Start checking EA dependencies")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/GitUtils)



#####################################################################################
#   Implement EA repo checking with git clone
#####################################################################################
function(NCPP_EARepository_Checkout)   
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;GIT_URL;CUSTOM_DIRECTORY"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(PARGS_CUSTOM_DIRECTORY)
        NCPP_GitClone(
            PROJECT_NAME ${PARGS_NAME}
            GIT_URL ${PARGS_GIT_URL}
            GIT_BRANCH "master"
            DIRECTORY "${PARGS_CUSTOM_DIRECTORY}"
        )
    else()
        NCPP_GitClone(
            PROJECT_NAME ${PARGS_NAME}
            GIT_URL ${PARGS_GIT_URL}
            GIT_BRANCH "master"
            DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies"
        )
    endif()
endfunction()



#####################################################################################
#   Download EA repos
#####################################################################################
NCPP_EARepository_Checkout(
    NAME EASTL
    GIT_URL "https://github.com/electronicarts/EASTL.git"
)
NCPP_EARepository_Checkout(
    NAME EAStdC
    GIT_URL "https://github.com/electronicarts/EAStdC.git"
)
NCPP_EARepository_Checkout(
    NAME EAAssert
    GIT_URL "https://github.com/electronicarts/EAAssert.git"
)
NCPP_EARepository_Checkout(
    NAME EAThread
    GIT_URL "https://github.com/electronicarts/EAThread.git"
)

# If EABase is not cloned, delete the empty EABase subdirectory to be cloned next time
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase/CMakeLists.txt")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase")
endif()

NCPP_EARepository_Checkout(
    NAME EABase
    GIT_URL "https://github.com/electronicarts/EABase.git"
    CUSTOM_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages"
)



message(STATUS "<NCPP::CheckEADependencies> Check EA dependencies done")