
include(NCPP/Utilities/MacroHelper)



set(NCPP_RTTI_MACROS_FILE "${NCPP_GENERATED_FILES_DIR}/rtti_macros.hpp")



function(NCPP_RTTIHelper_AddIncludes)

    cmake_parse_arguments(
        PARGS
        ""
        ""
        "INCLUDES"
        ${ARGN}
    )

    set(content "\n")

    message(${PARGS_INCLUDES})

    foreach(includePath ${PARGS_INCLUDES})
        set(content "${content} #include ${includePath} \n ")
    endforeach()

    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "${content}")

endfunction()



function(NCPP_RTTIHelper_RObject_CreateMemberOverrider)
    
    cmake_parse_arguments(
        PARGS
        "HIDE_NAME_IN_MEMBER_MACROS;FUNCTION_ONLY;VARIABLE_ONLY;NO_VIRTUAL;NO_CONST;NO_STATIC;MUST_VIRTUAL;MUST_CONST;MUST_STATIC"
        "NAME;PREFIX;REFLECT;BODY;KEYWORDS;IMPLEMENT"
        "INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    set(PARGS_IMPLEMENT_FUNCTION "${PARGS_IMPLEMENT}")
    set(PARGS_IMPLEMENT_VARIABLE "${PARGS_IMPLEMENT}")

    if(PARGS_VARIABLE_ONLY AND PARGS_FUNCTION_ONLY)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberOverrider> FUNCTION_ONLY and VARIABLE_ONLY can't be used together")
    endif()



    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_BODY_OVERRIDER_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName"
        BODY ${PARGS_BODY}
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_REFLECT_OVERRIDER_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName"
        BODY ${PARGS_REFLECT}
    )



    set(OVERRIDER_NAME_SUFFIX _${PARGS_NAME})

    if(PARGS_HIDE_NAME_IN_MEMBER_MACROS)
        set(OVERRIDER_NAME_SUFFIX "")
    endif()
    if(PARGS_PREFIX)
        set(PARGS_PREFIX "${PARGS_PREFIX}_")
    endif()


    
    # non static
    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
    endif()

    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()

    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
    endif()

    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()

    if(NOT PARGS_NO_VIRTUAL)
        if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_STATIC)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()
    endif()



    # static
    if(NOT PARGS_NO_STATIC)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()



    if(NOT PARGS_VARIABLE_ONLY)
        # non static
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()

        if(NOT PARGS_NO_VIRTUAL)
            if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()

            if(NOT PARGS_NO_CONST)
                if(NOT PARGS_MUST_STATIC)
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                endif()
            endif()
        endif()
#abc
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()

        if(NOT PARGS_NO_VIRTUAL)
            if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()

            if(NOT PARGS_NO_CONST)
                if(NOT PARGS_MUST_STATIC)
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                    NCPP_MacroHelper_CreateFunctionMacro(
                        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
                        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                    )
                endif()
            endif()
        endif()



        # static
        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()
    endif()



    if(NOT PARGS_FUNCTION_ONLY)
        # non static
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()



        # static
        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()
    endif()

endfunction()



function(NCPP_RTTIHelper_RObject_CreateMacro)
    
    cmake_parse_arguments(
        PARGS
        ""
        "NAME_AND_PARAMS;REFLECT;BODY"
        "INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    if(NOT PARGS_NAME_AND_PARAMS)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMacro> Require NAME_AND_PARAMS")
    endif()
    
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "\n #define NCPP_ROBJECT_BODY_${PARGS_NAME_AND_PARAMS} ${PARGS_BODY} \n")
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "\n #define NCPP_ROBJECT_REFLECT_${PARGS_NAME_AND_PARAMS} ${PARGS_REFLECT} \n")

endfunction()



function(NCPP_RTTIHelper_RObject_CreateNestedMacro)

    cmake_parse_arguments(
        PARGS
        ""
        "NAME_AND_PARAMS"
        "PARTS;SINGLE_PART;INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    if(NOT PARGS_NAME_AND_PARAMS)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateNestedMacro> Require NAME_AND_PARAMS")
    endif()



    set(REFLECT "")
    set(BODY "")

    if(PARGS_SINGLE_PART)
        set(REFLECT "${REFLECT} NCPP_EXPAND(NCPP_ROBJECT_REFLECT_${PARGS_SINGLE_PART})\\\;")
        set(BODY "${BODY} NCPP_EXPAND(NCPP_ROBJECT_BODY_${PARGS_SINGLE_PART})\\\;")
    else()
        foreach(part ${PARGS_PARTS})
            set(REFLECT "${REFLECT} NCPP_EXPAND(NCPP_ROBJECT_REFLECT_${part})\\\;")
            set(BODY "${BODY} NCPP_EXPAND(NCPP_ROBJECT_BODY_${part})\\\;")
        endforeach()
    endif()

    NCPP_RTTIHelper_RObject_CreateMacro(
        NAME_AND_PARAMS "${PARGS_NAME_AND_PARAMS}"
        REFLECT "${REFLECT};"
        BODY "${BODY};"
    )

