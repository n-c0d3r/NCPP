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

#include <ncpp/containers/.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/traits.hpp>
#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/rtti/robject_flag.hpp>
#include <ncpp/rtti/security_helper.hpp>

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

#define NCPP_ROBJECT_USER_REFLECT_CUSTOM_PARAMS(CustomReflector, CustomParamsType) \
            NCPP_RTTI_IMPLEMENT_FLAG_WITH_INNER(ncpp::rtti::F_user_reflect_custom_params_flag, NCPP_MA(using F_custom_params = CustomParamsType;));



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
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_pre_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            typename F_member__,                                        \
            class F_member_static_info__,                               \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
        );\
		template<class F_robject__, typename F_member__, class F_member_static_info__, NCPP_RTTI_SPECIFIC_TARGS()>\
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
			F_member_static_info\
		>(\
			rcontainer_p,\
			robject_type_info_p,\
			robject_member_info_p,\
			custom_params_p\
		);

#define NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(...) \
        NCPP_RTTI_IMPLEMENT_FLAG(                                       \
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_post_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            typename F_member__,                                        \
            class F_member_static_info__,                               \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
        );\
		template<class F_robject__, typename F_member__, class F_member_static_info__, NCPP_RTTI_SPECIFIC_TARGS()>\
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
			F_member_static_info\
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
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_pre_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            class F_base__,                                        \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
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
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_post_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            class F_base__,                                        \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
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
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_pre_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
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
            NCPP_MA(                                                    \
                ncpp::rtti::TF_user_post_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_TARGS()> \
            ),\
            class F_robject__,                                          \
            NCPP_RTTI_SPECIFIC_TARGS_NO_DEFAULT()                                  \
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



#define NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_BODY_OVERRIDER_##Overrider)(MemberType, MemberName);
#define NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_REFLECT_OVERRIDER_##Overrider)(MemberType, MemberName);

#define NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_OVERRIDER_KEYWORDS_##Overrider)()
#define NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_ROBJECT_MEMBER_OVERRIDER_IMPLEMENT_##Overrider)(MemberType, MemberName)



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_ROBJECT_WRAP_TYPE(Type) ncpp::utilities::TF_first_template_arg<Type>
#define NCPP_ROBJECT_SAFE_FUNC_WRAP_TYPE(Type) ncpp::utilities::TF_nth_template_arg<ncpp::utilities::T_is_function<Type>, Type, NCPP_ROBJECT_WRAP_TYPE(Type)*>



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

#define NCPP_ROBJECT_BODY_BASE(BaseName)

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

#define NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO(MemberType, MemberName, IsVirtualFunction, IsConstFunction) \
			template<typename object_type__, typename member_type__, bool is_function__, bool is_virtual__, bool is_const__>\
			struct TF_##MemberName##___ncpp_static_info___;                                                       \
            template<typename object_type__, typename member_type__, bool is_function__, bool is_virtual__, bool is_const__>\
			friend struct TF_##MemberName##___ncpp_static_info___;\
			template<typename object_type__, typename member_type__>\
			struct TF_##MemberName##___ncpp_static_info___<object_type__, member_type__, false, IsVirtualFunction, IsConstFunction>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
				\
				static NCPP_FORCE_INLINE auto* member_p(){ return &F_this::MemberName; }\
				\
				static NCPP_FORCE_INLINE void invoke(void* object_p = 0){}\
				\
				static NCPP_FORCE_INLINE ncpp::sz address(){ return 0; }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_WRAPPED_ARGS_TO_CSTR(MemberType), ""); }\
				static constexpr ncpp::u64 id() { return utilities::T_type_hash_code<TF_##MemberName##___ncpp_static_info___>; }\
				\
				static constexpr ncpp::sz offset() { return (ncpp::sz)reinterpret_cast<ncpp::sz>(&(reinterpret_cast<object_type__*>(0)->MemberName)); }\
                static constexpr ncpp::u16 size() { return (ncpp::u16)ncpp::utilities::T_sizeof<NCPP_EXPAND(NCPP_PACK MemberType)>; }\
				\
				static constexpr bool is_static() { return false; }\
				static NCPP_FORCE_INLINE int static_get() { return 0; }\
                \
                static constexpr ncpp::b8 is_function() { return false; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
				static constexpr ncpp::b8 is_const_function() { return false; }\
				\
			};\
			\
            template<typename object_type__, typename return_type__, typename... arg_types__>\
			struct TF_##MemberName##___ncpp_static_info___<object_type__, return_type__(arg_types__...), true, IsVirtualFunction, IsConstFunction>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
				\
				static NCPP_FORCE_INLINE auto* member_p(){ return &F_this::MemberName; }\
				\
				static NCPP_FORCE_INLINE auto invoke(arg_types__... args, void* object_p = 0) {\
					\
					return reinterpret_cast<F_this*>(object_p)->MemberName(std::forward<arg_types__>(args)...);\
					\
				}\
				\
				static NCPP_FORCE_INLINE ncpp::sz address(){ return reinterpret_cast<ncpp::sz>(&invoke); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_WRAPPED_ARGS_TO_CSTR(MemberType), ""); }\
				static constexpr ncpp::u64 id() { return utilities::T_type_hash_code<TF_##MemberName##___ncpp_static_info___>; }\
				\
				static constexpr ncpp::sz offset() { return 0; }\
				static constexpr ncpp::u16 size() { return 0; }\
				\
				static constexpr bool is_static() { return false; }\
				static NCPP_FORCE_INLINE int static_get() { return 0; }\
                \
                static constexpr ncpp::b8 is_function() { return true; }\
                static constexpr ncpp::b8 is_virtual_function() { return IsVirtualFunction; }\
                static constexpr ncpp::b8 is_const_function() { return IsConstFunction; }\
				\
			};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName);\
			NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO(MemberType, MemberName, false, false);\
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberType, MemberName) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_MA Implement)

