#pragma once

/** @file ncpp/rtti/robject_member_info.hpp
*	@brief Implements robject member info.
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/traits.hpp>
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

		template<typename F_options__>
		class TF_robject_member_info {

		public:
			NCPP_RTTI_SEPECIFIC_USING(F_options__);



		private:
			sz type_hash_code_ = 0;
			sz invoke_function_address_or_variable_offset_ = 0;
			eastl::string name_;
			sz id_ = 0;
			u16 size_ = 0;
            
            F_robject_type_info* robject_type_info_p_ = 0;



		public:
			F_robject_member_info_additional_data additional_data;



		public:
			NCPP_FORCE_INLINE sz type_hash_code() const { return type_hash_code_; }
			NCPP_FORCE_INLINE sz invoke_function_address_or_variable_offset() const { return invoke_function_address_or_variable_offset_; }
			NCPP_FORCE_INLINE const eastl::string name() const { return name_; }
			NCPP_FORCE_INLINE sz id() const { return id_; }
			NCPP_FORCE_INLINE u16 size() const { return size_; }
            
            NCPP_FORCE_INLINE F_robject_type_info* robject_type_info_p() { return robject_type_info_p_; }
            NCPP_FORCE_INLINE const F_robject_type_info* robject_type_info_p() const { return robject_type_info_p_; }



		public:
			TF_robject_member_info(
				sz type_hash_code,
				sz invoke_function_address_or_variable_offset,
				const eastl::string& name,
				sz id,
				u16 size,
                F_robject_type_info* robject_type_info_p
			) :
				type_hash_code_(type_hash_code),
				invoke_function_address_or_variable_offset_(invoke_function_address_or_variable_offset),
				name_(name),
				id_(id),
				size_(size),
                robject_type_info_p_(robject_type_info_p)
			{



			}

		};

		template<
			class F_robject__,
			typename F_member__,
			class F_member_static_info__,

			NCPP_RTTI_SEPECIFIC_TARGS()
		>
		F_robject_member_info__* T_reflect_object_member(
			F_robject_type_info__* robject_type_info_p
		) {

			F_robject_member_info__* member_info_p = robject_type_info_p->member_info(F_member_static_info__::name());

			if (member_info_p)
				return member_info_p;

			member_info_p = F_rtti_traits__::template T_new<F_robject_member_info__>(
				robject_type_info_p->rcontainer_p()->allocator(),
				F_robject_member_info__(

					typeid(F_member__).hash_code(),
					F_member_static_info__::invoke_address() | F_member_static_info__::offset(),
					F_member_static_info__::name(),
					F_member_static_info__::id(),
					F_member_static_info__::size(),
                                        
                    robject_type_info_p

				)
			);

			robject_type_info_p->add_member_info(member_info_p);

			return member_info_p;
		}

	}

}
