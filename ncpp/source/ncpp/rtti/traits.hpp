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
#include <ncpp/mem/.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/rflag.hpp>
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

#define NCPP_RTTI_SEPECIFIC_TARGS(...) \
			class F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options__,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__ = ncpp::rtti::TF_traits<F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options__>,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##allocator__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_allocator,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_rcontainer,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_robject_type_info,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_robject_member_info,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer_additional_data__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_rcontainer_additional_data,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info_additional_data__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_robject_type_info_additional_data,\
			class F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info_additional_data__ = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__::F_robject_member_info_additional_data

#define NCPP_RTTI_PASS_SEPECIFIC_TARGS(...) \
			F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options__, \
			F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits__, \
			F_##__VA_OPT__(__VA_ARGS__##_)##allocator__, \
			F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer__, \
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info__, \
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info__,\
			F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer_additional_data__,\
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info_additional_data__,\
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info_additional_data__

#define NCPP_RTTI_SEPECIFIC_USING(RTTIOptions, ...) \
			using F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options = RTTIOptions;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits = ncpp::rtti::TF_traits<F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options>;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##allocator = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_allocator;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_rcontainer;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_robject_type_info;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_robject_member_info;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer_additional_data = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_rcontainer_additional_data;\
			using F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info_additional_data = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_robject_type_info_additional_data;\
            using F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info_additional_data = typename F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits::F_robject_member_info_additional_data;

#define NCPP_RTTI_PASS_SEPECIFIC_USING(...) \
			F_##__VA_OPT__(__VA_ARGS__##_)##rtti_options, \
			F_##__VA_OPT__(__VA_ARGS__##_)##rtti_traits, \
			F_##__VA_OPT__(__VA_ARGS__##_)##allocator, \
			F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer, \
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info, \
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info,\
			F_##__VA_OPT__(__VA_ARGS__##_)##rcontainer_additional_data,\
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_type_info_additional_data,\
			F_##__VA_OPT__(__VA_ARGS__##_)##robject_member_info_additional_data



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
		struct TF_robject_member_info;



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

			using F_allocator = mem::F_default_allocator;

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

			using F_allocator = typename F_options::F_allocator;

			using F_rcontainer_additional_data = typename F_options::F_rcontainer_additional_data;
			using F_robject_type_info_additional_data = typename F_options::F_robject_type_info_additional_data;
			using F_robject_member_info_additional_data = typename F_options::F_robject_member_info_additional_data;

			using F_rcontainer = TF_rcontainer<F_options>;
			using F_robject_type_info = TF_robject_type_info<F_options>;
			using F_robject_member_info = TF_robject_member_info<F_options>;



			template<class F__>
			static NCPP_FORCE_INLINE F__* T_allocate(F_allocator& allocator) {

				return reinterpret_cast<F__*>(allocator.allocate(sizeof(F__), 0));
			}
			template<class F__, typename... arg_types__>
			static NCPP_FORCE_INLINE F__* T_new(F_allocator& allocator, arg_types__&&... args) {

				return new(T_allocate<F__>(allocator)) F__(std::forward<arg_types__>(args)...);
			}
			template<class F__>
			static NCPP_FORCE_INLINE void T_delete(F_allocator& allocator, F__* pointer) {

				pointer->~F__();

				allocator.deallocate(pointer, sizeof(F__));
			}



			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_compile_time_rflag__ = void,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag) 
                    && (NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_virtual_flag) && enable_virtual_reflect__),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, rtti::F_rflag rflag = NCPP_RFLAG_DEFAULT, void* custom_data_p = 0) {

				if(object_p)
					return object_p->virtual_reflect(rcontainer_p, rflag, custom_data_p);
				else
					return F_robject__::static_reflect(rcontainer_p, rflag, custom_data_p);

				return 0;
			}
			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_compile_time_rflag__ = void,
				std::enable_if_t<
					NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag)
                    && (!NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_virtual_flag) || (!enable_virtual_reflect__)),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, rtti::F_rflag rflag = NCPP_RFLAG_DEFAULT, void* custom_data_p = 0) {

				return F_robject__::template T_static_reflect<F_compile_time_rflag__>(rcontainer_p, rflag, custom_data_p);
			}
			template<
				class F_robject__,
                b8 enable_virtual_reflect__ = true,
                class F_compile_time_rflag__ = void,
				std::enable_if_t<
					!NCPP_RTTI_IS_HAS_FLAG(F_robject__, F_robject_flag),
					i32
				> = 0
			>
			static NCPP_FORCE_INLINE F_robject_type_info* T_safe_reflect(F_rcontainer* rcontainer_p, F_robject__* object_p = 0, rtti::F_rflag rflag = NCPP_RFLAG_DEFAULT, void* custom_data_p = 0) {

				return 0;
			}

		};

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		NCPP_RTTI_SEPECIFIC_USING(F_default_options, default);

	}

}
