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

#include <ncpp/iostream.hpp>
#include <ncpp/utilities/is_function.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/traits.hpp>
#include <ncpp/rtti/rflag.hpp>

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

		template<typename options__>
		class robject_type_info_t {

		public:
			NCPP_RTTI_SEPECIFIC_USING(options__);



		private:
			rcontainer_type* rcontainer_p_ = 0;
			sz hash_code_ = 0;
			eastl::string name_;
			robject_type_info_t* base_type_info_p_ = 0;

		public:
			robject_type_info_additional_data_type additional_data;

			eastl::unordered_map<eastl::string, robject_member_info_type*> name_to_member_info_p_map_;

		public:
			inline rcontainer_type* rcontainer_p() { return rcontainer_p_; }
			inline const rcontainer_type* rcontainer_p() const { return rcontainer_p_; }
			inline sz hash_code() const { return hash_code_; }
			inline eastl::string name() const { return name_; }
			inline robject_type_info_t* get_base_type_info_p() { return base_type_info_p_; }
			inline const robject_type_info_t* get_base_type_info_p() const { return base_type_info_p_; }

			inline robject_member_info_type* member_info(const eastl::string& name) {

				auto it = name_to_member_info_p_map_.find(name);

				if (it == name_to_member_info_p_map_.end())
					return 0;

				return it->second;
			}
			inline const robject_member_info_type* member_info(const eastl::string& name) const {

				auto it = name_to_member_info_p_map_.find(name);

				if (it == name_to_member_info_p_map_.end())
					return 0;

				return it->second;
			}
			inline void add_member_info(robject_member_info_type* info) {

				auto it = name_to_member_info_p_map_.find(info->name);

				if (it != name_to_member_info_p_map_.end())
					return;

				name_to_member_info_p_map_[info->name] = info;
			}
			inline void remove_member_info(const eastl::string& name) {

				auto it = name_to_member_info_p_map_.find(name);

				if (it != name_to_member_info_p_map_.end()) {

					rtti_traits::template delete_t<robject_member_info_type>(rcontainer_p_->allocator(), it->second);

					name_to_member_info_p_map_.erase(it);

				}
			}



		public:
			inline robject_type_info_t(rcontainer_type* rcontainer_p, sz hash_code, const eastl::string& name, robject_type_info_t* base_type_info_p) :
				rcontainer_p_(rcontainer_p),
				hash_code_(hash_code),
				name_(name),
				base_type_info_p_(base_type_info_p)
			{



			}
			~robject_type_info_t() {

				clear();

			}



		public:
			void clear() {

				for (auto it = name_to_member_info_p_map_.begin(); it != name_to_member_info_p_map_.end();) {

					auto current_it = it++;

					remove_member_info(current_it->first);

				}

			}

		};



		template<
			class object_type__,

			NCPP_RTTI_SEPECIFIC_TARGS()
		>
		robject_type_info_type__* reflect_object_type_t(
			rcontainer_type__* rcontainer_p, 
			rflag flag = NCPP_RFLAG_DEFAULT
		) {

			robject_type_info_type__* robject_type_info_p = rcontainer_p->robject_type_info(object_type__::static_type_hash_code());

			if (robject_type_info_p)
				return robject_type_info_p;

			robject_type_info_p = rtti_traits__::template new_t<robject_type_info_type__>(
				rcontainer_p->allocator(),
				rcontainer_p,
				object_type__::static_type_hash_code(),
				object_type__::static_type_name(),
				rcontainer_p->robject_type_info(typeid(typename rtti_traits__::safe_base_type_t<object_type__>::type).hash_code())
			);

			rcontainer_p->add_robject_type_info(robject_type_info_p);

			return robject_type_info_p;
		}

	}

}