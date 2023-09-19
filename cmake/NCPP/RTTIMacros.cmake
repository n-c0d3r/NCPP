
message(STATUS "<NCPP::RTTIMacros> Start building rtti macros")



include(NCPP/MacroHelper)



set(NCPP_RTTI_MACROS_FILE "${NCPP_GENERATED_FILES_DIR}/rtti_macros.h")

file(WRITE ${NCPP_RTTI_MACROS_FILE} "\n")



function(NCPP_RTTIMacros_CreateMemberOverrider)
    
    cmake_parse_arguments(
        PARGS
        "QUIET;HIDE_NAME_IN_MEMBER_MACROS"
        "NAME;REFLECT;BODY"
        ""
        ${ARGN}
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_BODY_OVERRIDER_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName"
        BODY ${PARGS_REFLECT}
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_MEMBER_BODY_OVERRIDER_${PARGS_NAME}
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName"
        BODY ${PARGS_BODY}
    )



    set(OVERRIDER_NAME_PREFIX _${PARGS_NAME})

    if(PARGS_HIDE_NAME_IN_MEMBER_MACROS)
        set(OVERRIDER_NAME_PREFIX "")
    endif()


    
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PRIVATE
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PROTECTED
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PUBLIC
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PRIVATE_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PROTECTED_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_BODY${OVERRIDER_NAME_PREFIX}_PUBLIC_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PRIVATE
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PROTECTED
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PUBLIC
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PRIVATE_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PROTECTED_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )
    NCPP_MacroHelper_CreateFunctionMacro(
        NAME NCPP_ROBJECT_REFLECT${OVERRIDER_NAME_PREFIX}_PUBLIC_CONST
        OUTPUT_FILE "${NCPP_RTTI_MACROS_FILE}"
        PARAM_NAMES "MemberType" "MemberName" "..."
        BODY "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(${PARGS_NAME}, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))"
    )

endfunction()



NCPP_RTTIMacros_CreateMemberOverrider(
    NAME DEFAULT
    HIDE_NAME_IN_MEMBER_MACROS
    REFLECT ";"
    BODY ";"
)



message(STATUS "<NCPP::RTTIMacros> Build rtti macros done")