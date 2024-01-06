
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
        "HIDE_NAME_IN_MEMBER_MACROS;NO_VIRTUAL;NO_CONST;NO_STATIC;NO_ABSTRACT;MUST_VIRTUAL;MUST_CONST;MUST_STATIC;MUST_ABSTRACT"
        "NAME;PREFIX;REFLECT;BODY;KEYWORDS;IMPLEMENT"
        "INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
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



    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_OVERRIDER_KEYWORDS_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        BODY "${PARGS_KEYWORDS}"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_OVERRIDER_IMPLEMENT_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName"
        BODY "${PARGS_IMPLEMENT}"
    )



    set(OVERRIDER_NAME_SUFFIX _${PARGS_NAME})

    if(PARGS_HIDE_NAME_IN_MEMBER_MACROS)
        set(OVERRIDER_NAME_SUFFIX "")
    endif()
    if(PARGS_PREFIX)
        set(PARGS_PREFIX "${PARGS_PREFIX}_")
    endif()


    
    # non static
    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
    endif()

    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()

    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
    endif()

    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()

    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
        NCPP_MacroHelper_CreateFunctionMacro(
            NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
            OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
            PARAM_NAMES "MemberType" "MemberName" "..."
            BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
        )
    endif()

    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()



    # virtual
    if(NOT PARGS_NO_VIRTUAL)
        if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC AND NOT PARGS_MUST_ABSTRACT)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_STATIC AND NOT PARGS_MUST_ABSTRACT)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()
    endif()



    # abstract
    if(NOT PARGS_NO_ABSTRACT)
        if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC AND NOT PARGS_MUST_VIRTUAL)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_ABSTRACT${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_ABSTRACT(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()

        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_STATIC AND NOT PARGS_MUST_VIRTUAL)
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )

                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
                NCPP_MacroHelper_CreateFunctionMacro(
                    NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}
                    OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                    PARAM_NAMES "MemberType" "MemberName" "..."
                    BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_ABSTRACT_CONST(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
                )
            endif()
        endif()
    endif()



    # static
    if(NOT PARGS_NO_STATIC)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_CONST)
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )

            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PRIVATE_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PROTECTED_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
            NCPP_MacroHelper_CreateFunctionMacro(
                NAME NCPP_ROBJECT_SINFOS_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
                OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
                PARAM_NAMES "MemberType" "MemberName" "..."
                BODY "NCPP_EXPAND(NCPP_ROBJECT_SINFOS_BASE_PUBLIC_STATIC(${PARGS_NAME}, (), (), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
            )
        endif()
    endif()

endfunction()



function(NCPP_RTTIHelper_RObject_CreateLowLevelMacro)
    
    cmake_parse_arguments(
        PARGS
        ""
        "NAME_AND_PARAMS;REFLECT;BODY;SINFOS"
        "INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    if(NOT PARGS_NAME_AND_PARAMS)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateLowLevelMacro> Require NAME_AND_PARAMS")
    endif()
    
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "\n #define NCPP_ROBJECT_BODY_${PARGS_NAME_AND_PARAMS} ${PARGS_BODY} \n")
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "#define NCPP_ROBJECT_REFLECT_${PARGS_NAME_AND_PARAMS} ${PARGS_REFLECT} \n")
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "#define NCPP_ROBJECT_SINFOS_${PARGS_NAME_AND_PARAMS} ${PARGS_SINFOS} \n")

endfunction()



function(NCPP_RTTIHelper_RObject_CreateHighLevelMacro)

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
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateHighLevelMacro> Require NAME_AND_PARAMS")
    endif()



    set(REFLECT "")
    set(BODY "")
    set(SINFOS "")

    if(PARGS_SINGLE_PART)
        set(REFLECT "${REFLECT} NCPP_EXPAND(NCPP_ROBJECT_REFLECT_${PARGS_SINGLE_PART})\\\;")
        set(BODY "${BODY} NCPP_EXPAND(NCPP_ROBJECT_BODY_${PARGS_SINGLE_PART})\\\;")
        set(SINFOS "${SINFOS} NCPP_EXPAND(NCPP_ROBJECT_SINFOS_${PARGS_SINGLE_PART})")
    else()
        foreach(part ${PARGS_PARTS})
            set(REFLECT "${REFLECT} NCPP_EXPAND(NCPP_ROBJECT_REFLECT_${part})\\\;")
            set(BODY "${BODY} NCPP_EXPAND(NCPP_ROBJECT_BODY_${part})\\\;")
            set(SINFOS "${SINFOS} NCPP_EXPAND(NCPP_ROBJECT_SINFOS_${part})")
        endforeach()
    endif()

    NCPP_RTTIHelper_RObject_CreateLowLevelMacro(
        NAME_AND_PARAMS "${PARGS_NAME_AND_PARAMS}"
        REFLECT "${REFLECT};"
        BODY "${BODY};"
        SINFOS "${SINFOS}"
    )

