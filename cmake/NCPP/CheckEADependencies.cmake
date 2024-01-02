
message(STATUS "<NCPP::CheckEADependencies> Start checking EA dependencies")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/Utilities/GitHelper)



#####################################################################################
#   Implement EA repo checking with git clone
#####################################################################################
function(NCPP_EARepository_Checkout)   
    cmake_parse_arguments(
        PARGS                                                                                                         # prefix of output variables
        "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
        "NAME;GIT_URL;CUSTOM_DIRECTORY;GIT_COMMIT"      # list of names of mono-valued arguments
        ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )     

    if(PARGS_CUSTOM_DIRECTORY)
        if(NOT EXISTS "${PARGS_CUSTOM_DIRECTORY}/${PARGS_NAME}")
            NCPP_GitHelper_Clone(
                PROJECT_NAME ${PARGS_NAME}
                GIT_URL ${PARGS_GIT_URL}
                GIT_COMMIT ${PARGS_GIT_COMMIT}
                DIRECTORY "${PARGS_CUSTOM_DIRECTORY}"
            )
        endif()
    else()
        if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dependencies/${PARGS_NAME}")
            NCPP_GitHelper_Clone(
                PROJECT_NAME ${PARGS_NAME}
                GIT_URL ${PARGS_GIT_URL}
                GIT_COMMIT ${PARGS_GIT_COMMIT}
                DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies"
            )
        endif()
    endif()
endfunction()



#####################################################################################
#   Download EA repos
#####################################################################################
NCPP_EARepository_Checkout(
    NAME EASTL
    GIT_URL "https://github.com/electronicarts/EASTL.git"
    GIT_COMMIT "05f4b4aef33f2f3ded08f19fa97f5a27ff35ff9f"
)
NCPP_EARepository_Checkout(
    NAME EAStdC
    GIT_URL "https://github.com/electronicarts/EAStdC.git"
    GIT_COMMIT "fbcc34e89c63636054334888f3a5bd7ac2fd4b76"
)
NCPP_EARepository_Checkout(
    NAME EAAssert
    GIT_URL "https://github.com/electronicarts/EAAssert.git"
    GIT_COMMIT "e5e181255de2e883dd1f987c78ccc42ac81d3bca"
)
NCPP_EARepository_Checkout(
    NAME EAThread
    GIT_URL "https://github.com/electronicarts/EAThread.git"
    GIT_COMMIT "b05f3b308a9be1b525f09c79bd66ce8736fe5630"
)

# If EABase is not cloned, delete the empty EABase subdirectory to be cloned next time
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase/CMakeLists.txt")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase")
endif()

NCPP_EARepository_Checkout(
    NAME EABase
    GIT_URL "https://github.com/electronicarts/EABase.git"
    GIT_COMMIT "521cb053d9320636f53226ffc616216cf532f0ef"
    CUSTOM_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages"
)



message(STATUS "<NCPP::CheckEADependencies> Check EA dependencies done")