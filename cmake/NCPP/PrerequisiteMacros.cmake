
message(STATUS "<NCPP::PrerequisiteMacros> Start building prerequisite macro")



include(NCPP/Utilities/MacroHelper)



set(NCPP_PREREQUISITE_MACROS_FILE_PATH "${NCPP_GENERATED_FILES_DIR}/prerequisite_macros.hpp")

file(WRITE ${NCPP_PREREQUISITE_MACROS_FILE_PATH} "\n")



function(NCPP_PrerequisiteMacros_Create_NARGS MaxArgCount)

    set(PARAM_NAMES "")
    foreach(i RANGE 1 ${MaxArgCount})
        list(APPEND PARAM_NAMES "_${i}")
    endforeach()
    
    list(APPEND PARAM_NAMES "N")
    list(APPEND PARAM_NAMES "...")



    set(BODY "__VA_ARGS__ __VA_OPT__(,)")
    foreach(i RANGE ${MaxArgCount} 0)
        set(BODY "${BODY} ${i}")
        if(i GREATER 0)
            set(BODY "${BODY},")
        endif()
    endforeach()

    set(BODY "NCPP_EXPAND(NCPP_NARGS_IMPL(${BODY}))")

    

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_NARGS_IMPL
        OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
        PARAM_NAMES ${PARAM_NAMES}
        BODY "N"       
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_NARGS
        OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
        PARAM_NAMES "..."
        BODY ${BODY}
    )
    
endfunction()

function(NCPP_PrerequisiteMacros_Create_NTH_ARG MaxArgCount)

    foreach(index RANGE 1 ${MaxArgCount})
        set(PARAM_NAMES "")
        foreach(i RANGE 1 ${index})
            list(APPEND PARAM_NAMES "V${i}")
        endforeach()

        list(APPEND PARAM_NAMES "...")

        NCPP_MacroHelper_CreateFunctionMacro(
            NAME "NCPP_NTH_ARG_${index}"
            OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
            PARAM_NAMES ${PARAM_NAMES}
            BODY "NCPP_EXPAND(V${index})"        
        )
    endforeach()
    

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_NTH_ARG
        OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
        PARAM_NAMES 
            "I"
            "..."
        BODY "NCPP_EXPAND(NCPP_EXPAND(NCPP_NTH_ARG_ ## I)( __VA_ARGS__))"
    )
    
endfunction()

function(NCPP_PrerequisiteMacros_Create_FOR_EACH MaxArgCount)

    foreach(index RANGE 0 ${MaxArgCount})
        set(BODY "")

        if(${index} GREATER 0)
            foreach(i RANGE 1 ${index})
                set(BODY "${BODY} NCPP_EXPAND(STEP_MACRO_NAME(${i}, NCPP_EXPAND(NCPP_NTH_ARG(${i} __VA_OPT__(,) __VA_ARGS__))))")
            endforeach()
        endif()

        NCPP_MacroHelper_CreateFunctionMacro(
            NAME "NCPP_FOR_EACH_STEPS_${index}"
            OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
            PARAM_NAMES 
                "STEP_MACRO_NAME" 
                "..."
            BODY ${BODY}
        )
    endforeach()
    

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_FOR_EACH
        OUTPUT_FILE ${NCPP_PREREQUISITE_MACROS_FILE_PATH}
        PARAM_NAMES 
            "STEP_MACRO_NAME" 
            "..."
        BODY "NCPP_EXPAND(NCPP_GLUE(NCPP_FOR_EACH_STEPS_, NCPP_EXPAND(NCPP_NARGS( __VA_ARGS__)))(STEP_MACRO_NAME __VA_OPT__(,) __VA_ARGS__))"        
    )
    
endfunction()



NCPP_PrerequisiteMacros_Create_NARGS(63)

NCPP_PrerequisiteMacros_Create_NTH_ARG(63)

NCPP_PrerequisiteMacros_Create_FOR_EACH(63)



message(STATUS "<NCPP::PrerequisiteMacros> Build prerequisite macro done")