
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
#   Default member overrider
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMemberOverrider(
    NAME DEFAULT
    HIDE_NAME_IN_MEMBER_MACROS
    REFLECT ";"
    BODY ";"
)



#####################################################################################
#   Body-only macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "BONLY(...)"
    REFLECT ";"
    BODY "__VA_ARGS__;"
)
#####################################################################################
#   Reflect-only macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "RONLY(...)"
    REFLECT "__VA_ARGS__;"
    BODY ";"
)



#####################################################################################
#   _ macro
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "_(...)"
    REFLECT ";"
    BODY "__VA_ARGS__;"
)



#####################################################################################
#   Getter macros
#####################################################################################
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, false)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PRIVATE_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PRIVATE_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, false)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PROTECTED_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PROTECTED_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, false)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PUBLIC_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, false)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "GETTER_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, true)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() const { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PRIVATE_GETTER_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PRIVATE_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, true)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() const { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PROTECTED_GETTER_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PROTECTED_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, true)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() const { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PUBLIC_GETTER_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, false, true)\\\; \\
        NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() const { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "GETTER_VIRTUAL(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, false)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PRIVATE_GETTER_VIRTUAL(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PRIVATE_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, false)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PROTECTED_GETTER_VIRTUAL(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PROTECTED_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, false)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PUBLIC_GETTER_VIRTUAL(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, false)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "GETTER_VIRTUAL_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, true)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PRIVATE_GETTER_VIRTUAL_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PRIVATE_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, true)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PROTECTED_GETTER_VIRTUAL_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PROTECTED_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, true)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PUBLIC_GETTER_VIRTUAL_CONST(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName, true, true)\\\; \\
        virtual ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "STATIC_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName)\\\; \\
        static NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PRIVATE_STATIC_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PRIVATE_KEYWORD \\
        NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName)\\\; \\
        static NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PROTECTED_STATIC_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PROTECTED_KEYWORD \\
        NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName)\\\; \\
        static NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)
NCPP_RTTIHelper_RObject_CreateMacro(
    NAME_AND_PARAMS "PUBLIC_STATIC_GETTER(GetterName, MemberName, ...)"
    REFLECT "NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(DEFAULT, (ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName __VA_OPT__(,) __VA_ARGS__))"
    BODY "NCPP_PUBLIC_KEYWORD \\
        NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO((ncpp::containers::TF_view<decltype(MemberName)>)(), GetterName)\\\; \\
        static NCPP_FORCE_INLINE ncpp::containers::TF_view<decltype(MemberName)> GetterName() { return MemberName\\\; }
    "
)



message(STATUS "<NCPP::RTTIMacros> Build rtti macros done")