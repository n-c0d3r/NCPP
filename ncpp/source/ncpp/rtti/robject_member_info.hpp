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

		template<typename F_options__>
		class TF_robject_member_info {

		public:
			NCPP_RTTI_SPECIFIC_USING(F_options__);



		private:
			u64 hash_code_ = 0;
            union {
                sz function_address_ = 0;
                sz variable_getter_address_;
            };
			containers::TF_string<char, F_allocator> name_;
			sz id_ = 0;
			u16 size_ = 0;
            b8 is_virtual_function_ = false;
            b8 is_const_function_ = false;
            b8 is_static_ = false;
            
            F_robject_type_info* robject_type_info_p_ = 0;

            F_subtype subtype_;



		public:
			F_robject_member_info_additional_data additional_data;



		public:
			NCPP_FORCE_INLINE u64 hash_code() const { return hash_code_; }
            NCPP_FORCE_INLINE sz function_address() const { return function_address_; }
			NCPP_FORCE_INLINE sz variable_getter_address() const { return variable_getter_address_; }
			NCPP_FORCE_INLINE const containers::TF_string<char, F_allocator>& name() const { return name_; }
			NCPP_FORCE_INLINE sz id() const { return id_; }
            NCPP_FORCE_INLINE u16 size() const { return size_; }
			NCPP_FORCE_INLINE b8 is_function() const { return (size_ == 0); }
            NCPP_FORCE_INLINE b8 is_virtual_function() const { return is_virtual_function_; }
            NCPP_FORCE_INLINE b8 is_const_function() const { return is_const_function_; }
            NCPP_FORCE_INLINE b8 is_static() const { return is_static_; }
            
            NCPP_FORCE_INLINE F_robject_type_info* robject_type_info_p() { return robject_type_info_p_; }
            NCPP_FORCE_INLINE const F_robject_type_info* robject_type_info_p() const { return robject_type_info_p_; }

            NCPP_FORCE_INLINE F_subtype subtype() const { return subtype_; }



		public:
			TF_robject_member_info(
				sz hash_code,
				sz function_address_or_variable_getter_address,
				const containers::TF_string<char, F_allocator>& name,
				sz id,
				u16 size,
                b8 is_virtual_function,
                b8 is_const_function,
                b8 is_static,
                                   
                F_robject_type_info* robject_type_info_p,

                F_subtype subtype
			) :
                hash_code_(hash_code),
                function_address_(function_address_or_variable_getter_address),
                name_(name),
                id_(id),
                size_(size),
                is_virtual_function_(is_virtual_function),
                is_const_function_(is_const_function),
                is_static_(is_static),

                robject_type_info_p_(robject_type_info_p),

                subtype_(subtype)
			{



			}
            
            
            
        private:
            template<typename F__>
            struct TF_get_internal;
            template<typename F__>
            friend struct TF_get_internal;
            
            template<typename F__>
            struct TF_get_internal {

                typedef F__& F_static_getter();
                typedef F__& F_non_static_getter(void*);
                
                static NCPP_FORCE_INLINE F__& invoke(void* object_p, const TF_robject_member_info& member_info) {
                    
                    NCPP_ASSERT(utilities::T_type_hash_code<F__> == member_info.subtype().data().hash_code) << "invalid F__";

                    if(member_info.is_static_)
                        return ((F_static_getter*)member_info.variable_getter_address_)();

                    return ((F_non_static_getter*)member_info.variable_getter_address_)(object_p);
                }
                
            };
            template<typename F_return__, typename... F_args__>
            struct TF_get_internal<F_return__(F_args__...)> {
            
            private:
                using F = F_return__(F_args__...);
                using F_invoke = F_return__(F_args__..., void* object_p);
                
            public:
                static NCPP_FORCE_INLINE F_invoke* invoke(void* object_p, const TF_robject_member_info& member_info) {
                    
                    NCPP_ASSERT(utilities::T_type_hash_code<F> == member_info.subtype().data().hash_code) << "invalid F__";
                    NCPP_ASSERT(!member_info.is_static_ || (member_info.is_static_ && !object_p)) << "object_p must be zero if member is static";
                    
                    return reinterpret_cast<F_invoke*>(member_info.offset_);
                }
                
            };
            
            
            
        public:
            template<typename F__>
            NCPP_FORCE_INLINE b8 T_is() const {
                
                return (utilities::T_type_hash_code<F__> == subtype().data().hash_code);
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_function<F__>, i32> = 0>
            NCPP_FORCE_INLINE F__& T_get(void* object_p = 0) const {
                
                return TF_get_internal<F__>::invoke(object_p, *this);
            }
            template<typename F__, std::enable_if_t<utilities::T_is_function<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_get(void* object_p = 0) const {
                
                return TF_get_internal<F__>::invoke(object_p, *this);
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_function<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_invoke(void* object_p = 0) const {
                
                NCPP_STATIC_ASSERT(utilities::T_is_function<F__>, "cant invoke non function type");
            }
            template<typename F__, typename... F_args__, std::enable_if_t<utilities::T_is_function<F__>, i32> = 0>
            NCPP_FORCE_INLINE typename utilities::TF_function_traits<F__>::F_return T_invoke(F_args__... args, void* object_p = 0) const {
                
                return T_get<F__>()(std::forward<F_args__>(args)..., object_p);
            }

		};

		template<
			class F_robject__,
			typename F_member__,
			class F_member_sinfo__,

			NCPP_RTTI_SPECIFIC_TARGS()
		>
		F_robject_member_info__* T_reflect_object_member(
			F_robject_type_info__* robject_type_info_p
		) {

			F_robject_member_info__* member_info_p = robject_type_info_p->member_info(utilities::T_type_hash_code<F_member_sinfo__>);

			if (member_info_p)
				return member_info_p;

			member_info_p = F_rtti_traits__::template T_new<F_robject_member_info__>(
				&(robject_type_info_p->rcontainer_p()->allocator()),
				F_robject_member_info__(

					utilities::T_type_hash_code<F_member_sinfo__>,
					F_member_sinfo__::function_address() | F_member_sinfo__::variable_getter_address(),
					F_member_sinfo__::name(),
					F_member_sinfo__::id(),
					F_member_sinfo__::size(),
                    F_member_sinfo__::is_virtual_function(),
                    F_member_sinfo__::is_const_function(),
                    F_member_sinfo__::is_static(),
                                        
                    robject_type_info_p,

                    TF_subtype<F_member__>()

				)
			);

			robject_type_info_p->add_member_info(member_info_p);

			return member_info_p;
		}

	}

}
