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

#ifdef NCPP_ENABLE_RTTI
		class rcontext_base;

		template<class rtti_traits__>
		class rcontext_t;
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_PRIVATE_KEYWORD private:
#define NCPP_PROTECTED_KEYWORD protected:
#define NCPP_PUBLIC_KEYWORD public:



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		struct robject_flag {



		};

		template<typename type__>
		static inline constexpr b8 is_robject_t = utilities::is_ostreamable_t<type__, robject_flag>::value;



		struct robject_support_virtual_flag {



		};

		template<typename object_type__>
		static inline constexpr b8 is_support_virtual_t = utilities::is_ostreamable_t<object_type__, robject_support_virtual_flag>::value;



#ifdef NCPP_ENABLE_RTTI
		using name_getter_type = eastl::string(*)();
		using member_offset_getter_type = sz(*)();
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
		class default_traits {

#ifdef NCPP_ENABLE_METADATA
		public:
			struct metadata {



			};
#endif

		};
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
		struct reflector_container_base {

			reflector_container_base(rcontext_base& context);

			void apply_name(rcontext_base& context, const eastl::string& name);
			void apply_hash_code(rcontext_base& context, sz hash_code);

		};



		u32 current_object_offset();
		void set_current_object_offset(u32 new_offset);



		rcontext_base& current_context();

		template<class rtti_traits__>
		static inline rcontext_t<rtti_traits__>& current_context_t() {

			return reinterpret_cast<rcontext_t<rtti_traits__>&>(
				current_context()
			);
		}
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
		template<class rtti_traits__ = default_traits>
		struct rmember_t {

#ifdef NCPP_ENABLE_METADATA
			using metadata_type = typename rtti_traits__::metadata;
#endif

			using ostream_function_type = std::ostream&(void* object_p, u32 tabs, std::ostream& os);



			ostream_function_type* ostream_function_p = 0;

#ifdef NCPP_ENABLE_METADATA
			metadata_type metadata;
#endif



			inline std::ostream& ostream(void* object_p, u32 tabs = 0, std::ostream& os = std::cout) const {

				return ostream_function_p(object_p, tabs, os);
			}

		};
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
		class rcontext_base {

		public:
			friend struct reflector_container_base;



		private:
			eastl::string name_;
			sz hash_code_ = 0;

		protected:
			eastl::string base_name_;
			sz base_hash_code_ = 0;

		public:
			inline const eastl::string& name() const { return name_; }
			inline sz hash_code() const { return hash_code_; }

			inline const eastl::string& base_name() const { return base_name_; }
			inline sz base_hash_code() const { return base_hash_code_; }
			inline b8 is_has_base() const { return base_hash_code_ != 0; }



		protected:
			rcontext_base() {
			
			
			}
			~rcontext_base() {


			}

		};

		template<class rtti_traits__ = default_traits>
		class rcontext_t : public rcontext_base {

		public:
			using rmember_type = rmember_t<rtti_traits__>;

#ifdef NCPP_ENABLE_METADATA
			using metadata_type = typename rtti_traits__::metadata;
#endif



		private:
			eastl::unordered_map<eastl::string, rmember_type> name_to_member_map_;

#ifdef NCPP_ENABLE_METADATA
		public:
			metadata_type metadata;
#endif



		public:
			inline const eastl::unordered_map<eastl::string, rmember_type>& name_to_member_map() const { return name_to_member_map_; }
			inline b8 is_has_member(const eastl::string& member_name) const { return name_to_member_map_.find(member_name) != name_to_member_map_.end(); }
			inline const rmember_type& member(const eastl::string& member_name) const {

				assert(is_has_member(member_name));

				return name_to_member_map_.find(member_name)->second;
			}



		public:
			rcontext_t() {


			}
			~rcontext_t() {


			}



		public:
			template<typename type__>
			void reflect_type_t() {

				auto _ = type__::reflector_container(*this);

			}
			template<typename base_type__>
			void reflect_base_t(const eastl::string& name) {

				if (!is_has_base()) {

					base_name_ = name;
					base_hash_code_ = typeid(base_type__).hash_code();

				}

				reflect_type_t<base_type__>();

			}



		public:
			template<typename type__, std::enable_if_t<is_support_virtual_t<type__>, i32> = 0>
			void reflect_t(const type__& object) {

				object.virtual_reflect(*this);

			}
			template<typename type__, std::enable_if_t<!is_support_virtual_t<type__>, i32> = 0>
			void reflect_t(const type__& object) {

				reflect_type_t<type__>();

			}



		public:
			template<
				typename object_type__, typename member_type__, member_offset_getter_type member_offset_getter__,
				std::enable_if_t<!utilities::is_function_t<member_type__>::value, i32> = 0
			>
			void add_member_t(const eastl::string& member_name) {

				assert(!is_has_member(member_name));

				name_to_member_map_[member_name] = {
				
					[](void* object_p, u32 tabs, std::ostream& os) -> std::ostream& {
						
						return safe_ostream_with_tab_t<std::ostream, ostream_input_t<member_type__>>(
							os,
							ostream_input_t<member_type__>{ 
								*reinterpret_cast<member_type__*>(
									reinterpret_cast<u8*>(object_p) + member_offset_getter__()
								),
								tabs 
							}
						);

						return os;
					}
				
				};

			}
			template<
				typename object_type__, typename member_type__, member_offset_getter_type member_offset_getter__,
				std::enable_if_t<utilities::is_function_t<member_type__>::value, i32> = 0
			>
			void add_member_t(const eastl::string& member_name) {

				assert(!is_has_member(member_name));

				name_to_member_map_[member_name] = {

					[](void* object_p, u32 tabs, std::ostream& os) -> std::ostream& {

						return safe_ostream_with_tab_t<std::ostream, const char*>(
							os,
							ostream_input_t<const char*> {
								("\x1B[33m" + eastl::string(typeid(member_type__).name()) + "\033[0m").c_str(),
								tabs
							}
						);
					}

				};

			}
			void remove_member(const eastl::string& member_name) {

				assert(is_has_member(member_name));

				name_to_member_map_.erase(member_name);

			}

		};
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
		template<class rtti_traits__, typename object_type__, typename member_type__, member_offset_getter_type member_offset_getter__, name_getter_type name_getter__>
		struct member_reflector_t {

		public:
			member_reflector_t() {

				current_context_t<rtti_traits__>().add_member_t<object_type__, member_type__, member_offset_getter__>(name_getter__());

			}

		};



		template<class rtti_traits__, typename base_type__, name_getter_type name_getter__>
		struct base_reflector_t {

		public:
			base_reflector_t() {

				current_context_t<rtti_traits__>().reflect_base_t<base_type__>(name_getter__());

			}

		};
