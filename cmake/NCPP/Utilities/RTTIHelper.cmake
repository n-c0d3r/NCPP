
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



function(NCPP_Utilities_RTTIHelper_RObject_CreateMemberOverrider)
    
    cmake_parse_arguments(
        PARGS
        "HIDE_NAME_IN_MEMBER_MACROS"
        "NAME;PREFIX;REFLECT;BODY;KEYWORDS"
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



    set(OVERRIDER_NAME_SUFFIX _${PARGS_NAME})

    if(PARGS_HIDE_NAME_IN_MEMBER_MACROS)
        set(OVERRIDER_NAME_SUFFIX "")
    endif()
    if(PARGS_PREFIX)
        set(PARGS_PREFIX "${PARGS_PREFIX}_")
    endif()


    
    # non static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )



    # static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )



    # non static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )



    # static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC_FUNCTION(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberReturnType, MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC_FUNCTION${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberReturnType" "MemberArgs" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, MemberReturnType MemberArgs, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )



    # non static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_VIRTUAL_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_VIRTUAL_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_VIRTUAL_CONST_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )



    # static
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PRIVATE_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PROTECTED_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY_${PARGS_PREFIX}PUBLIC_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(${PARGS_NAME}, (${PARGS_KEYWORDS}), MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PRIVATE_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PROTECTED_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT_${PARGS_PREFIX}PUBLIC_STATIC_VARIABLE${OVERRIDER_NAME_SUFFIX}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

endfunction()



function(NCPP_Utilities_RTTIHelper_RObject_CreateMacro)
    
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
        message(FATAL_ERROR "<NCPP_Utilities_RTTIHelper_RObject_CreateMacro> Require NAME_AND_PARAMS")
    endif()
    
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "\n #define NCPP_ROBJECT_BODY_${PARGS_NAME_AND_PARAMS} ${PARGS_BODY} \n")
    file(APPEND "${NCPP_RTTI_MACROS_FILE}" "\n #define NCPP_ROBJECT_REFLECT_${PARGS_NAME_AND_PARAMS} ${PARGS_REFLECT} \n")

endfunction()



function(NCPP_Utilities_RTTIHelper_RObject_CreateNestedMacro)

    cmake_parse_arguments(
        PARGS
        ""
        "NAME_AND_PARAMS"
        "PARTS;INCLUDES"
        ${ARGN}
    )



    if(PARGS_INCLUDES)
        NCPP_RTTIHelper_AddIncludes(INCLUDES ${PARGS_INCLUDES})
    endif()



    if(NOT PARGS_NAME_AND_PARAMS)
        message(FATAL_ERROR "<NCPP_Utilities_RTTIHelper_RObject_CreateNestedMacro> Require NAME_AND_PARAMS")
    endif()



    set(REFLECT "")
    set(BODY "")

    foreach(part ${PARGS_PARTS})
        set(REFLECT "${REFLECT} NCPP_ROBJECT_REFLECT_${part}\\\;")
        set(BODY "${BODY} NCPP_ROBJECT_BODY_${part}\\\;")
    endforeach()

    set(REFLECT "${REFLECT}\n")
    set(BODY "${BODY}\n")

    NCPP_Utilities_RTTIHelper_RObject_CreateMacro(
        NAME_AND_PARAMS "${PARGS_NAME_AND_PARAMS}"
        REFLECT "${REFLECT};"
        BODY "${BODY};"
    )

endfunction()