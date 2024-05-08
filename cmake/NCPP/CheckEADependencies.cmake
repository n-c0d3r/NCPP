
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
    GIT_URL "https://github.com/n-c0d3r/EASTL.git"
    GIT_COMMIT "05f4b4aef33f2f3ded08f19fa97f5a27ff35ff9f"
)
NCPP_EARepository_Checkout(
    NAME EAStdC
    GIT_URL "https://github.com/n-c0d3r/EAStdC.git"
    GIT_COMMIT "5621cd506c78f475f1d5db8a470a7a334939eaa3"
)
NCPP_EARepository_Checkout(
    NAME EAAssert
    GIT_URL "https://github.com/n-c0d3r/EAAssert.git"
    GIT_COMMIT "3f34ff5246614555b4299cee6918a4241ea90aec"
)
NCPP_EARepository_Checkout(
    NAME EAThread
    GIT_URL "https://github.com/n-c0d3r/EAThread.git"
    GIT_COMMIT "80b7a812ed1d4df3535b214b4d64bb916cee9f8b"
)

# If EABase is not cloned, delete the empty EABase subdirectory to be cloned next time
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase/CMakeLists.txt")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages/EABase")
endif()

NCPP_EARepository_Checkout(
    NAME EABase
    GIT_URL "https://github.com/n-c0d3r/EABase.git"
    GIT_COMMIT "a5b5065aba247193b9c5afc9b942ee1f59a21293"
    CUSTOM_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dependencies/EAThread/test/packages"
)



message(STATUS "<NCPP::CheckEADependencies> Check EA dependencies done")