#pragma once

/** @file ncpp/rtti/robject_type_info.hpp
*	@brief Implements robject type info.
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

#include <ncpp/containers/.hpp>
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
		class TF_robject_type_info {

		public:
			NCPP_RTTI_SPECIFIC_USING(F_options__);



		private:
			F_rcontainer* rcontainer_p_ = 0;
			containers::TF_string<char, typename F_rtti_traits::F_allocator> name_;
            F_subtype subtype_;

			containers::TF_set<F_robject_type_info*> base_type_info_p_set_;
            
            containers::TF_unordered_multimap<containers::TF_string<char, typename F_rtti_traits::F_allocator>, F_robject_member_info*> name_to_member_info_p_map_;
            containers::TF_unordered_map<u64, F_robject_member_info*> hash_code_to_member_info_p_map_;

		public:
			F_robject_type_info_additional_data additional_data;

		public:
			NCPP_FORCE_INLINE F_rcontainer* rcontainer_p() { return rcontainer_p_; }
			NCPP_FORCE_INLINE const F_rcontainer* rcontainer_p() const { return rcontainer_p_; }
			NCPP_FORCE_INLINE const containers::TF_string<char, F_allocator>& name() const { return name_; }
			NCPP_FORCE_INLINE F_subtype subtype() const { return subtype_; }

			NCPP_FORCE_INLINE const containers::TF_set<F_robject_type_info*>& base_type_info_p_set() const { return base_type_info_p_set_; }
            NCPP_FORCE_INLINE b8 is_has_base(F_robject_type_info* base_type_info_p) const {
                
                return (base_type_info_p_set_.find(base_type_info_p) != base_type_info_p_set_.end());
            }
            NCPP_FORCE_INLINE void add_base(F_robject_type_info* base_type_info_p) {
                
                NCPP_ASSERT(!is_has_base(base_type_info_p)) << "this base type info is already added";
                
                base_type_info_p_set_.insert(base_type_info_p);
            }
            NCPP_FORCE_INLINE void remove_base(F_robject_type_info* base_type_info_p) {
                
                NCPP_ASSERT(is_has_base(base_type_info_p)) << "this base type info is not added";
                
                base_type_info_p_set_.erase(base_type_info_p_set_.find(base_type_info_p));
            }
            
            NCPP_FORCE_INLINE const containers::TF_unordered_multimap<containers::TF_string<char, typename F_rtti_traits::F_allocator>, F_robject_member_info*>& name_to_member_info_p_map() const { return name_to_member_info_p_map_; }
            NCPP_FORCE_INLINE const containers::TF_unordered_map<u64, F_robject_member_info*>& hash_code_to_member_info_p_map() const { return hash_code_to_member_info_p_map_; }

			inline F_robject_member_info* member_info(const containers::TF_string<char, F_allocator>& name) {

				auto it = name_to_member_info_p_map_.find(name);

				if (it == name_to_member_info_p_map_.end())
					return 0;

				return it->second;
			}
			inline const F_robject_member_info* member_info(const containers::TF_string<char, F_allocator>& name) const {

				auto it = name_to_member_info_p_map_.find(name);

				if (it == name_to_member_info_p_map_.end())
					return 0;

				return it->second;
			}
            inline F_robject_member_info* member_info(u64 hash_code) {

                auto it = hash_code_to_member_info_p_map_.find(hash_code);

                if (it == hash_code_to_member_info_p_map_.end())
                    return 0;

                return it->second;
            }
            inline const F_robject_member_info* member_info(u64 hash_code) const {

                auto it = hash_code_to_member_info_p_map_.find(hash_code);

                if (it == hash_code_to_member_info_p_map_.end())
                    return 0;

                return it->second;
            }
			inline void add_member_info(F_robject_member_info* info) {

				auto it = hash_code_to_member_info_p_map_.find(info->hash_code());

				if (it != hash_code_to_member_info_p_map_.end())
					return;

				name_to_member_info_p_map_.insert({ info->name(), info });
                hash_code_to_member_info_p_map_.insert({ info->hash_code(), info });
			}
			inline void remove_member_info(const containers::TF_string<char, F_allocator>& name) {

                auto name_range = name_to_member_info_p_map_.equal_range(name);

				if (name_range.first != name_to_member_info_p_map_.end()) {

                    for(auto next_name_it = name_range.first;;) {

                        auto name_it = next_name_it++;

                        hash_code_to_member_info_p_map_.erase(hash_code_to_member_info_p_map_.find(name_it->second->hash_code()));

                        F_rtti_traits::template T_delete<F_robject_member_info>(&(rcontainer_p_->allocator()), name_it->second);

                        name_to_member_info_p_map_.erase(name_it);

                        if(next_name_it == name_range.second)
                            break;

                    }

				}
			}
            inline void remove_member_info(u64 hash_code) {

                auto it = hash_code_to_member_info_p_map_.find(hash_code);

                if (it != hash_code_to_member_info_p_map_.end()) {

                    auto name_range = name_to_member_info_p_map_.equal_range(it->second->name());

                    if (name_range.first != name_to_member_info_p_map_.end())
                        for(auto next_name_it = name_range.first;;) {

                            auto name_it = next_name_it++;

                            if(name_it->second->hash_code() == hash_code) {

                                name_to_member_info_p_map_.erase(name_it);

                                break;

                            }

                            if(next_name_it == name_range.second)
                                break;

                        }

                    F_rtti_traits::template T_delete<F_robject_member_info>(&(rcontainer_p_->allocator()), it->second);

                    hash_code_to_member_info_p_map_.erase(it);

                }
            }



		public:
			NCPP_FORCE_INLINE TF_robject_type_info(F_rcontainer* rcontainer_p, const containers::TF_string<char, F_allocator>& name, F_subtype subtype) :
				rcontainer_p_(rcontainer_p),
				name_(name),
                subtype_(subtype)
			{}
			~TF_robject_type_info() {

				clear();
			}



		public:
			void clear() {

				for (auto it = hash_code_to_member_info_p_map_.begin(); it != hash_code_to_member_info_p_map_.end();) {

					auto current_it = it++;

					remove_member_info(current_it->first);

				}

			}

		};



		template<
			class F_robject__,

			NCPP_RTTI_SPECIFIC_TARGS()
		>
		F_robject_type_info__* T_reflect_object_type(
			F_rcontainer__* rcontainer_p
		) {

			F_robject_type_info__* robject_type_info_p = rcontainer_p->robject_type_info(utilities::T_type_hash_code<F_robject__>);

			if (robject_type_info_p)
				return robject_type_info_p;

			robject_type_info_p = F_rtti_traits__::template T_new<F_robject_type_info__>(
				&(rcontainer_p->allocator()),
				rcontainer_p,
                F_rtti_traits__::template T_safe_type_name<F_robject__>(),
                TF_subtype<F_robject__>()
			);

			rcontainer_p->add_robject_type_info(robject_type_info_p);

			return robject_type_info_p;
		}

	}

}