#endif



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_RTTI
#define NCPP_ROBJECT(RTTITraits, ClassName,...) \
			NCPP_PUBLIC_KEYWORD\
				using rtti_traits = RTTITraits;\
				\
			NCPP_PRIVATE_KEYWORD\
				friend class ncpp::rtti::rcontext_base;\
				\
				friend class ncpp::rtti::rcontext_t<rtti_traits>;\
				friend struct ncpp::rtti::rmember_t<rtti_traits>;\
			\
			NCPP_PUBLIC_KEYWORD\
				using current_class = ClassName;\
				static inline eastl::string static_name() { return #ClassName; }\
				using rcontext_type = ncpp::rtti::rcontext_t<rtti_traits>;\
				using rmember_type = ncpp::rtti::rmember_t<rtti_traits>;\
			\
			NCPP_PUBLIC_KEYWORD friend void operator << (current_class&, const ncpp::rtti::robject_flag& flag) { }\
			\
			NCPP_PRIVATE_KEYWORD\
				template<typename in_data__, typename in_reflector__>\
				using dr_pair_t = typename ncpp::utilities::nth_template_arg_t<0, in_data__, in_reflector__>::type;\
			\
				__VA_ARGS__\
			\
			NCPP_PRIVATE_KEYWORD\
				struct reflector_container;\
				friend struct reflector_container;\
				struct reflector_container : public ncpp::rtti::reflector_container_base {\
					\
					NCPP_PRIVATE_KEYWORD\
						template<typename in_data__, typename in_reflector__>\
						using dr_pair_t = typename ncpp::utilities::nth_template_arg_t<1, in_data__, in_reflector__>::type;\
					\
					__VA_ARGS__\
					\
					NCPP_PUBLIC_KEYWORD reflector_container(rcontext_type& context) : ncpp::rtti::reflector_container_base(context) {\
						apply_name(context, #ClassName);\
						apply_hash_code(context, typeid(current_class).hash_code());\
					}\
				};
#else
#define NCPP_ROBJECT(RTTITraits, ClassName,...) \
			\
			NCPP_PUBLIC_KEYWORD\
				using current_class = ClassName;\
				static inline eastl::string static_name() { return #ClassName; }\
			\
			NCPP_PUBLIC_KEYWORD friend void operator << (current_class&, const ncpp::rtti::robject_flag& flag) { }\
			\
				__VA_ARGS__
#endif

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#ifdef NCPP_ENABLE_RTTI
#define NCPP_MEMBER(Type, Name,...) dr_pair_t<Type, void()> Name;\
			NCPP_PRIVATE_KEYWORD static inline eastl::string Name##_name_cstr() { return #Name; }\
			NCPP_PRIVATE_KEYWORD static inline sz Name##_member_offset() { return ncpp::utilities::member_offset_t(&current_class::Name); }\
			NCPP_PRIVATE_KEYWORD dr_pair_t<void(), ncpp::rtti::member_reflector_t<rtti_traits, current_class, Type, &current_class::Name##_member_offset, &current_class::Name##_name_cstr>> Name##_reflector;
#else
#define NCPP_MEMBER(Type, Name,...) using Name##_type = Type;\
			Name##_type Name;
#endif

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_PRIVATE(Type, Name,...) NCPP_PRIVATE_KEYWORD NCPP_MEMBER(Type, Name, __VA_ARGS__)
#define NCPP_PROTECTED(Type, Name,...) NCPP_PROTECTED_KEYWORD NCPP_MEMBER(Type, Name, __VA_ARGS__)
#define NCPP_PUBLIC(Type, Name,...) NCPP_PUBLIC_KEYWORD NCPP_MEMBER(Type, Name, __VA_ARGS__)

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#ifdef NCPP_ENABLE_RTTI
#define NCPP_BASE(Name) \
			NCPP_PUBLIC_KEYWORD static inline eastl::string base_name_cstr() { return #Name; }\
			NCPP_PRIVATE_KEYWORD dr_pair_t<void(), ncpp::rtti::base_reflector_t<rtti_traits, Name, &current_class::base_name_cstr>> base##_reflector;
#else
#define NCPP_BASE(Name)
#endif

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#ifdef NCPP_ENABLE_RTTI
#define NCPP_SUPPORT_VIRTUAL()\
			NCPP_PUBLIC_KEYWORD friend current_class& operator << (current_class&, const dr_pair_t<ncpp::rtti::robject_support_virtual_flag, b8***>& flag) { return *reinterpret_cast<current_class*>(0); }\
			NCPP_PRIVATE_KEYWORD virtual void virtual_reflect(rcontext_type& context) const { context.reflect_type_t<current_class>(); }
#else
#define NCPP_SUPPORT_VIRTUAL()
#endif

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

#define NCPP_RCLASS(RTTITraits, ClassName,...) NCPP_ROBJECT(RTTITraits, ClassName, NCPP_SUPPORT_VIRTUAL(); __VA_ARGS__)
#define NCPP_RSTRUCT(RTTITraits, ClassName,...) NCPP_ROBJECT(RTTITraits, ClassName, __VA_ARGS__)
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



template<typename item_type__, std::enable_if_t<ncpp::rtti::is_robject_t<item_type__>, ncpp::i32> = 0>
std::ostream& operator << (
	std::ostream& os,
	const ncpp::ostream_input_t<
		item_type__
	>& input
)
{

	if (input.second > NCPP_MAX_TAB_COUNT) {

		os << ncpp::cout_lowlight("...");

		return os;
	}



#ifdef NCPP_ENABLE_RTTI

	typename item_type__::rcontext_type ctx;
	ctx.reflect_t(input.first);



	os << ("\x1B[33m" + ctx.name() + "\033[0m").c_str();

	if (ctx.base_hash_code())
		os << ncpp::cout_lowlight(" extends ") << ("\x1B[34m" + ctx.base_name() + "\033[0m").c_str();

	os << " ";

	os << ncpp::cout_lowlight("{") << std::endl;



	ncpp::u32 member_count = ctx.name_to_member_map().size();



	auto member_it = ctx.name_to_member_map().begin();

	for (ncpp::sz i = 0; i < member_count; ++i) {

		for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}

		os << ncpp::cout_field_name(member_it->first) << ncpp::cout_lowlight(": ");

		member_it->second.ostream((void*)(&(input.first)), input.second + 1, os);

		if (i != member_count - 1)
			os << ncpp::cout_lowlight(",");

		os << std::endl;

		++member_it;

	}



	for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

		os << " ";

	}
	os << ncpp::cout_lowlight("}");

#else
	os << ("\x1B[33m" + eastl::string(typeid(item_type__).name()) + "\033[0m").c_str();
	os << ncpp::cout_lowlight(" { }");
#endif

	return os;
}

template<typename item_type__, std::enable_if_t<ncpp::rtti::is_robject_t<item_type__>, ncpp::i32> = 0>
std::ostream& operator << (
	std::ostream& os,
	const item_type__& input
)
{

	os << ncpp::ostream_input_t<item_type__> { input, 0 };

	return os;
}