


function(NCPP_MacroHelper_CreateFunctionMacro)

    cmake_parse_arguments(
        PARGS
        "QUIET"
        "NAME;OUTPUT_FILE;BODY"
        "PARAM_NAMES"
        ${ARGN}
    )

    if(NOT EXISTS ${PARGS_OUTPUT_FILE})
        file(WRITE ${PARGS_OUTPUT_FILE} "\n")
    endif()    
    
    # Create the macro
    set(MACRO_STRING "#define ${PARGS_NAME}(")

    if(PARGS_PARAM_NAMES)
        foreach(PARAM_NAME ${PARGS_PARAM_NAMES})
            set(MACRO_STRING "${MACRO_STRING}${PARAM_NAME}, ")
        endforeach()
        string(REGEX REPLACE ", $" ")" MACRO_STRING "${MACRO_STRING}")
    else()
        set(MACRO_STRING "${MACRO_STRING})")
    endif()

    set(MACRO_STRING "${MACRO_STRING} ${PARGS_BODY}\n")

    # Append the macro to the output file
    file(APPEND ${PARGS_OUTPUT_FILE} "${MACRO_STRING}")
        
endfunction()



function(NCPP_MacroHelper_CreateObjectMacro)

    cmake_parse_arguments(
        PARGS
        "QUIET"
        "NAME;OUTPUT_FILE;BODY"
        ""
        ${ARGN}
    )

    if(NOT EXISTS ${PARGS_OUTPUT_FILE})
        file(WRITE ${PARGS_OUTPUT_FILE} "\n")
    endif()    
    
    # Create the macro
    set(MACRO_STRING "#define ${PARGS_NAME} ${PARGS_BODY}\n")

    # Append the macro to the output file
    file(APPEND ${PARGS_OUTPUT_FILE} "${MACRO_STRING}")
        
endfunction()
