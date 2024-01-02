
include(NCPP/Utilities/SetGlobal)
include(NCPP/Utilities/ApplyGlobal)
include(NCPP/Utilities/MacroHelper)



function(NCPP_VersionHelper_CreateVersionMacros)

    cmake_parse_arguments(
        PARGS
        "QUIET"
        "PROJECT_NAME;OUTPUT_FILE;MAJOR;MINOR;PATCH;MAX_COMPONENT_VALUE"
        ""
        ${ARGN}
    )

    if(NOT PARGS_MAJOR)
        set(PARGS_MAJOR 0)
    endif()
    if(NOT PARGS_MINOR)
        set(PARGS_MINOR 0)
    endif()
    if(NOT PARGS_PATCH)
        set(PARGS_PATCH 0)
    endif()
    if(NOT PARGS_MAX_COMPONENT_VALUE)
        set(PARGS_MAX_COMPONENT_VALUE 99)
    endif()

    math(EXPR version_number "${PARGS_MAJOR} * (${PARGS_MAX_COMPONENT_VALUE} + 1) * (${PARGS_MAX_COMPONENT_VALUE} + 1) + ${PARGS_MINOR} * (${PARGS_MAX_COMPONENT_VALUE} + 1) + ${PARGS_PATCH}")    

    if(PARGS_PROJECT_NAME)
        if(PARGS_OUTPUT_FILE)
            file(WRITE "${PARGS_OUTPUT_FILE}" "")

            # Apply variables
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_MAJOR ${PARGS_MAJOR})
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_MAINOR ${PARGS_MINOR})
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_PATCH ${PARGS_PATCH})
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION ${PARGS_MAJOR}.${PARGS_MINOR}.${PARGS_PATCH})
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_STR "\"${PARGS_MAJOR}.${PARGS_MINOR}.${PARGS_PATCH}\"")
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_NUMBER ${version_number})
            NCPP_SetGlobal(${PARGS_PROJECT_NAME}_VERSION_MAX_COMPONENT_VALUE ${PARGS_MAX_COMPONENT_VALUE})

            # Create macros
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION_MAJOR
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${PARGS_MAJOR}
            )
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION_MAINOR
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${PARGS_MINOR}
            )
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION_PATCH
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${PARGS_PATCH}
            )
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${${PARGS_PROJECT_NAME}_VERSION}
            )
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION_STR
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${${PARGS_PROJECT_NAME}_VERSION_STR}
            )
            NCPP_MacroHelper_CreateObjectMacro(
                NAME ${PARGS_PROJECT_NAME}_VERSION_NUMBER
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                BODY ${version_number}
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME ${PARGS_PROJECT_NAME}_ANOTHER_VERSION_NUMBER
                OUTPUT_FILE "${PARGS_OUTPUT_FILE}"
                PARAM_NAMES 
                    "MAJOR"
                    "MINOR"
                    "PATCH"
                BODY 
                    "((MAJOR * (${PARGS_MAX_COMPONENT_VALUE} + 1) * (${PARGS_MAX_COMPONENT_VALUE} + 1)) + MINOR * ((${PARGS_MAX_COMPONENT_VALUE} + 1)) + PATCH)"
            )
        else()
            message(FATAL_ERROR "Cant create version macros without OUTPUT_FILE")
        endif()  
    else()
        message(FATAL_ERROR "Cant create version macros without PROJECT_NAME")
    endif()   

endfunction()
