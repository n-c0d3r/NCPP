
function(xor result)
    set(true_args_count 0)

    foreach(foo ${ARGN})
        if(foo)
            math(EXPR true_args_count "${true_args_count}+1")
        endif()
    endforeach()

    if(NOT (${true_args_count} EQUAL 1))
        set(${result} FALSE PARENT_SCOPE)
    else()
        set(${result} TRUE PARENT_SCOPE)
    endif()
endfunction()

function(at_most_one result)
    set(true_args_count 0)

    foreach(foo ${ARGN})
        if(foo)
            math(EXPR true_args_count "${true_args_count}+1")
        endif()
    endforeach()

    if(${true_args_count} GREATER 1)
        set(${result} FALSE PARENT_SCOPE)
    else()
        set(${result} TRUE PARENT_SCOPE)
    endif()
endfunction()



include(CMakeParseArguments)

find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "git not found!")
endif()



function(NCPP_GitHelper_Clone)

    cmake_parse_arguments(
            PARGS                                                                                                         # prefix of output variables
            "QUIET"                                                                                                       # list of names of the boolean arguments (only defined ones will be true)
            "PROJECT_NAME;GIT_URL;GIT_TAG;GIT_BRANCH;GIT_COMMIT;DIRECTORY"      # list of names of mono-valued arguments
            ""                                                                                                            # list of names of multi-valued arguments (output variables are lists)
            ${ARGN}                                                                                                       # arguments of the function to parse, here we take the all original ones
    )
    set(USE_GIT_BRANCH OFF)# remaining unparsed arguments can be found in PARGS_UNPARSED_ARGUMENTS
    if(NOT PARGS_GIT_BRANCH)
        set(PARGS_GIT_BRANCH "master")
    else()
        set(USE_GIT_BRANCH ON)
    endif()
                                                                                                                 # remaining unparsed arguments can be found in PARGS_UNPARSED_ARGUMENTS
    if(NOT PARGS_PROJECT_NAME)
        message(FATAL_ERROR "You must provide a project name")
    endif()

    if(NOT PARGS_GIT_URL)
        message(FATAL_ERROR "You must provide a git url")
    endif()

    if(NOT PARGS_DIRECTORY)
        set(PARGS_DIRECTORY ${CMAKE_BINARY_DIR})
    endif()

    if(NOT PARGS_QUIET)
        message(STATUS "downloading/updating ${PARGS_PROJECT_NAME}")
    endif()

    # first clone the repo
    if(NOT PARGS_QUIET)
        message(STATUS "${PARGS_PROJECT_NAME} directory not found, cloning...")
    endif()

    if(PARGS_GIT_BRANCH)
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} clone -b ${PARGS_GIT_BRANCH} ${PARGS_GIT_URL}
            WORKING_DIRECTORY   ${PARGS_DIRECTORY}
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output
        )
    else()
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} clone ${PARGS_GIT_URL}
            WORKING_DIRECTORY   ${PARGS_DIRECTORY}
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output
        )
    endif()

    if(NOT git_result EQUAL "0")
        if(NOT PARGS_QUIET)
            message(WARNING "${PARGS_PROJECT_NAME} clone error ${git_result}")  #ToDo: maybe FATAL_ERROR?
        endif()
        return()
    endif()

    if(NOT PARGS_QUIET)
        message(STATUS "${git_output}")
    endif()



    # now checkout the right commit
    if(PARGS_GIT_TAG)
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} fetch --all --tags --prune
            COMMAND             ${GIT_EXECUTABLE} checkout tags/${PARGS_GIT_TAG} -b tag_${PARGS_GIT_TAG}
            WORKING_DIRECTORY   "${PARGS_DIRECTORY}/${PARGS_PROJECT_NAME}"
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output)
    elseif(PARGS_GIT_COMMIT)
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} checkout ${PARGS_GIT_COMMIT}
            WORKING_DIRECTORY   "${PARGS_DIRECTORY}/${PARGS_PROJECT_NAME}"
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output)
    elseif(USE_GIT_BRANCH)
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} checkout ${PARGS_GIT_BRANCH}
            WORKING_DIRECTORY   "${PARGS_DIRECTORY}/${PARGS_PROJECT_NAME}"
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output)
    else()
        if(NOT PARGS_QUIET)
            message(STATUS "no tag specified, defaulting to ${PARGS_GIT_BRANCH}")
        endif()
        execute_process(
            COMMAND             ${GIT_EXECUTABLE} checkout "${PARGS_GIT_BRANCH}"
            WORKING_DIRECTORY   "${PARGS_DIRECTORY}/${PARGS_PROJECT_NAME}"
            RESULT_VARIABLE     git_result
            OUTPUT_VARIABLE     git_output)
    endif()
    if(NOT git_result EQUAL "0")
        if(NOT PARGS_QUIET)
            message(WARNING "${PARGS_PROJECT_NAME} some error happens. ${git_output}")  #ToDo: maybe FATAL_ERROR?
        endif()
        return()
    endif()
    if(NOT PARGS_QUIET)
        message(STATUS "${git_output}")
    endif()
endfunction()
