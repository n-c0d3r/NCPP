#pragma once

/** @file ncpp/rtti/robject.hpp
*	@brief Implements reflected object.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/iostream.hpp>
#include <ncpp/utilities/is_function.hpp>
#include <ncpp/utilities/cpass.hpp>
#include <ncpp/utilities/magic.hpp>
#include <ncpp/utilities/smart_cast_member.hpp>
#include <ncpp/utilities/template_targ_list.hpp>
#include <ncpp/utilities/try_class.hpp>

#include <ncpp/containers/.hpp>

#include <ncpp/object.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/traits.hpp>
#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/rtti/robject_flag.hpp>
#include <ncpp/rtti/security_helper.hpp>
#include <ncpp/rtti/accessibility.hpp>

#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

	namespace rtti {

#define NCPP_ROBJECT_USER_REFLECT_CUSTOM_PARAMS(CustomParamsType) \
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_user_reflect_custom_params_flag, CustomParamsType);



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_USER_PRE_REFLECT_MEMBER(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_pre_reflect_member_flag \
        );\
		template<class F_robject__, typename F_member__, class F_member_sinfo__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_pre_reflect_member( \
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			F_robject_member_info__* robject_member_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER() F_rtti_traits::template T_safe_user_pre_reflect_member<\
			F_reflect_flag__,\
			F_this,\
			F_member,\
			F_member_sinfo\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			robject_member_info_p,\
			custom_params_p\
		);

#define NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_post_reflect_member_flag \
        );\
		template<class F_robject__, typename F_member__, class F_member_sinfo__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_post_reflect_member( \
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			F_robject_member_info__* robject_member_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER() F_rtti_traits::template T_safe_user_post_reflect_member<\
			F_reflect_flag__,\
			F_this,\
			F_member,\
			F_member_sinfo\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			robject_member_info_p,\
			custom_params_p\
		);



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_USER_PRE_REFLECT_BASE(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_pre_reflect_base_flag \
        );\
		template<class F_robject__, class F_base__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_pre_reflect_base(\
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_PRE_REFLECT_BASE() F_rtti_traits::template T_safe_user_pre_reflect_base<\
			F_reflect_flag__,\
			F_this,\
			F_base\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			custom_params_p\
		);

#define NCPP_ROBJECT_USER_POST_REFLECT_BASE(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_post_reflect_base_flag \
        );\
		template<class F_robject__, class F_base__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_post_reflect_base(\
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			F_robject_type_info__* base_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_POST_REFLECT_BASE() F_rtti_traits::template T_safe_user_post_reflect_base<\
			F_reflect_flag__,\
			F_this,\
			F_base\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			base_info_p,\
			custom_params_p\
		);



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_USER_PRE_REFLECT_OBJECT(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_pre_reflect_object_flag \
        );\
		template<class F_robject__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_pre_reflect_object(\
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_PRE_REFLECT_OBJECT() F_rtti_traits::template T_safe_user_pre_reflect_object<\
			F_reflect_flag__,\
			F_this\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			custom_params_p\
		);

#define NCPP_ROBJECT_USER_POST_REFLECT_OBJECT(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            ncpp::rtti::F_user_post_reflect_object_flag \
        );\
		template<class F_robject__, NCPP_RTTI_SPECIFIC_TARGS()>\
		static NCPP_FORCE_INLINE void T_user_post_reflect_object(\
			F_rcontainer__* rcontainer_p, \
			F_robject_type_info__* robject_type_info_p,\
			ncpp::rtti::F_default_rtti_traits::template TF_safe_custom_params<NCPP_MA(__VA_ARGS__)>* custom_params_p = 0\
		)

#define NCPP_ROBJECT_CALL_USER_POST_REFLECT_OBJECT() F_rtti_traits::template T_safe_user_post_reflect_object<\
			F_reflect_flag__,\
			F_this\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			custom_params_p\
		);



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        namespace internal {

            template<typename F__>
            struct TF_member_safe_type_wrapper_helper {
                using F = F__;
                TF_member_safe_type_wrapper_helper(auto...) {}
            };

            template<typename F__>
            struct TF_member_safe_type_parse_helper;

            template<typename F__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>> {
                using F = F__;
            };

            template<typename F__, sz N__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>[N__]> {
                using F = F__[N__];
            };
            template<typename F_return__, typename... F_args__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F_return__>(F_args__...)> {
                using F = F_return__(F_args__...);
            };

            template<typename F__, sz N__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>(*)[N__]> {
                using F_data = F__[N__];
                using F = F_data*;
            };
            template<typename F_return__, typename... F_args__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F_return__>(*)(F_args__...)> {
                using F_data = F_return__(F_args__...);
                using F = F_data*;
            };

            template<typename F__, sz N__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>(&)[N__]> {
                using F_data = F__[N__];
                using F = F_data&;
            };
            template<typename F_return__, typename... F_args__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F_return__>(&)(F_args__...)> {
                using F_data = F_return__(F_args__...);
                using F = F_data&;
            };

            template<typename F__, sz N__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>(&&)[N__]> {
                using F_data = F__[N__];
                using F = F_data&&;
            };
            template<typename F_return__, typename... F_args__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F_return__>(&&)(F_args__...)> {
                using F_data = F_return__(F_args__...);
                using F = F_data&&;
            };

            template<typename F__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>*> {
                using F_data = F__;
                using F = F_data*;
            };
            template<typename F__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>&> {
                using F_data = F__;
                using F = F_data&;
            };
            template<typename F__>
            struct TF_member_safe_type_parse_helper<TF_member_safe_type_wrapper_helper<F__>&&> {
                using F_data = F__;
                using F = F_data&&;
            };

        };



#define NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, IsVirtualFunction, IsConstFunction, LowKeywords, LowImplement) \
            struct ___F_##MemberName##___ncpp_member_##IsVirtualFunction##_##IsConstFunction##___;\
            friend struct ___F_##MemberName##___ncpp_member_##IsVirtualFunction##_##IsConstFunction##___;\
            struct ___F_##MemberName##___ncpp_member_##IsVirtualFunction##_##IsConstFunction##___ {                                                           \
                LowKeywords                                                                                                                                   \
                ncpp::rtti::internal::TF_member_safe_type_wrapper_helper<NCPP_MAGIC_FIRST_TYPE(MemberMagicType)> MemberMagicName NCPP_MAGIC_SECOND_PART(MemberMagicType)\
                LowImplement;                                                                      \
            };

#define NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE(MemberName, IsVirtualFunction, IsConstFunction) \
            typename ncpp::rtti::internal::TF_member_safe_type_parse_helper<                                                                                \
                ncpp::utilities::TF_smart_cast_member<                                          \
                    decltype(&___F_##MemberName##___ncpp_member_##IsVirtualFunction##_##IsConstFunction##___::MemberName) \
                >\
            >::F

#define NCPP_ROBJECT_DECLARE_STATIC_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName) \
            struct ___F_##MemberName##___ncpp_member_static___;\
            friend struct ___F_##MemberName##___ncpp_member_static___;\
            struct ___F_##MemberName##___ncpp_member_static___ {                                      \
                ncpp::rtti::internal::TF_member_safe_type_wrapper_helper<NCPP_MAGIC_FIRST_TYPE(MemberMagicType)> MemberMagicName NCPP_MAGIC_SECOND_PART(MemberMagicType);\
            };

#define NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE(MemberName) \
            typename ncpp::rtti::internal::TF_member_safe_type_parse_helper<                                                                                \
                ncpp::utilities::TF_smart_cast_member<         \
                    decltype(&___F_##MemberName##___ncpp_member_static___::MemberName) \
                >\
            >::F



#define NCPP_ROBJECT_MEMBER_SINFO(MemberName, IsVirtualFunction, IsConstFunction) \
			___TF_##MemberName##___ncpp_sinfo___<                                                             \
				F_this,                                                                              \
				NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE(MemberName, IsVirtualFunction, IsConstFunction), \
				ncpp::utilities::T_is_function<                                                      \
					NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE(MemberName, IsVirtualFunction, IsConstFunction) \
				>, \
				IsVirtualFunction,                                                               \
				IsConstFunction                                                                  \
			>

#define NCPP_ROBJECT_STATIC_MEMBER_SINFO(MemberName) \
			___TF_##MemberName##___ncpp_sinfo___<                                \
				F_this,                                                 \
				NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE(MemberName), \
				ncpp::utilities::T_is_function<                         \
					NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE(MemberName) \
				>                                                   \
			>


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_BODY_OVERRIDER_##Overrider)(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);
#define NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_REFLECT_OVERRIDER_##Overrider)(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_OVERRIDER_KEYWORDS_##Overrider)()
#define NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_OVERRIDER_IMPLEMENT_##Overrider)(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName)



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_WRAP_TYPE(Type) ncpp::utilities::TF_first_template_targ<Type>
#define NCPP_ROBJECT_SAFE_FUNC_WRAP_TYPE(Type) ncpp::utilities::TF_nth_template_targ<ncpp::utilities::T_is_function<Type>, Type, NCPP_ROBJECT_WRAP_TYPE(Type)*>



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_BODY_METADATA(...) ;

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) \
            NCPP_EXPAND(NCPP_MA Keywords) __VA_ARGS__ Inputs NCPP_EXPAND(NCPP_MA Implement)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) NCPP_PRIVATE_KEYWORD \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) NCPP_PROTECTED_KEYWORD \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) NCPP_PUBLIC_KEYWORD \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_BASE(...) \
            template<typename F_robject__, typename F_base__>\
			struct ___TF_base___ncpp_sinfo___;                                                       \
            template<typename F_robject__, typename F_base__>\
			friend struct ___TF_base___ncpp_sinfo___;\
			template<typename F_robject__>\
			struct ___TF_base___ncpp_sinfo___<F_robject__, __VA_ARGS__>                            \
            { \
                using F_base = __VA_ARGS__;                  \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_flag);                        \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_base_flag);                        \
            };

#define NCPP_ROBJECT_BODY_EXTENDS(...) NCPP_ROBJECT_BODY_BASE(__VA_ARGS__)

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_VIRTUAL \
			NCPP_PRIVATE_KEYWORD NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_robject_virtual_flag);\
			NCPP_PUBLIC_KEYWORD virtual F_robject_type_info* virtual_reflect(\
					F_rcontainer* rcontainer_p, \
                    void* custom_params_p = 0\
				) {\
					return F_this::static_reflect(rcontainer_p, custom_params_p);\
				}

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, IsVirtualFunction, IsConstFunction, IsAbstractFunction, Accessibility) \
			template<typename F_robject__, typename F_member__, bool is_function__, bool is_virtual__, bool is_const__>\
			struct ___TF_##MemberName##___ncpp_sinfo___;                                                       \
            template<typename F_robject__, typename F_member__, bool is_function__, bool is_virtual__, bool is_const__>\
			friend struct ___TF_##MemberName##___ncpp_sinfo___;\
			template<typename F_robject__, typename F_member__>\
			struct ___TF_##MemberName##___ncpp_sinfo___<F_robject__, F_member__, false, IsVirtualFunction, IsConstFunction>{\
				\
            NCPP_PUBLIC_KEYWORD\
				\
				using F_member = F_member__;\
				\
				static NCPP_FORCE_INLINE void invoke(void* object_p = 0){}\
				\
				static NCPP_FORCE_INLINE ncpp::sz function_address(){ return 0; }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberMagicType, ""); }\
				static constexpr ncpp::u64 id() { return ncpp::utilities::T_type_hash_code<___TF_##MemberName##___ncpp_sinfo___>; }\
				\
				static NCPP_FORCE_INLINE auto&& variable(F_this* obj) { return obj->MemberName; }\
				static constexpr ncpp::sz variable_getter_address() { return reinterpret_cast<ncpp::sz>(&variable); }\
                static constexpr ncpp::u16 size() { return (ncpp::u16)ncpp::utilities::T_sizeof<F_member>; }\
				\
				static constexpr bool is_static() { return false; }\
				static NCPP_FORCE_INLINE int static_get() { return 0; }\
                \
                static constexpr ncpp::b8 is_function() { return false; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
                static constexpr ncpp::b8 is_abstract_function() { return false; }\
				static constexpr ncpp::b8 is_const_function() { return false; }                                                     \
                                                                                                                        \
				static constexpr ncpp::rtti::E_accessibility accessibility() { return Accessibility; }\
				\
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_flag);                                                                         \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_member_flag);                                                                  \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_variable_flag);                                                                \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PRIVATE, ncpp::rtti::F_sinfo_private_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PROTECTED, ncpp::rtti::F_sinfo_protected_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PUBLIC, ncpp::rtti::F_sinfo_public_flag>)                                      \
                );                                  \
                                                                                                                        \
			};\
			\
            template<typename F_robject__, typename return_type__, typename... arg_types__>\
			struct ___TF_##MemberName##___ncpp_sinfo___<F_robject__, return_type__(arg_types__...), true, IsVirtualFunction, IsConstFunction>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = return_type__(arg_types__...);\
				\
				static NCPP_FORCE_INLINE return_type__ invoke(arg_types__... args, void* object_p = 0) {\
					\
					return reinterpret_cast<F_this*>(object_p)->MemberName(std::forward<arg_types__>(args)...);\
					\
				}\
				\
				static NCPP_FORCE_INLINE ncpp::sz function_address(){ return reinterpret_cast<ncpp::sz>(&invoke); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberMagicType, ""); }\
				static constexpr ncpp::u64 id() { return ncpp::utilities::T_type_hash_code<___TF_##MemberName##___ncpp_sinfo___>; }\
				\
				static constexpr ncpp::sz variable_getter_address() { return 0; }\
				static constexpr ncpp::u16 size() { return 0; }\
				\
				static constexpr bool is_static() { return false; }\
				static NCPP_FORCE_INLINE int static_get() { return 0; }\
                \
                static constexpr ncpp::b8 is_function() { return true; }\
                static constexpr ncpp::b8 is_virtual_function() { return IsVirtualFunction; }\
                static constexpr ncpp::b8 is_abstract_function() { return IsAbstractFunction; }\
                static constexpr ncpp::b8 is_const_function() { return IsConstFunction; }\
                                                                                                                        \
				static constexpr ncpp::rtti::E_accessibility accessibility() { return Accessibility; }\
				\
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_flag);                                                                         \
                                                                                                                                            \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_member_flag);                                                                  \
                                                                                                                                            \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_function_flag);                                                                \
                                                                                                                                            \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PRIVATE, ncpp::rtti::F_sinfo_private_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PROTECTED, ncpp::rtti::F_sinfo_protected_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PUBLIC, ncpp::rtti::F_sinfo_public_flag>)                                      \
                );                                                                                                                          \
                                                                                                                                            \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<IsVirtualFunction, ncpp::rtti::F_sinfo_virtual_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<IsConstFunction, ncpp::rtti::F_sinfo_const_flag>)                                          \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<IsAbstractFunction, ncpp::rtti::F_sinfo_abstract_flag>)                                          \
                );                                  \
				\
			};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, false, false,,);                                                 \
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement);\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, false, false, false, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, false, false)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, false, true,,);                                                 \
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) const NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement);\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, false, true, false, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, false, true)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, true, false,,);                                                 \
			virtual NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement);\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, true, false, false, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, false)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, true, true,,);                                                 \
			virtual NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) const NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement);\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, true, true, false, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, true)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, true, false,,);                                                 \
			virtual NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement) = 0;\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, true, false, true, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, false)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName, true, true,,);                                                 \
			virtual NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) const NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement) = 0;\
            NCPP_ROBJECT_BODY_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, true, false, true, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, true)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_STATIC_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility) \
			template<typename F_robject__, typename F_member__, bool is_function__>\
			struct ___TF_##MemberName##___ncpp_sinfo___;\
			template<typename F_robject__, typename F_member__, bool is_function__>\
			friend struct ___TF_##MemberName##___ncpp_sinfo___;\
			template<typename F_robject__, typename F_member__>\
			struct ___TF_##MemberName##___ncpp_sinfo___<F_robject__, F_member__, false>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
				\
				static NCPP_FORCE_INLINE void invoke(void* object_p = 0){}\
				\
				static NCPP_FORCE_INLINE ncpp::sz function_address(){ return reinterpret_cast<ncpp::sz>(&F_this::MemberName); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberMagicType, ""); }\
				static constexpr ncpp::u64 id() { return ncpp::utilities::T_type_hash_code<___TF_##MemberName##___ncpp_sinfo___>; }\
				\
				static NCPP_FORCE_INLINE auto&& variable() { return F_this::MemberName; }\
				static constexpr ncpp::sz variable_getter_address() { return reinterpret_cast<ncpp::sz>(&variable); }\
                static constexpr ncpp::u16 size() { return (ncpp::u16)ncpp::utilities::T_sizeof<F_member>; }\
				\
				static constexpr bool is_static() { return true; }\
				static NCPP_FORCE_INLINE auto&& static_get() { return F_this::MemberName; }\
                \
                static constexpr ncpp::b8 is_function() { return false; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
                static constexpr ncpp::b8 is_abstract_function() { return false; }\
				static constexpr ncpp::b8 is_const_function() { return false; }\
                                                                                                                        \
				static constexpr ncpp::rtti::E_accessibility accessibility() { return Accessibility; }\
				\
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_flag);                        \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_member_flag);                 \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_variable_flag);               \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_static_flag);                 \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PRIVATE, ncpp::rtti::F_sinfo_private_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PROTECTED, ncpp::rtti::F_sinfo_protected_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PUBLIC, ncpp::rtti::F_sinfo_public_flag>)                                      \
                );                                  \
				\
			};\
			\
			template<typename F_robject__, typename return_type__, typename... arg_types__>\
			struct ___TF_##MemberName##___ncpp_sinfo___<F_robject__, return_type__(arg_types__...), true>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
				\
				static NCPP_FORCE_INLINE return_type__ invoke(arg_types__... args, void* object_p = 0) {\
					\
					return F_this::MemberName(std::forward<arg_types__>(args)...);\
					\
				}\
				\
				static NCPP_FORCE_INLINE ncpp::sz function_address(){ return reinterpret_cast<ncpp::sz>(&invoke); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberMagicType, ""); }\
				static constexpr ncpp::u64 id() { return ncpp::utilities::T_type_hash_code<___TF_##MemberName##___ncpp_sinfo___>; }\
				\
				static constexpr ncpp::sz variable_getter_address() { return 0; }\
				static constexpr ncpp::u16 size() { return 0; }\
				\
				static constexpr bool is_static() { return true; }\
				static NCPP_FORCE_INLINE auto* static_get() { return &F_this::MemberName; }\
                \
                static constexpr ncpp::b8 is_function() { return true; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
                static constexpr ncpp::b8 is_abstract_function() { return false; }\
                static constexpr ncpp::b8 is_const_function() { return false; }\
                                                                                                                        \
				static constexpr ncpp::rtti::E_accessibility accessibility() { return Accessibility; }\
				\
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_flag);                        \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_member_flag);                 \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_function_flag);               \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_sinfo_static_flag);                 \
                \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PRIVATE, ncpp::rtti::F_sinfo_private_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PROTECTED, ncpp::rtti::F_sinfo_protected_flag>)                                      \
                );                                  \
                NCPP_RTTI_IMPLEMENT_FLAG(                                                                                                   \
                    NCPP_MA(ncpp::utilities::TF_try_class<Accessibility == ncpp::rtti::E_accessibility::PUBLIC, ncpp::rtti::F_sinfo_public_flag>)                                      \
                );                                  \
				\
			};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_STATIC_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_ROBJECT_DECLARE_STATIC_MEMBER_TYPE_WRAPPER(MemberMagicType, MemberMagicName, MemberName);                                                 \
			static NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberMagicType, (MemberMagicName)) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName) NCPP_EXPAND(NCPP_MA Implement);\
			NCPP_ROBJECT_BODY_STATIC_MEMBER_SINFO(MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility);\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);

#define NCPP_ROBJECT_BODY_STATIC_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName, Accessibility,...) \
            NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE (MemberName)), MemberName, Accessibility __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PRIVATE __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PROTECTED __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName), ncpp::rtti::E_accessibility::PUBLIC __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_STEP(I, Code) NCPP_GLUE(NCPP_ROBJECT_BODY_, Code);



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_REFLECT_METADATA(...) \
			if constexpr (\
				!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_type_info)\
			) {\
				__VA_ARGS__;\
			}

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs, ...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_CONSTRUCTOR(Overrider, Keywords, Implement, Inputs __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_BASE(...) \
			{\
				\
				using F_base = __VA_ARGS__;\
				using F_base_sinfo = ___TF_base___ncpp_sinfo___<F_this, __VA_ARGS__>;\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_BASE();\
                \
                F_robject_type_info* base_info_p = F_rtti_traits::template T_safe_reflect<__VA_ARGS__, false, F_reflect_flag__>(\
                    rcontainer_p,\
                    0,\
                    custom_params_p\
                );\
                \
                if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_type_info))\
                    if (!robject_type_info_p->is_has_base(base_info_p))\
                        robject_type_info_p->add_base(base_info_p);\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_BASE();\
				\
			}

#define NCPP_ROBJECT_REFLECT_EXTENDS(...) NCPP_ROBJECT_REFLECT_BASE(__VA_ARGS__)

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_VIRTUAL ;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberMagicType, MemberName, IsVirtualFunction, IsConstFunction,...) \
			robject_member_info_p = ncpp::rtti::T_reflect_object_member<\
				F_this, \
				NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE(MemberName, IsVirtualFunction, IsConstFunction), \
				NCPP_ROBJECT_MEMBER_SINFO(MemberName, IsVirtualFunction, IsConstFunction), \
				NCPP_RTTI_PASS_SPECIFIC_USING()\
			>(\
				robject_type_info_p \
			);

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER_INFO(MemberMagicType, MemberName,...) \
			robject_member_info_p = ncpp::rtti::T_reflect_object_member<\
				F_this, \
				NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE(MemberName), \
				NCPP_ROBJECT_STATIC_MEMBER_SINFO(MemberName), \
				NCPP_RTTI_PASS_SPECIFIC_USING()\
			>(\
				robject_type_info_p \
			);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName,...) \
			__VA_ARGS__;

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
                using F_member_sinfo = ___TF_##MemberName##___ncpp_sinfo___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, false, false>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberMagicType, MemberName, false, false __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}

#define NCPP_ROBJECT_REFLECT_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, false, false)), MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
                using F_member_sinfo = ___TF_##MemberName##___ncpp_sinfo___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, false, true>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberMagicType, MemberName, false, true __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}

#define NCPP_ROBJECT_REFLECT_MEMBER_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, false, true)), MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
                using F_member_sinfo = ___TF_##MemberName##___ncpp_sinfo___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, true, false>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberMagicType, MemberName, true, false __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, false)), MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
                using F_member_sinfo = ___TF_##MemberName##___ncpp_sinfo___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, true, true>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberMagicType, MemberName, true, true __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_MEMBER_TYPE (MemberName, true, true)), MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND_PARAMS(MemberTypeParams);\
                using F_member_sinfo = ___TF_##MemberName##___ncpp_sinfo___<F_this, F_member, ncpp::utilities::T_is_function<F_member>>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER_INFO(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberMagicType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER_IMPL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberTypeParams, MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, MemberName,...) \
            NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER_IMPL2(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName, (NCPP_ROBJECT_WRAPPER_TO_STATIC_MEMBER_TYPE (MemberName)), MemberName __VA_OPT__(,) __VA_ARGS__))

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(Overrider, Keywords, Implement, MemberMagicType, RawMemberMagicName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberMagicType, NCPP_MAGIC_NAME(RawMemberMagicName), NCPP_MAGIC_PARSE_NAME(RawMemberMagicName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_STEP(I, Code) NCPP_GLUE(NCPP_ROBJECT_REFLECT_, Code);

    }

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

    namespace rtti {

#define NCPP_ROBJECT_SINFOS_METADATA(...)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE(...) , ___TF_base___ncpp_sinfo___<F_this, __VA_ARGS__>
#define NCPP_ROBJECT_SINFOS_EXTENDS(...) NCPP_ROBJECT_SINFOS_BASE(__VA_ARGS__)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_VIRTUAL

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_PASS_MEMBER(MemberName, IsVirtualFunction, IsConstFunction) \
            NCPP_EXPAND(NCPP_ROBJECT_MEMBER_SINFO(MemberName, IsVirtualFunction, IsConstFunction))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, false)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, false)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, false)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, true)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, true)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), false, true)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_VIRTUAL(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_ABSTRACT(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, false)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_ABSTRACT_CONST(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName), true, true)

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_PASS_STATIC_MEMBER(MemberName) \
            NCPP_EXPAND(NCPP_ROBJECT_STATIC_MEMBER_SINFO(MemberName))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_BASE_PRIVATE_STATIC(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_STATIC_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName))
#define NCPP_ROBJECT_SINFOS_BASE_PROTECTED_STATIC(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_STATIC_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName))
#define NCPP_ROBJECT_SINFOS_BASE_PUBLIC_STATIC(Overrider, Keywords, Implement, MemberMagicType, MemberMagicName,...) , NCPP_ROBJECT_SINFOS_PASS_STATIC_MEMBER(NCPP_MAGIC_PARSE_NAME(MemberMagicName))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_SINFOS_STEP(I, Code) NCPP_GLUE(NCPP_ROBJECT_SINFOS_, Code)

    }

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <ncpp/rtti_macros.hpp>



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

    namespace rtti {

#define NCPP_ROBJECT(RTTIOptions, ObjectRepresentTypeName, ObjectImplementTypeName,...)\
			NCPP_PUBLIC_KEYWORD\
				NCPP_RTTI_SPECIFIC_USING(RTTIOptions);\
				\
				\
				\
			NCPP_PUBLIC_KEYWORD\
				using F_this = ObjectImplementTypeName;\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> static_type_name()  { \
					\
					if constexpr (ncpp::rtti::secured_name) return ("_" + ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(ncpp::utilities::T_type_hash_code<F_this>));\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_EXPAND(NCPP_CSTR_ML(ObjectImplementTypeName)), ""); \
				}\
				\
				\
				\
			NCPP_PRIVATE_KEYWORD\
				NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_robject_flag);\
				NCPP_OBJECT_IMPLEMENT(F_this);\
				\
				\
				\
			NCPP_PRIVATE_KEYWORD\
				NCPP_EXPAND(NCPP_FOR_EACH(NCPP_ROBJECT_BODY_STEP __VA_OPT__(,) __VA_ARGS__));\
				\
				\
				\
			NCPP_PUBLIC_KEYWORD\
				using F_sinfos = ncpp::utilities::TF_template_targ_list<void NCPP_EXPAND(NCPP_FOR_EACH(NCPP_ROBJECT_SINFOS_STEP __VA_OPT__(,) __VA_ARGS__))>::template TF_remove_heads<1>;\
                using F_base_sinfos = F_sinfos::template TF_filter<ncpp::rtti::TL_sinfo_base>;                                                                       \
                using F_member_sinfos = F_sinfos::template TF_filter<ncpp::rtti::TL_sinfo_member>;                                                                       \
				\
				\
				\
			NCPP_PUBLIC_KEYWORD\
				template<typename F_reflect_flag__>\
				static F_robject_type_info* T_static_reflect(\
					F_rcontainer* rcontainer_p, \
					F_rtti_traits::template TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0\
				){\
					\
					F_robject_type_info* robject_type_info_p = 0;\t
					F_robject_member_info* robject_member_info_p = 0;\
					\
					if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_type_info))\
						robject_type_info_p = ncpp::rtti::T_reflect_object_type<F_this, NCPP_RTTI_PASS_SPECIFIC_USING()>(rcontainer_p);\
					\
					NCPP_ROBJECT_CALL_USER_PRE_REFLECT_OBJECT();\
					\
					NCPP_EXPAND(NCPP_FOR_EACH(NCPP_ROBJECT_REFLECT_STEP __VA_OPT__(,) __VA_ARGS__));\
					\
					NCPP_ROBJECT_CALL_USER_POST_REFLECT_OBJECT();\
					\
					return robject_type_info_p;\
					\
				};\
				\
				static NCPP_FORCE_INLINE F_robject_type_info* static_reflect(\
					F_rcontainer* rcontainer_p, \
					void* custom_params_p = 0\
				){\
					return T_static_reflect<void>(rcontainer_p, custom_params_p);\
				}

		////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_BASIC_ROBJECT(ObjectTypeName,...) NCPP_EXPAND(NCPP_ROBJECT(ncpp::rtti::F_default_options, NCPP_MA(ObjectTypeName), NCPP_MA(ObjectTypeName) __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_FINALIZE_REPRESENT(ObjectRepresentTypeName, ObjectImplementTypeName,...) NCPP_EXPAND(NCPP_RTTI_FLAG_BIND_REPRESENT(NCPP_MA(ObjectRepresentTypeName), NCPP_MA(ObjectImplementTypeName) __VA_OPT__(,) __VA_ARGS__))

	}

}