#define NCPP_ROBJECT_BODY_BASE_PRIVATE(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...)\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName);\
			NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO(MemberType, MemberName, false, true);\
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberType, MemberName) const NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_MA Implement)

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName);\
			NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO(MemberType, MemberName, true, false);\
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) virtual NCPP_MAGIC(MemberType, MemberName) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_MA Implement)

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...)\
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName);\
			NCPP_ROBJECT_BODY_MEMBER_STATIC_INFO(MemberType, MemberName, true, true);\
			NCPP_FORCE_INLINE auto MemberName(auto&&... args) const {\
				\
				return ((F_this*)this)->MemberName(std::forward<decltype(args)>(args)...);\
				\
			};\
			NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) virtual NCPP_MAGIC(MemberType, MemberName) const NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_MA Implement)

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO(MemberType, MemberName) \
			template<typename object_type__, typename member_type__, bool is_function__>\
			struct TF_##MemberName##___ncpp_static_info___;\
			template<typename object_type__, typename member_type__, bool is_function__>\
			friend struct TF_##MemberName##___ncpp_static_info___;\
			template<typename object_type__, typename member_type__>\
			struct TF_##MemberName##___ncpp_static_info___<object_type__, member_type__, false>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
				\
				static NCPP_FORCE_INLINE auto* member_p(){ return &F_this::MemberName; }\
				\
				static NCPP_FORCE_INLINE void invoke(void* object_p = 0){}\
				\
				static NCPP_FORCE_INLINE ncpp::sz address(){ return reinterpret_cast<ncpp::sz>(&F_this::MemberName); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_WRAPPED_ARGS_TO_CSTR(MemberType), ""); }\
				static constexpr ncpp::u64 id() { return utilities::T_type_hash_code<TF_##MemberName##___ncpp_static_info___>; }\
				\
				static constexpr ncpp::sz offset() { return 0; }\
                static constexpr ncpp::u16 size() { return (ncpp::u16)ncpp::utilities::T_sizeof<NCPP_EXPAND(NCPP_PACK MemberType)>; }\
				\
				static constexpr bool is_static() { return true; }\
				static NCPP_FORCE_INLINE auto& static_get() { return F_this::MemberName; }\
                \
                static constexpr ncpp::b8 is_function() { return false; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
				static constexpr ncpp::b8 is_const_function() { return false; }\
				\
			};\
			\
			template<typename object_type__, typename return_type__, typename... arg_types__>\
			struct TF_##MemberName##___ncpp_static_info___<object_type__, return_type__(arg_types__...), true>{\
				\
			NCPP_PUBLIC_KEYWORD\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
				\
				static NCPP_FORCE_INLINE auto* member_p(){ return &F_this::MemberName; }\
				\
				static NCPP_FORCE_INLINE auto invoke(arg_types__... args, void* object_p = 0) {\
					\
					return F_this::MemberName(std::forward<arg_types__>(args)...);\
					\
				}\
				\
				static NCPP_FORCE_INLINE ncpp::sz address(){ return reinterpret_cast<ncpp::sz>(&invoke); }\
				\
				static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> name() { \
					\
					if constexpr (ncpp::rtti::secured_name) return ncpp::containers::T_to_string<char, typename F_rtti_traits::F_allocator>(id());\
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(#MemberName, ""); \
				}\
                static NCPP_FORCE_INLINE ncpp::containers::TF_string<char, typename F_rtti_traits::F_allocator> raw_type_name() { return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_WRAPPED_ARGS_TO_CSTR(MemberType), ""); }\
				static constexpr ncpp::u64 id() { return utilities::T_type_hash_code<TF_##MemberName##___ncpp_static_info___>; }\
				\
				static constexpr ncpp::sz offset() { return 0; }\
				static constexpr ncpp::u16 size() { return 0; }\
				\
				static constexpr bool is_static() { return true; }\
				static NCPP_FORCE_INLINE auto* static_get() { return &F_this::MemberName; }\
                \
                static constexpr ncpp::b8 is_function() { return true; }\
                static constexpr ncpp::b8 is_virtual_function() { return false; }\
                static constexpr ncpp::b8 is_const_function() { return false; }\
				\
			};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			NCPP_ROBJECT_APPLY_MEMBER_BODY_OVERRIDER(Overrider, MemberType, MemberName);\
			NCPP_ROBJECT_BODY_STATIC_MEMBER_STATIC_INFO(MemberType, MemberName);\
			static NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_KEYWORDS(Overrider) NCPP_EXPAND(NCPP_MA Keywords) NCPP_MAGIC(MemberType, MemberName) NCPP_ROBJECT_APPLY_MEMBER_OVERRIDER_IMPLEMENT(Overrider, MemberType, MemberName) NCPP_EXPAND(NCPP_MA Implement)

#define NCPP_ROBJECT_BODY_BASE_PRIVATE_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PRIVATE_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PROTECTED_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PROTECTED_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_BODY_BASE_PUBLIC_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_PUBLIC_KEYWORD NCPP_EXPAND(NCPP_ROBJECT_BODY_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

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

#define NCPP_ROBJECT_REFLECT_BASE(BaseName) \
			{\
				\
				using F_base = BaseName;\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_BASE();\
                \
                F_robject_type_info* base_info_p = F_rtti_traits::template T_safe_reflect<BaseName, false, F_reflect_flag__>(\
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

#define NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberType, MemberName, IsVirtualFunction, IsConstFunction,...) \
			robject_member_info_p = ncpp::rtti::T_reflect_object_member<\
				F_this, \
				NCPP_EXPAND(NCPP_PACK MemberType), \
				TF_##MemberName##___ncpp_static_info___<F_this, NCPP_EXPAND(NCPP_PACK MemberType), ncpp::utilities::T_is_function<NCPP_EXPAND(NCPP_PACK MemberType)>, IsVirtualFunction, IsConstFunction>, \
				NCPP_RTTI_PASS_SPECIFIC_USING()\
			>(\
				robject_type_info_p \
			);

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER_INFO(MemberType, MemberName,...) \
			robject_member_info_p = ncpp::rtti::T_reflect_object_member<\
				F_this, \
				NCPP_EXPAND(NCPP_PACK MemberType), \
				TF_##MemberName##___ncpp_static_info___<F_this, NCPP_EXPAND(NCPP_PACK MemberType), ncpp::utilities::T_is_function<NCPP_EXPAND(NCPP_PACK MemberType)>>, \
				NCPP_RTTI_PASS_SPECIFIC_USING()\
			>(\
				robject_type_info_p \
			);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName,...) \
			__VA_ARGS__;

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
                using F_member_static_info = TF_##MemberName##___ncpp_static_info___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, false, false>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberType, MemberName, false, false __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
					&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}\
			\
			if constexpr (false)\
				ncpp::utilities::TF_first_template_arg<NCPP_EXPAND(NCPP_PACK MemberType)> MemberName##_tail

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
                using F_member_static_info = TF_##MemberName##___ncpp_static_info___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, false, true>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberType, MemberName, false, true __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
					&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}\
			\
			if constexpr (false)\
				ncpp::utilities::TF_first_template_arg<NCPP_EXPAND(NCPP_PACK MemberType)> MemberName##_tail

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
                using F_member_static_info = TF_##MemberName##___ncpp_static_info___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, true, false>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberType, MemberName, true, false __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
					&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}\
			\
			if constexpr (false)\
				int MemberName##_tail

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
                using F_member_static_info = TF_##MemberName##___ncpp_static_info___<F_this, F_member, ncpp::utilities::T_is_function<F_member>, true, true>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_INFO(MemberType, MemberName, true, true __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
					&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}\
			\
			if constexpr (false)\
				int MemberName##_tail

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_VIRTUAL_CONST(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName,...) \
			{\
				\
				using F_member = NCPP_EXPAND(NCPP_PACK MemberType);\
                using F_member_static_info = TF_##MemberName##___ncpp_static_info___<F_this, F_member, ncpp::utilities::T_is_function<F_member>>;\
				\
				if constexpr (!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info))\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER_INFO(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_PRE_REFLECT_MEMBER();\
				\
				NCPP_ROBJECT_APPLY_MEMBER_REFLECT_OVERRIDER(Overrider, MemberType, MemberName);\
				\
				if constexpr (\
					!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_metadata)\
					&& !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, ncpp::rtti::F_disable_reflect_robject_member_info)\
				)\
					{ NCPP_EXPAND(NCPP_ROBJECT_REFLECT_MEMBER_METADATA(MemberType, MemberName __VA_OPT__(,) __VA_ARGS__)) };\
				\
				NCPP_ROBJECT_CALL_USER_POST_REFLECT_MEMBER();\
				\
			}\
			\
			if constexpr (false)\
				ncpp::utilities::TF_first_template_arg<NCPP_EXPAND(NCPP_PACK MemberType)> MemberName##_tail

