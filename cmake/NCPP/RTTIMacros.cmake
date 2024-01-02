
message(STATUS "<NCPP::RTTIMacros> Start generating rtti macros")



include(NCPP/Utilities/RTTIHelper)



#####################################################################################
#   Setup NCPP_RTTI_MACROS_FILE
#####################################################################################
file(WRITE ${NCPP_RTTI_MACROS_FILE} "\n
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

    FUNCTION_ONLY
)
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME "FORCE_INLINE"

    REFLECT ";"
    BODY ";"

    KEYWORDS "NCPP_FORCE_INLINE"

    FUNCTION_ONLY
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
    MEMBER_RETURN_TYPE "ncpp::containers::TF_view<decltype(MemberName)>"

    FUNCTION_ONLY

    IMPLEMENT "{ return MemberName\\\; }"
)



#####################################################################################
#   Setter macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMemberMacro(
    NAME "SETTER"
    PARAMS "SetterName" "MemberName" "..."

    OVERRIDER FORCE_INLINE

    MEMBER_NAME "SetterName"
    MEMBER_RETURN_TYPE "void"
    MEMBER_ARG_TYPES "ncpp::containers::TF_view<decltype(MemberName)> value"

    FUNCTION_ONLY

    IMPLEMENT "{ MemberName = value\\\; }"

    NO_CONST
)



message(STATUS "<NCPP::RTTIMacros> Build rtti macros done")