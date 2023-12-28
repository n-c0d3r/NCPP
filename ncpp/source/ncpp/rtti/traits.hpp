#pragma once

/** @file ncpp/rtti/traits.hpp
*	@brief Implements rtti traits.
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
#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/mem/.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/rtti/traits_defs.hpp>
#include <ncpp/rtti/robject_flag.hpp>
#include <ncpp/rtti/security_helper.hpp>
#include <ncpp/rtti/subtype.hpp>

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



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		template<typename F_options__>
		class TF_rcontainer;

		template<typename F_options__>
		class TF_robject_type_info;

		template<typename F_options__>
        class TF_robject_member_info;



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		struct F_default_options {

			struct F_rcontainer_additional_data {

			};

			struct F_robject_type_info_additional_data {

			};

			struct F_robject_member_info_additional_data {

			};

			using F_allocator = mem::F_general_allocator;

			using F_subtype = rtti::F_subtype;

		};



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		template<class F_options__>
		struct TF_traits {

            using F_options = F_options__;
            
            using F_rtti_options = F_options__;
            using F_rtti_traits = TF_traits<F_options__>;

			using F_allocator = typename F_options::F_allocator;

			using F_rcontainer_additional_data = typename F_options::F_rcontainer_additional_data;
			using F_robject_type_info_additional_data = typename F_options::F_robject_type_info_additional_data;
			using F_robject_member_info_additional_data = typename F_options::F_robject_member_info_additional_data;

			using F_rcontainer = TF_rcontainer<F_options>;
			using F_robject_type_info = TF_robject_type_info<F_options>;
			using F_robject_member_info = TF_robject_member_info<F_options>;

			using F_subtype = typename F_options::F_subtype;



			template<class F__>
			static NCPP_FORCE_INLINE F__* T_allocate(F_allocator* allocator_p) {

				return reinterpret_cast<F__*>(allocator_p->allocate(sizeof(F__), NCPP_ALIGNOF(F__), 0, 0));
			}
			template<class F__, typename... arg_types__>
			static NCPP_FORCE_INLINE F__* T_new(F_allocator* allocator_p, arg_types__&&... args) {

				return new(T_allocate<F__>(allocator_p)) F__(std::forward<arg_types__>(args)...);
			}
			template<class F__>
			static NCPP_FORCE_INLINE void T_delete(F_allocator* allocator_p, F__* pointer) {

				pointer->~F__();

                allocator_p->deallocate(pointer, 1);
			}
            
            
            
			template<typename F_reflect_flag__>
			static auto TF_safe_custom_params_test_internal(int)
                -> decltype(std::declval<F_reflect_flag__&>() << std::declval<F_user_reflect_custom_params_flag>());
			template<typename>
			static auto TF_safe_custom_params_test_internal(...)
                -> void;

			template<typename F_reflect_flag__>
			using TF_safe_custom_params = decltype(TF_safe_custom_params_test_internal<F_reflect_flag__>(0));



			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_reflect_flag__ = void,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag) 
                    && (NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_virtual_flag) && enable_virtual_reflect__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0) {

				if(object_p)
					return object_p->virtual_reflect(rcontainer_p, custom_params_p);
				else
					return F_robject__::static_reflect(rcontainer_p, custom_params_p);

				return 0;
			}
			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_reflect_flag__ = void,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag)
                    && (!NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_virtual_flag) || (!enable_virtual_reflect__)),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0) {

				return F_robject__::template T_static_reflect<F_reflect_flag__>(rcontainer_p, custom_params_p);
			}
			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_reflect_flag__ = void,
				std::enable_if_t<
					!NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0) {

				return 0;
			}



			template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_member__,
                class F_member_static_info__,
				typename F_user_pre_reflect_member_flag__ = TF_user_pre_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_member_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_member(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_member_info* robject_member_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				F_reflect_flag__::template T_user_pre_reflect_member<
                    F_robject__,
                    F_member__,
                    F_member_static_info__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
					robject_member_info_p,
					custom_params_p
                );
			}
			template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_member__,
                class F_member_static_info__,
				typename F_user_pre_reflect_member_flag__ = TF_user_pre_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_member_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_member(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_member_info* robject_member_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				
			}



			template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_member__,
                class F_member_static_info__,
				typename F_user_post_reflect_member_flag__ = TF_user_post_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_member_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_post_reflect_member(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_member_info* robject_member_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				F_reflect_flag__::template T_user_post_reflect_member<
                    F_robject__,
                    F_member__,
                    F_member_static_info__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
					robject_member_info_p,
					custom_params_p
                );
			}
			template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_member__,
                class F_member_static_info__,
				typename F_user_post_reflect_member_flag__ = TF_user_post_reflect_member_flag<F_robject__, F_member__, F_member_static_info__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_member_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_post_reflect_member(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_member_info* robject_member_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				
			}



			template<
                class F_reflect_flag__,
                class F_robject__,
                class F_base__,
				typename F_user_pre_reflect_base_flag__ = TF_user_pre_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_base_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_base(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				F_reflect_flag__::template T_user_pre_reflect_base<
                    F_robject__,
                    F_base__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
					custom_params_p
                );
			}
			template<
                class F_reflect_flag__,
                class F_robject__,
                class F_base__,
				typename F_user_pre_reflect_base_flag__ = TF_user_pre_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_base_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_base(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				
			}



			template<
                class F_reflect_flag__,
                class F_robject__,
                class F_base__,
				typename F_user_post_reflect_base_flag__ = TF_user_post_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_base_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_post_reflect_base(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_type_info* base_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				F_reflect_flag__::template T_user_post_reflect_base<
                    F_robject__,
                    F_base__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
					base_info_p,
					custom_params_p
                );
			}
			template<
                class F_reflect_flag__,
                class F_robject__,
                class F_base__,
				typename F_user_post_reflect_base_flag__ = TF_user_post_reflect_base_flag<F_robject__, F_base__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
				std::enable_if_t<
            		!NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_base_flag__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE void T_safe_user_post_reflect_base(
				F_rcontainer* rcontainer_p, 
				F_robject_type_info* robject_type_info_p,
				F_robject_type_info* base_info_p,
				TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
			) {

				
			}
            
            
            
            template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_user_pre_reflect_object_flag__ = TF_user_pre_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
                std::enable_if_t<
                    NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_object_flag__),
                    i32
                > = 0
            >
            static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_object(
                F_rcontainer* rcontainer_p,
                F_robject_type_info* robject_type_info_p,
                TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
            ) {

                F_reflect_flag__::template T_user_pre_reflect_object<
                    F_robject__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
                    custom_params_p
                );
            }
            template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_user_pre_reflect_object_flag__ = TF_user_pre_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
                std::enable_if_t<
                    !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_pre_reflect_object_flag__),
                    i32
                > = 0
            >
            static NCPP_FORCE_INLINE void T_safe_user_pre_reflect_object(
                F_rcontainer* rcontainer_p,
                F_robject_type_info* robject_type_info_p,
                TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
            ) {

                
            }
            
            
            
            template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_user_post_reflect_object_flag__ = TF_user_post_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
                std::enable_if_t<
                    NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_object_flag__),
                    i32
                > = 0
            >
            static NCPP_FORCE_INLINE void T_safe_user_post_reflect_object(
                F_rcontainer* rcontainer_p,
                F_robject_type_info* robject_type_info_p,
                TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
            ) {

                F_reflect_flag__::template T_user_post_reflect_object<
                    F_robject__,
                    NCPP_RTTI_PASS_SPECIFIC_USING()
                >(
                    rcontainer_p,
                    robject_type_info_p,
                    custom_params_p
                );
            }
            template<
                class F_reflect_flag__,
                class F_robject__,
                typename F_user_post_reflect_object_flag__ = TF_user_post_reflect_object_flag<F_robject__, NCPP_RTTI_PASS_SPECIFIC_USING()>,
                std::enable_if_t<
                    !NCPP_RTTI_IS_HAS_FLAG(F_reflect_flag__, F_user_post_reflect_object_flag__),
                    i32
                > = 0
            >
            static NCPP_FORCE_INLINE void T_safe_user_post_reflect_object(
                F_rcontainer* rcontainer_p,
                F_robject_type_info* robject_type_info_p,
                TF_safe_custom_params<F_reflect_flag__>* custom_params_p = 0
            ) {

                
            }

		};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		NCPP_RTTI_SPECIFIC_USING(F_default_options, default);

	}

}