#define NCPP_ROBJECT_REFLECT_BASE_PRIVATE_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PROTECTED_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))
#define NCPP_ROBJECT_REFLECT_BASE_PUBLIC_STATIC(Overrider, Keywords, Implement, MemberType, MemberName,...) NCPP_EXPAND(NCPP_ROBJECT_REFLECT_STATIC_MEMBER(Overrider, Keywords, Implement, MemberType, MemberName __VA_OPT__(,) __VA_ARGS__))

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
					else return NCPP_PARSE_RTTI_SECURED_NAME_CODE(NCPP_EXPAND(NCPP_CSTR(ObjectImplementTypeName)), ""); \
				}\
				\
				\
				\
			NCPP_PRIVATE_KEYWORD\
				NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_robject_flag);\
				\
				\
				\
			NCPP_PRIVATE_KEYWORD\
				NCPP_EXPAND(NCPP_FOR_EACH(NCPP_ROBJECT_BODY_STEP __VA_OPT__(,) __VA_ARGS__));\
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
					F_robject_type_info* robject_type_info_p = 0;\
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
				}\
				\
				\
				\
			NCPP_PUBLIC_KEYWORD\
				static constexpr ncpp::b8 is_virtual = NCPP_RTTI_IS_HAS_FLAG(F_this, ncpp::rtti::F_robject_virtual_flag);\

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_RCLASS(RTTIOptions, ObjectRepresentTypeName, ObjectImplementTypeName,...) NCPP_EXPAND(NCPP_ROBJECT(RTTIOptions, NCPP_MA(ObjectRepresentTypeName), NCPP_MA(ObjectImplementTypeName), VIRTUAL __VA_OPT__(,) __VA_ARGS__))
#define NCPP_RSTRUCT(RTTIOptions, ObjectRepresentTypeName, ObjectImplementTypeName,...) NCPP_EXPAND(NCPP_ROBJECT(RTTIOptions, NCPP_MA(ObjectRepresentTypeName), NCPP_MA(ObjectImplementTypeName) __VA_OPT__(,) __VA_ARGS__))

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_BASIC_RCLASS(ObjectTypeName,...) NCPP_EXPAND(NCPP_ROBJECT(ncpp::rtti::F_default_options, NCPP_MA(ObjectTypeName), NCPP_MA(ObjectTypeName), VIRTUAL __VA_OPT__(,) __VA_ARGS__))
#define NCPP_BASIC_RSTRUCT(ObjectTypeName,...) NCPP_EXPAND(NCPP_ROBJECT(ncpp::rtti::F_default_options, NCPP_MA(ObjectTypeName), NCPP_MA(ObjectTypeName), __VA_OPT__(,) __VA_ARGS__))

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

#define NCPP_ROBJECT_FINALIZE_REPRESENT(ObjectRepresentTypeName, ObjectImplementTypeName,...) NCPP_EXPAND(NCPP_RTTI_FLAG_BIND_REPRESENT(NCPP_MA(ObjectRepresentTypeName), NCPP_MA(ObjectImplementTypeName) __VA_OPT__(,) __VA_ARGS__))

	}

}