endfunction()



function(NCPP_RTTIHelper_RObject_CreateMemberMacro)

    cmake_parse_arguments(
        PARGS
        "FUNCTION_ONLY;VARIABLE_ONLY;NO_VIRTUAL;NO_CONST;NO_STATIC;MUST_VIRTUAL;MUST_CONST;MUST_STATIC"
        "NAME;PREFIX;KEYWORDS;IMPLEMENT;MEMBER_TYPE;MEMBER_RETURN_TYPE;OVERRIDER;MEMBER_NAME_PARAM"
        "PARAMS;MEMBER_ARG_TYPES;INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    set(OVERRIDER_NAME_SUFFIX _${PARGS_NAME})

    if(NOT PARGS_NAME)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> NAME is required")
    endif()
    if(NOT PARGS_MEMBER_NAME_PARAM)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> MEMBER_NAME_PARAM is required")
    endif()

    if(PARGS_PREFIX)
        set(PARGS_PREFIX "${PARGS_PREFIX}_")
    endif()



    if(NOT PARGS_OVERRIDER)
        set(PARGS_OVERRIDER "DEFAULT")
    endif()



    string(REPLACE ";" "\\\\\\\\;" PARGS_IMPLEMENT "${PARGS_IMPLEMENT}")



    set(PARGS_IMPLEMENT_FUNCTION "${PARGS_IMPLEMENT}")
    set(PARGS_IMPLEMENT_VARIABLE "${PARGS_IMPLEMENT}")

    if(PARGS_VARIABLE_ONLY AND PARGS_FUNCTION_ONLY)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> FUNCTION_ONLY and VARIABLE_ONLY can't be used together")
    endif()



    set(PARGS_MEMBER_ARG_TYPES_STR "")
    if(PARGS_MEMBER_RETURN_TYPE AND NOT PARGS_MEMBER_TYPE)
        string(REPLACE ";" ", " PARGS_MEMBER_ARG_TYPES_STR "${PARGS_MEMBER_ARG_TYPES}")
        set(PARGS_MEMBER_TYPE "${PARGS_MEMBER_RETURN_TYPE}(${PARGS_MEMBER_ARG_TYPES_STR})")
    endif()

    set(PARGS_PARAMS_STR "")
    if(PARGS_PARAMS)
        string(REPLACE ";" ", " PARGS_PARAMS_STR "${PARGS_PARAMS}")
    endif()



    if(NOT PARGS_FUNCTION_ONLY)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()

        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()

        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()

        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_STATIC_VARIABLE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_STATIC_VARIABLE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_STATIC_VARIABLE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
    else()
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
        if(NOT PARGS_NO_VIRTUAL)
            if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
            if(NOT PARGS_NO_CONST)
                if(NOT PARGS_MUST_STATIC)
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PRIVATE_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PROTECTED_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PUBLIC_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                endif()
            endif()
        endif()
        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
    endif()

    if(NOT PARGS_VARIABLE_ONLY)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateNestedMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
        if(NOT PARGS_NO_VIRTUAL)
            if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_VIRTUAL_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
            if(NOT PARGS_NO_CONST)
                if(NOT PARGS_MUST_STATIC)
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PRIVATE_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PROTECTED_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                    NCPP_RTTIHelper_RObject_CreateNestedMacro(
                        NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                        SINGLE_PART "BASE_PUBLIC_VIRTUAL_CONST_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                    )
                endif()
            endif()
        endif()
        if(NOT PARGS_NO_STATIC)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_CONST)
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateNestedMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_STATIC_FUNCTION(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), (${PARGS_MEMBER_RETURN_TYPE}), (${PARGS_MEMBER_ARG_TYPES_STR}), ${PARGS_MEMBER_NAME_PARAM} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
    endif()

endfunction()