endfunction()



function(NCPP_RTTIHelper_RObject_CreateMemberMacro)

    cmake_parse_arguments(
        PARGS
        "NO_VIRTUAL;NO_CONST;NO_STATIC;NO_ABSTRACT;MUST_VIRTUAL;MUST_CONST;MUST_STATIC;MUST_ABSTRACT"
        "NAME;PREFIX;KEYWORDS;IMPLEMENT;MEMBER_TYPE;OVERRIDER;MEMBER_NAME"
        "PARAMS;INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    set(OVERRIDER_NAME_SUFFIX _${PARGS_NAME})

    if(NOT PARGS_NAME)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> NAME is required")
    endif()
    if(NOT PARGS_MEMBER_NAME)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> MEMBER_NAME is required")
    endif()
    if(NOT PARGS_MEMBER_TYPE)
        message(FATAL_ERROR "<NCPP_RTTIHelper_RObject_CreateMemberMacro> MEMBER_TYPE is required")
    endif()

    if(PARGS_PREFIX)
        set(PARGS_PREFIX "${PARGS_PREFIX}_")
    endif()



    if(NOT PARGS_OVERRIDER)
        set(PARGS_OVERRIDER "DEFAULT")
    endif()



    string(REPLACE ";" "\\\\\\\\;" PARGS_IMPLEMENT "${PARGS_IMPLEMENT}")



    set(PARGS_PARAMS_STR "")
    if(PARGS_PARAMS)
        string(REPLACE ";" ", " PARGS_PARAMS_STR "${PARGS_PARAMS}")
    endif()



    if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_CONST AND NOT PARGS_MUST_STATIC)
        NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
            NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
            SINGLE_PART "BASE_PRIVATE(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
        )
        NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
            NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
            SINGLE_PART "BASE_PROTECTED(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
        )
        NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
            NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
            SINGLE_PART "BASE_PUBLIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
        )
    endif()
    if(NOT PARGS_NO_CONST)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
    endif()
    if(NOT PARGS_NO_VIRTUAL)
        if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_VIRTUAL(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_VIRTUAL(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_VIRTUAL(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_ABSTRACT AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_VIRTUAL_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_VIRTUAL_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_VIRTUAL_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
    endif()
    if(NOT PARGS_NO_ABSTRACT)
        if(NOT PARGS_MUST_CONST AND NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_ABSTRACT${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_ABSTRACT(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_ABSTRACT${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_ABSTRACT(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_ABSTRACT${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_ABSTRACT(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
        if(NOT PARGS_NO_CONST)
            if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_STATIC)
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PRIVATE_ABSTRACT_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PROTECTED_ABSTRACT_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
                NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                    NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_ABSTRACT_CONST${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                    SINGLE_PART "BASE_PUBLIC_ABSTRACT_CONST(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
                )
            endif()
        endif()
    endif()
    if(NOT PARGS_MUST_STATIC)
        if(NOT PARGS_MUST_VIRTUAL AND NOT PARGS_MUST_ABSTRACT AND  NOT PARGS_MUST_CONST)
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PRIVATE_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PROTECTED_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
            NCPP_RTTIHelper_RObject_CreateHighLevelMacro(
                NAME_AND_PARAMS "${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}(${PARGS_PARAMS_STR})"
                SINGLE_PART "BASE_PUBLIC_STATIC(${PARGS_OVERRIDER}, (${PARGS_KEYWORDS}), (${PARGS_IMPLEMENT}), ${PARGS_MEMBER_TYPE}, ${PARGS_MEMBER_NAME} __VA_OPT__(,) __VA_ARGS__)"
            )
        endif()
    endif()

endfunction()