
message(STATUS "<NCPP::RTTIMacros> Start generating rtti macros")



include(NCPP/Utilities/RTTIHelper)



#####################################################################################
#   Setup NCPP_RTTI_MACROS_FILE
#####################################################################################
file(WRITE ${NCPP_RTTI_MACROS_FILE} "\n
    #pragma once
    #include <ncpp/prerequisites.hpp>\n
"
)



#####################################################################################
#   Member overriders
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME "DEFAULT"

    HIDE_NAME_IN_MEMBER_MACROS

    REFLECT ";"
    BODY ";"
)
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME "INLINE"

    REFLECT ";"
    BODY ";"

    KEYWORDS "inline"
)
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME "FORCE_INLINE"

    REFLECT ";"
    BODY ";"

    KEYWORDS "NCPP_FORCE_INLINE"
)
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME "CONSTEXPR"

    REFLECT ";"
    BODY ";"

    KEYWORDS "constexpr"

    NO_VIRTUAL
    NO_ABSTRACT
    NO_CONST
)



#####################################################################################
#   Body-only macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateLowLevelMacro(
    NAME_AND_PARAMS "BONLY(...)"
    REFLECT ";"
    BODY "__VA_ARGS__;"
)
#####################################################################################
#   Reflect-only macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateLowLevelMacro(
    NAME_AND_PARAMS "RONLY(...)"
    REFLECT "__VA_ARGS__;"
    BODY ";"
)



#####################################################################################
#   _ macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateLowLevelMacro(
    NAME_AND_PARAMS "_(...)"
    REFLECT ";"
    BODY "__VA_ARGS__;"
)



#####################################################################################
#   Getter macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMemberMacro(
    NAME "GETTER"
    PARAMS "GetterName" "MemberName" "..."

    OVERRIDER FORCE_INLINE

    MEMBER_NAME "GetterName"
    MEMBER_TYPE "(ncpp::utilities::TF_cpass<decltype(MemberName)>)()"

    IMPLEMENT "{ return MemberName\\\; }"

    NO_ABSTRACT
)
NCPP_RTTIHelper_RObject_CreateMemberMacro(
    NAME "GETTER_NOEXCEPT"
    PARAMS "GetterName" "MemberName" "..."

    OVERRIDER FORCE_INLINE

    MEMBER_NAME "GetterName"
    MEMBER_TYPE "(ncpp::utilities::TF_cpass<decltype(MemberName)>)()"

    IMPLEMENT "noexcept { return MemberName\\\; }"

    NO_ABSTRACT
)



#####################################################################################
#   Setter macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMemberMacro(
    NAME "SETTER"
    PARAMS "SetterName" "MemberName" "..."

    OVERRIDER FORCE_INLINE

    MEMBER_NAME "SetterName"
    MEMBER_TYPE "()(ncpp::utilities::TF_cpass<decltype(MemberName)> value)"

    IMPLEMENT "{ MemberName = value\\\; }"

    NO_CONST
    NO_ABSTRACT
)
NCPP_RTTIHelper_RObject_CreateMemberMacro(
    NAME "SETTER_NOEXCEPT"
    PARAMS "SetterName" "MemberName" "..."

    OVERRIDER FORCE_INLINE

    MEMBER_NAME "SetterName"
    MEMBER_TYPE "()(ncpp::utilities::TF_cpass<decltype(MemberName)> value)"

    IMPLEMENT "noexcept { MemberName = value\\\; }"

    NO_CONST
    NO_ABSTRACT
)



message(STATUS "<NCPP::RTTIMacros> Build rtti macros done")