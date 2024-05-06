#pragma once

/** @file ncpp/object.hpp
*	@brief Implement object.
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

#include <ncpp/mem/default_allocator.hpp>
#include <ncpp/mem/object_allocator.hpp>
#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/utilities/mem_wrap.hpp>
#include <ncpp/utilities/alignof.hpp>
#include <ncpp/utilities/singleton.hpp>
#include <ncpp/utilities/unique_lock.hpp>
#include <ncpp/utilities/cpass.hpp>
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/pac/thread_index.hpp>
#include <ncpp/pac/spin_lock.hpp>

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

#define NCPP_OBJECT_FRIEND_CLASSES() \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_key_subpool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_key_pool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_manager;                                        \
                                                    \
            template<typename F_object_fr__, typename F_requirements_fr__>\
            friend class ncpp::TW_oref;\
            template<typename F_object_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements_fr__>\
            friend class ncpp::TK_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements_fr__>\
            friend class ncpp::TU_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements_fr__>\
            friend class ncpp::TS_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements_fr__>\
            friend class ncpp::TX_oref;

	using F_object_destructor_caller = void(*)(void*);



#define NCPP_OBJECT_COUNTER_MEMORY_OFFSET (0)
#define NCPP_OBJECT_KEY_MEMORY_OFFSET ( \
                (NCPP_OBJECT_COUNTER_MEMORY_OFFSET + sizeof(ncpp::u64))\
			)
#define NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET ( \
                NCPP_OBJECT_KEY_MEMORY_OFFSET + sizeof(ncpp::u64)                             \
			)
#define NCPP_OBJECT_MEMORY_OFFSET ( \
                NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET + sizeof(ncpp::u64)                             \
			)
#define NCPP_OBJECT_MEMORY_HEADER_SIZE NCPP_OBJECT_MEMORY_OFFSET

#define NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE (NCPP_OBJECT_MEMORY_HEADER_SIZE - NCPP_OBJECT_COUNTER_MEMORY_OFFSET)
#define NCPP_OBJECT_KEY_MEMORY_OFFSET_REVERSE (NCPP_OBJECT_MEMORY_HEADER_SIZE - NCPP_OBJECT_KEY_MEMORY_OFFSET)
#define NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET_REVERSE (NCPP_OBJECT_MEMORY_HEADER_SIZE - NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET)

#define NCPP_RAW_P_TO_COUNTER_P(...) ( \
                (ncpp::au32*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_COUNTER_MEMORY_OFFSET                            \
				)                                     \
			)
#define NCPP_RAW_P_TO_KEY_P(...) ( \
                (ncpp::F_object_key*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_KEY_MEMORY_OFFSET                    \
				)                                     \
			)
#define NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(...) ( \
                (ncpp::F_object_destructor_caller*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET                        \
				)                                     \
			)
#define NCPP_RAW_P_TO_OBJECT_P(...) ( \
                (void*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_MEMORY_OFFSET                        \
				)                                     \
			)

#define NCPP_OBJECT_P_TO_COUNTER_P(...) ( \
                (ncpp::au32*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		- NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)
#define NCPP_OBJECT_P_TO_KEY_P(...) ( \
                (ncpp::F_object_key*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		- NCPP_OBJECT_KEY_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)
#define NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(...) ( \
                (ncpp::F_object_destructor_caller*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		- NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)

#define NCPP_COUNTER_P_TO_OBJECT_P(...) ( \
                (void*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)
#define NCPP_KEY_P_TO_OBJECT_P(...) ( \
                (void*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_KEY_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)
#define NCPP_DESTRUCTOR_CALLER_P_TO_OBJECT_P(...) ( \
                (void*)                          \
				( \
					((ncpp::u8*)(__VA_ARGS__))            \
            		+ NCPP_OBJECT_DESTRUCTOR_CALLER_MEMORY_OFFSET_REVERSE                              \
				)                                     \
			)



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_OBJECT_IMPLEMENT(...) \
            NCPP_OBJECT_FRIEND_CLASSES()

#define NCPP_OBJECT_THREAD_SAFE() \
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::F_object_thread_safe_flag);



    NCPP_RTTI_CREATE_FLAG(F_object_thread_safe_flag);
    NCPP_RTTI_CREATE_FLAG(F_oref_flag);

    template<typename F__>
    concept T_is_object_thread_safe = NCPP_RTTI_IS_HAS_FLAG(F__, F_object_thread_safe_flag);
    template<typename F__>
    concept T_is_oref = NCPP_RTTI_IS_HAS_FLAG(F__, F_oref_flag);

    struct F_object_key {

        union {

            u64 value = NCPP_U64_MAX;

            struct {

                u32 id : 32;
                u32 generation : 31;
                u32 is_thread_safe : 1;

            };

        };

        NCPP_FORCE_INLINE constexpr F_object_key() noexcept = default;
        NCPP_FORCE_INLINE constexpr F_object_key(F_null) noexcept : value(NCPP_U64_MAX) {}

        NCPP_FORCE_INLINE constexpr F_object_key(u64 value_in) noexcept :
            value(value_in)
        {}
        NCPP_FORCE_INLINE constexpr F_object_key(u32 id_in, u32 generation_in, b8 is_thread_safe_in) noexcept :
            id(id_in),
            generation(generation_in),
            is_thread_safe(is_thread_safe_in)
        {

        }



        NCPP_FORCE_INLINE constexpr operator u64 () const noexcept {

            return value;
        }

        friend NCPP_FORCE_INLINE constexpr b8 operator == (F_object_key a, F_object_key b) noexcept {

            return (a.id == b.id) && (a.generation == b.generation);
        }
        friend NCPP_FORCE_INLINE constexpr b8 operator != (F_object_key a, F_object_key b) noexcept {

            return (a.id != b.id) || (a.generation != b.generation);
        }



        NCPP_FORCE_INLINE constexpr b8 is_valid() const noexcept {

            return (id != NCPP_U32_MAX);
        }
        NCPP_FORCE_INLINE constexpr b8 is_null() const noexcept {

            return (id == NCPP_U32_MAX);
        }



        NCPP_FORCE_INLINE constexpr void reset() noexcept {

            id = NCPP_U32_MAX;
        }

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



#define NCPP_ASSERT_OREF_REQUIREMENTS(...) \
            NCPP_ENABLE_IF_DEBUG( \
                std::remove_const_t<std::remove_pointer_t<decltype(__VA_ARGS__)>>::F_requirements::T_assert(*(__VA_ARGS__))                    \
            );

	namespace internal
	{
		struct F_this_oref_getter
		{
			static NCPP_FORCE_INLINE const auto& invoke(const auto& o)
			{
				return o.this_oref_internal();
			}
		};
	}

    template<class F_requirements__, b8 is_always_valid__ = false>
    struct TF_requirements_base {

        static constexpr b8 is_always_valid = is_always_valid__;



        template<
            class F_passed_oref__,
            class F_requirements_binded_oref__ = std::remove_const_t<std::remove_reference_t<F_passed_oref__>>::template TF_bind_requirements<F_requirements__>,
            typename F_return__ = utilities::TF_nth_template_targ<
                std::is_lvalue_reference_v<F_passed_oref__>,
                utilities::TF_nth_template_targ<
                    std::is_const_v<std::remove_reference_t<F_passed_oref__>>,
                    F_requirements_binded_oref__,
                    const F_requirements_binded_oref__
                >&&,
                utilities::TF_nth_template_targ<
                    std::is_const_v<std::remove_reference_t<F_passed_oref__>>,
                    F_requirements_binded_oref__,
                    const F_requirements_binded_oref__
                >&
            >
        >
        static NCPP_FORCE_INLINE F_return__ T_forward(F_passed_oref__&& oref) noexcept
        {

            NCPP_ENABLE_IF_DEBUG(
                F_requirements__::T_assert(internal::F_this_oref_getter::invoke(oref));
            );

            return ((F_return__)oref);
        }

        template<
            class F_passed_oref__,
            class F_requirements_binded_oref__ = std::remove_const_t<std::remove_reference_t<F_passed_oref__>>::template TF_bind_requirements<F_requirements__>,
            typename F_return__ = utilities::TF_nth_template_targ<
                std::is_const_v<std::remove_reference_t<F_passed_oref__>>,
                F_requirements_binded_oref__,
                const F_requirements_binded_oref__
            >&&
        >
        static NCPP_FORCE_INLINE F_return__ T_move(F_passed_oref__&& oref) noexcept
        {

            NCPP_ENABLE_IF_DEBUG(
                F_requirements__::T_assert(internal::F_this_oref_getter::invoke(oref));
            );

            return ((F_return__)oref);
        }



        template<T_is_oref F_oref__>
        static NCPP_FORCE_INLINE void T_assert(const F_oref__& oref) noexcept {

            NCPP_ASSERT(F_requirements__::T_check(oref))
				<< "requirements are not satisfied"
				<< std::endl
				<< "struct: " << T_cout_value(utilities::T_type_fullname<F_requirements__>())
				<< std::endl
				<< "object pointer: " << T_cout_value(oref.object_p_unsafe());
        }

    };

    struct F_no_requirements : public TF_requirements_base<F_no_requirements> {

        template<T_is_oref F_oref__>
        static NCPP_FORCE_INLINE b8 T_check(const F_oref__& oref) noexcept {

            return true;
        }

    };

    struct F_valid_requirements : public TF_requirements_base<F_valid_requirements, true> {

        template<T_is_oref F_oref__>
        static NCPP_FORCE_INLINE b8 T_check(const F_oref__& oref) noexcept {

            return oref.NQ_is_valid();
        }

    };

#define NCPP_FHANDLE_TEMPLATE_ADVANCED(Name, NamePrefixConnector, OrefIndex, PreClassKeyword, ...) \
                                                                                        \
            template<ncpp::T_is_oref F_oref__>\
            __VA_OPT__(requires std::is_base_of_v<__VA_ARGS__, typename F_oref__::F_object>) \
			struct TF##NamePrefixConnector##Name;                                                                          \
                                                                                        \
            __VA_OPT__(using U##OrefIndex##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TU<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using K##OrefIndex##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TK<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using S##OrefIndex##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TS<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using X##OrefIndex##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TX<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using K##OrefIndex##_valid##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TK_valid<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using S##OrefIndex##_valid##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TS_valid<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using X##OrefIndex##_valid##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TX_valid<__VA_ARGS__>>;) \
                                                                                        \
            __VA_OPT__(using UPA##OrefIndex##NamePrefixConnector##Name = TF##NamePrefixConnector##Name<ncpp::TU<__VA_ARGS__>>&&;) \
                                                                                        \
            __VA_OPT__(using KPA##OrefIndex##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TK<__VA_ARGS__>>&;) \
                                                                                        \
            __VA_OPT__(using SPA##OrefIndex##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TS<__VA_ARGS__>>&;) \
                                                                                        \
            __VA_OPT__(using XPA##OrefIndex##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TX<__VA_ARGS__>>&;) \
                                                                                        \
            __VA_OPT__(using KPA##OrefIndex##_valid##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TK_valid<__VA_ARGS__>>&;) \
                                                                                        \
            __VA_OPT__(using SPA##OrefIndex##_valid##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TS_valid<__VA_ARGS__>>&;) \
                                                                                        \
            __VA_OPT__(using XPA##OrefIndex##_valid##NamePrefixConnector##Name = const TF##NamePrefixConnector##Name<ncpp::TX_valid<__VA_ARGS__>>&;) \
                                                                                        \
            template<ncpp::T_is_oref F_oref__>\
            __VA_OPT__(requires std::is_base_of_v<__VA_ARGS__, typename F_oref__::F_object>) \
			struct PreClassKeyword TF##NamePrefixConnector##Name

#define NCPP_FHANDLE_TEMPLATE(Name, ...) NCPP_FHANDLE_TEMPLATE_ADVANCED(Name,_,,,__VA_ARGS__)
#define NCPP_FHANDLE2_TEMPLATE(Name, ...) NCPP_FHANDLE_TEMPLATE_ADVANCED(Name,_,2,,__VA_ARGS__)

#define NCPP_FHANDLE_TEMPLATE_DEFINE_MEMBER_ADVANCED(NamePrefixConnector, OrefIndex, ...) \
            template<ncpp::T_is_oref F_oref__>\
            __VA_OPT__(requires std::is_base_of_v<__VA_ARGS__, typename F_oref__::F_object>)

#define NCPP_FHANDLE_TEMPLATE_DEFINE_MEMBER(...) NCPP_FHANDLE_TEMPLATE_DEFINE_MEMBER_ADVANCED(_,,__VA_ARGS__)
#define NCPP_FHANDLE2_TEMPLATE_DEFINE_MEMBER(...) NCPP_FHANDLE_TEMPLATE_DEFINE_MEMBER_ADVANCED(_,2,__VA_ARGS__)

#define NCPP_FHANDLE_GENERATED_BODY_ADVANCED(Name, NamePrefixConnector, ...) \
            public:\
                using F_oref = F_oref__;       \
\
            public:\
                template<typename F_new_requirements__>\
                using TF_bind_requirements = TF##NamePrefixConnector##Name<  \
					typename F_oref::template TF_bind_requirements<F_new_requirements__>\
                >;                                                             \
                template<typename F_passed_object_in__>\
                using TF_bind_passed_object = TF##NamePrefixConnector##Name< \
					typename F_oref::template TF_bind_passed_object<F_passed_object_in__>\
				>;                                                         \
                                               \
            private:\
				friend ncpp::internal::F_this_oref_getter;\
                NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return oref; } \
                                               \
            private:                               \
                using F_this = TF##NamePrefixConnector##Name<F_oref>;\
                \
            public:\
                template<ncpp::T_is_oref F_oref_in__>\
                __VA_OPT__(requires std::is_base_of_v<__VA_ARGS__, typename F_oref__::F_object>)\
                using TF_forward_oref = TF##NamePrefixConnector##Name<F_oref_in__>;\
                \
            public:\
                F_oref__ oref;\
                \
            public:\
                NCPP_FORCE_INLINE operator F_oref__() noexcept {\
                \
                    return oref;\
                }\
                NCPP_FORCE_INLINE operator bool() const noexcept {\
                \
                    return oref.is_valid();\
                }\
                NCPP_FORCE_INLINE bool is_valid() const noexcept {\
                \
                    return oref.is_valid();\
                }\
                NCPP_FORCE_INLINE bool is_null() const noexcept {\
                \
                    return oref.is_null();\
                }\
                NCPP_FORCE_INLINE bool NQ_is_valid() const noexcept {\
                \
                    return oref.NQ_is_valid();\
                }\
                NCPP_FORCE_INLINE bool NQ_is_null() const noexcept {\
                \
                    return oref.NQ_is_null();\
                }\
                NCPP_FORCE_INLINE bool Q_is_valid() const noexcept {\
                \
                    return oref.Q_is_valid();\
                }\
                NCPP_FORCE_INLINE bool Q_is_null() const noexcept {\
                \
                    return oref.Q_is_null();\
                }\
                NCPP_FORCE_INLINE typename F_oref__::F_passed_object* operator ->() const noexcept {\
                \
                    return (typename F_oref__::F_passed_object*)(oref.object_p());\
                }\
                NCPP_FORCE_INLINE typename F_oref__::F_passed_object& operator *() const noexcept {\
                \
                    return *((typename F_oref__::F_passed_object*)(oref.object_p()));\
                }                              \
                                               \
            public:                            \
				NCPP_FORCE_INLINE void reset() {                                         \
                                                                             \
                	oref.reset();                                                             \
				}\
                                               \
            public:                            \
                template<typename F_other_p__>\
                requires ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_up_cast() & noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_up_cast() const & noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_up_cast() && noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_up_cast() const && noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_down_cast() & noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_down_cast() const & noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_down_cast() && noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
                template<typename F_other_p__>\
                requires ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_down_cast() const && noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
\
                template<typename F_other_p__>\
                requires (ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__> || ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>)\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_cast() & noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires (ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__> || ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>)\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_cast() const & noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                requires (ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__> || ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>)\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_cast() && noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
                template<typename F_other_p__>\
                requires (ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, F_other_p__> || ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, F_other_p__>)\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_cast() const && noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
\
                template<typename F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_force_cast() & noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>& T_force_cast() const & noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&)*this;\
                }\
                template<typename F_other_p__>\
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_force_cast() && noexcept {\
\
                    return (TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }\
                template<typename F_other_p__>\
                NCPP_FORCE_INLINE const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&& T_force_cast() const && noexcept {\
\
                    return (const TF##NamePrefixConnector##Name<typename F_oref__::template TF_bind_passed_object<F_other_p__>>&&)*this;\
                }                                                            \
                                                                                              \
            public:                            \
                NCPP_FORCE_INLINE TF##NamePrefixConnector##Name<             \
				  	std::remove_const_t<std::remove_reference_t<decltype(oref.keyed())>>\
				> keyed() const noexcept {\
\
                    return { oref.keyed() };\
                }\
                                               \
            public:                            \
                NCPP_FORCE_INLINE TF_bind_requirements<ncpp::F_no_requirements>& no_requirements() & noexcept {\
\
                    return (TF_bind_requirements<ncpp::F_no_requirements>&)*this;\
                }\
                NCPP_FORCE_INLINE const TF_bind_requirements<ncpp::F_no_requirements>& no_requirements() const & noexcept {\
\
                    return (const TF_bind_requirements<ncpp::F_no_requirements>&)*this;\
                }\
                NCPP_FORCE_INLINE TF_bind_requirements<ncpp::F_no_requirements>&& no_requirements() && noexcept {\
\
                    return (TF_bind_requirements<ncpp::F_no_requirements>&&)*this;\
                }\
                NCPP_FORCE_INLINE const TF_bind_requirements<ncpp::F_no_requirements>&& no_requirements() const && noexcept {\
\
                    return (const TF_bind_requirements<ncpp::F_no_requirements>&&)*this;\
                }\
\
                template<typename F_requirements_in__ = ncpp::F_no_requirements>\
                NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {\
\
                    return (TF_bind_requirements<F_requirements_in__>&)*this;\
                }\
                template<typename F_requirements_in__ = ncpp::F_no_requirements>\
                NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {\
\
                    return (TF_bind_requirements<F_requirements_in__>&&)*this;\
                }\
                template<typename F_requirements_in__ = ncpp::F_no_requirements>\
                NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {\
\
                    return (const TF_bind_requirements<F_requirements_in__>&)*this;\
                }\
                template<typename F_requirements_in__ = ncpp::F_no_requirements>\
                NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {\
\
                    return (const TF_bind_requirements<F_requirements_in__>&&)*this;\
                }                                                            \
			public:                                                                   \
				template<ncpp::T_is_oref F_other_oref__>\
				requires ncpp::T_is_object_down_castable<typename F_oref__::F_passed_object, typename F_other_oref__::F_passed_object>   \
					&& std::is_same_v<typename F_oref__::F_requirements, typename F_other_oref__::F_requirements>\
				NCPP_FORCE_INLINE operator TF##NamePrefixConnector##Name<F_other_oref__> () const noexcept {\
			\
					return { (const F_other_oref__&)oref };\
				}\
				template<ncpp::T_is_oref F_other_oref__>\
				requires ncpp::T_is_object_up_castable<typename F_oref__::F_passed_object, typename F_other_oref__::F_passed_object>\
					&& std::is_same_v<typename F_oref__::F_requirements, typename F_other_oref__::F_requirements>\
				explicit NCPP_FORCE_INLINE operator TF##NamePrefixConnector##Name<F_other_oref__> () const noexcept {\
			\
					return { (const F_other_oref__&)oref };\
				}

#define NCPP_FHANDLE_GENERATED_BODY(Name, ...) NCPP_FHANDLE_GENERATED_BODY_ADVANCED(Name,_,__VA_ARGS__)

#define NCPP_FHANDLE_CHECK(...) ((__VA_ARGS__).oref.is_valid())

// uses to cast from an oref or an object handle to keyed valid form
#define NCPP_FOH_VALID(...) ncpp::F_valid_requirements::T_forward((__VA_ARGS__).keyed())
// uses to cast from an oref or an object handle to keyed valid form, 
// but recommended to use NCPP_FOH_VALID(...) insteads
#define NCPP_FOREF_VALID(...) ncpp::F_valid_requirements::T_forward((__VA_ARGS__).keyed())
// uses to cast from an object handle to keyed valid form
#define NCPP_FHANDLE_VALID(...) std::remove_const_t< \
                std::remove_reference_t<             \
                    decltype(__VA_ARGS__)            \
                >                                    \
            >::template TF_forward_oref<             \
                ncpp::TK_valid<                      \
                    typename std::remove_const_t<    \
                        std::remove_reference_t<     \
                            decltype(__VA_ARGS__)    \
                        >                            \
                    >::F_oref::F_passed_object       \
                >                                    \
            > { NCPP_FOREF_VALID((__VA_ARGS__).oref) }
// uses to cast from an object handle to keyed valid oref
#define NCPP_FHANDLE_VALID_AS_OREF(...) (NCPP_FHANDLE_VALID(__VA_ARGS__).oref)
// uses to cast from an oref or an object handle to keyed valid oref
#define NCPP_AOH_VALID(...) (ncpp::internal::F_this_oref_getter::invoke(NCPP_FOH_VALID(__VA_ARGS__)))

#define NCPP_FHANDLE_REWRAP(...) { (__VA_ARGS__).oref }



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_key_subpool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_key_pool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_manager;

    template<typename F_passed_object__, typename F_requirements__>
    class TW_oref;
    template<typename F_passed_object__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TK_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TU_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TS_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TX_oref;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_key_subpool;

    template<typename F_allocator__>
    class TF_default_object_key_subpool<true, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;



    private:
        u32 index_ = 0;
        u32 object_key_begin_index_ = 0;
        u32 max_local_generation_count_ = 0;
        u32 subpool_count_ = 0;

        struct F_generation_buffer {

            u32* generation_p = 0;
            u32* next_p = 0;
            u32 size = 0;
            mutable pac::TF_spin_lock<false, true> lock;

            ~F_generation_buffer(){

                mem::F_default_allocator allocator;

                if(size) {

                    allocator.deallocate(generation_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                sz buffer_size_in_bytes = sizeof(u32) * new_size;
                u32* new_generation_p = (u32*)allocator.allocate(
                    2 * buffer_size_in_bytes,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = new_generation_p + new_size;

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, 2 * min_size * sizeof(u32));

                    allocator.deallocate(generation_p);

                }

                generation_p = new_generation_p;
                next_p = new_next_p;
                size = new_size;

            }

            NCPP_FORCE_INLINE void ensure_concurrent(u32 min_size) noexcept {

                lock.wlock();

                if(min_size > size) {

                    resize(min_size);

                }

                lock.wunlock();

            }

        };
        F_generation_buffer generation_buffer_;

        au32 free_generation_tail_index_ = NCPP_U32_MAX;
        au32 generation_capacity_ = 0;



    public:
        NCPP_FORCE_INLINE u32 index() const noexcept { return index_; }
        NCPP_FORCE_INLINE u32 subpool_count() const noexcept { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const noexcept { return max_local_generation_count_; }



    public:
        TF_default_object_key_subpool()
        {
        }



    private:
        inline b8 try_optain_generation(u32 free_generation_tail_index, u32& out_free_generation_tail_index, u32& out_generation_index, u32& out_generation) noexcept {

            if(free_generation_tail_index == NCPP_U32_MAX){

                out_generation_index = generation_capacity_.fetch_add(1, eastl::memory_order_acq_rel);

                generation_buffer_.ensure_concurrent(out_generation_index + 1);

                generation_buffer_.lock.rlock();
                generation_buffer_.generation_p[out_generation_index] = 0;
                generation_buffer_.lock.runlock();

                out_generation = 0;

                return true;
            }
            else{

                generation_buffer_.lock.rlock();
                u32 next_free_generation_tail_index = generation_buffer_.next_p[free_generation_tail_index];
                out_generation = generation_buffer_.generation_p[free_generation_tail_index];
                generation_buffer_.lock.runlock();

                out_free_generation_tail_index = next_free_generation_tail_index;
                out_generation_index = free_generation_tail_index;

                return false;
            }

        }
        inline void optain_generation(u32& out_generation_index, u32& out_generation) noexcept {

            u32 free_generation_tail_index = free_generation_tail_index_.load(eastl::memory_order_acquire);

            u32 obtained_generation_index = NCPP_U32_MAX;
            u32 new_free_generation_tail_index = NCPP_U32_MAX;

            b8 is_special = try_optain_generation(
                free_generation_tail_index,
                new_free_generation_tail_index,
                obtained_generation_index,
                out_generation
            );

            while(
                free_generation_tail_index_.compare_exchange_weak(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    eastl::memory_order_acq_rel
                )
                && !is_special
            ) {

                is_special = try_optain_generation(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    obtained_generation_index,
                    out_generation
                );

            }

            out_generation_index = obtained_generation_index;

        }

        inline void try_free_generation(u32 generation_index, u32 free_generation_tail_index, u32& out_free_generation_tail_index) noexcept {

            generation_buffer_.lock.rlock();
            generation_buffer_.next_p[generation_index] = free_generation_tail_index;
            generation_buffer_.lock.runlock();

            out_free_generation_tail_index = generation_index;

        }
        inline void free_generation(u32 generation_index) noexcept {

            generation_buffer_.lock.rlock();
            ++(generation_buffer_.generation_p[generation_index]);
            generation_buffer_.lock.runlock();

            u32 free_generation_tail_index = free_generation_tail_index_.load(eastl::memory_order_acquire);

            u32 new_free_generation_tail_index = NCPP_U32_MAX;

            try_free_generation(generation_index, free_generation_tail_index, new_free_generation_tail_index);

            while(
                free_generation_tail_index_.compare_exchange_weak(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    eastl::memory_order_acq_rel
                )
            )
            {

                try_free_generation(generation_index, free_generation_tail_index, new_free_generation_tail_index);

            }

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 generation_index = NCPP_U32_MAX;
            u32 generation = NCPP_U32_MAX;
            optain_generation(generation_index, generation);

            NCPP_ASSERT(generation_index != NCPP_U32_MAX) << "invalid generation index";
            NCPP_ASSERT(generation != NCPP_U32_MAX) << "invalid generation";

            return F_object_key{
                generation_index,
                generation,
                true
            };
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            free_generation(object_key.id);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            generation_buffer_.lock.rlock();

			if(object_key.id >= generation_buffer_.size) {

				generation_buffer_.lock.runlock();
				return false;
			}

			b8 result = (generation_buffer_.generation_p[object_key.id] == object_key.generation);
			generation_buffer_.lock.runlock();

			return result;
        }

    };



    template<typename F_allocator__>
    class TF_default_object_key_subpool<false, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;



    private:
        struct F_generation_buffer {

            u32* generation_p = 0;
            u32* next_p = 0;
            u32 size = 0;

            ~F_generation_buffer(){

                mem::F_default_allocator allocator;

                if(size) {

                    allocator.deallocate(generation_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                sz buffer_size_in_bytes = sizeof(u32) * new_size;
                u32* new_generation_p = (u32*)allocator.allocate(
                    2 * buffer_size_in_bytes,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = new_generation_p + new_size;

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, 2 * min_size * sizeof(u32));

                    allocator.deallocate(generation_p);

                }

                generation_p = new_generation_p;
                next_p = new_next_p;
                size = new_size;

            }

            NCPP_FORCE_INLINE void ensure(u32 min_size) noexcept {

                if(min_size > size) {

                    resize(min_size);

                }

            }

        };
        F_generation_buffer generation_buffer_;

        u32 free_generation_tail_index_ = NCPP_U32_MAX;
        u32 generation_capacity_ = 0;



    public:
        TF_default_object_key_subpool()
        {
        }



    private:
        inline void optain_generation(u32& out_generation_index, u32& out_generation) noexcept {

            if(free_generation_tail_index_ == NCPP_U32_MAX){

                out_generation_index = generation_capacity_++;

                generation_buffer_.ensure(out_generation_index + 1);

                generation_buffer_.generation_p[out_generation_index] = 0;

                out_generation = 0;
            }
            else{

                u32 next_free_generation_tail_index = generation_buffer_.next_p[free_generation_tail_index_];
                out_generation = generation_buffer_.generation_p[free_generation_tail_index_];

                out_generation_index = free_generation_tail_index_;
                free_generation_tail_index_ = next_free_generation_tail_index;
            }

        }

        inline void free_generation(u32 generation_index) noexcept {

            ++(generation_buffer_.generation_p[generation_index]);

            generation_buffer_.next_p[generation_index] = free_generation_tail_index_;

            free_generation_tail_index_ = generation_index;

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 generation_index = NCPP_U32_MAX;
            u32 generation = NCPP_U32_MAX;
            optain_generation(generation_index, generation);

            NCPP_ASSERT(generation_index != NCPP_U32_MAX) << "invalid generation index";
            NCPP_ASSERT(generation != NCPP_U32_MAX) << "invalid generation";

            return F_object_key{
                generation_index,
                generation,
                false
            };
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            free_generation(object_key.id);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

			if(object_key.id >= generation_buffer_.size)
				return false;

			return (generation_buffer_.generation_p[object_key.id] == object_key.generation);
		}

    };



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_key_pool;

    template<typename F_allocator__>
    class TF_default_object_key_pool<true, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;

        using F_subpool = TF_default_object_key_subpool<is_thread_safe>;



    private:
        u32 subpool_count_ = 1;
        u32 max_local_generation_count_ = 1;
        containers::TF_vector<F_subpool> subpool_vector_;

    public:
        NCPP_FORCE_INLINE u32 subpool_count() const { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const { return max_local_generation_count_; }
        NCPP_FORCE_INLINE const containers::TF_vector<F_subpool>& subpool_vector() const { return subpool_vector_; }



    public:
        TF_default_object_key_pool(u32 subpool_count = 1) :
                subpool_count_(subpool_count),
                subpool_vector_(subpool_count)
        {

            max_local_generation_count_ = (NCPP_U32_MAX / subpool_count);

            for(u32 i = 0; i < subpool_count; ++i) {

                subpool_vector_[i].index_ = i;
                subpool_vector_[i].object_key_begin_index_ = i * max_local_generation_count_;
                subpool_vector_[i].max_local_generation_count_ = max_local_generation_count_;
                subpool_vector_[i].subpool_count_ = subpool_count;
            }

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 thread_index = pac::thread_index();

            auto& subpool = subpool_vector_[thread_index];

            F_object_key object_key = subpool.pop();

            object_key.id += subpool.object_key_begin_index_;

            return object_key;
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            object_key.id %= max_local_generation_count_;

            subpool_vector_[object_key.id / max_local_generation_count_].push(object_key);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            if(object_key.is_null())
                return false;

			u32 subpool_index = object_key.id / max_local_generation_count_;

			if(subpool_index >= subpool_count_)
				return false;

            object_key.id %= max_local_generation_count_;

            return subpool_vector_[subpool_index].check(object_key);
        }

    };

    template<typename F_allocator__>
    class TF_default_object_key_pool<false, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;

        using F_subpool = TF_default_object_key_subpool<is_thread_safe>;



    private:
        F_subpool subpool_;

    public:
        NCPP_FORCE_INLINE const F_subpool& subpool() const { return subpool_; }



    public:
        TF_default_object_key_pool()
        {

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            return subpool_.pop();
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            subpool_.push(object_key);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            if(object_key.is_null())
                return false;

            return subpool_.check(object_key);
        }

    };

    using F_default_object_key_pool = TF_default_object_key_pool<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_manager;

    template<typename F_allocator__>
    class TF_default_object_manager<true, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;

        using F_key_pool = TF_default_object_key_pool<is_thread_safe, F_allocator>;



    private:
        F_key_pool key_pool_;

    public:
        NCPP_FORCE_INLINE F_key_pool& key_pool() noexcept { return key_pool_; }
        NCPP_FORCE_INLINE const F_key_pool& key_pool() const noexcept { return key_pool_; }



    public:
        TF_default_object_manager(u32 subpool_count) :
            key_pool_(subpool_count)
        {

        }
        ~TF_default_object_manager(){

        }

    };

    template<typename F_allocator__>
    class TF_default_object_manager<false, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;

        using F_key_pool = TF_default_object_key_pool<is_thread_safe, F_allocator>;



    private:
        F_key_pool key_pool_;

    public:
        NCPP_FORCE_INLINE F_key_pool& key_pool() noexcept { return key_pool_; }
        NCPP_FORCE_INLINE const F_key_pool& key_pool() const noexcept { return key_pool_; }



    public:
        TF_default_object_manager()
        {

        }
        ~TF_default_object_manager(){

        }

    };

    using F_default_object_manager = TF_default_object_manager<>;

    namespace internal {

        extern NCPP_API TF_default_object_manager<false> default_object_manager;
        extern NCPP_API TF_default_object_manager<true> default_object_manager_thread_safe;

        template<b8 is_thread_safe__>
        struct TF_default_object_manager_helper;
        template<>
        struct TF_default_object_manager_helper<false> {
            static NCPP_FORCE_INLINE auto& get_manager() noexcept { return default_object_manager; }
        };
        template<>
        struct TF_default_object_manager_helper<true> {
            static NCPP_FORCE_INLINE auto& get_manager() noexcept { return default_object_manager_thread_safe; }
        };

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



    template<typename F_allocator__>
    requires (!std::is_same_v<F_allocator__, mem::F_default_allocator>)
    inline void T_initialize_default_object_managers(){

        new TF_default_object_manager<true, F_allocator__>(std::thread::hardware_concurrency());
        new TF_default_object_manager<false, F_allocator__>();

    }
    template<typename F_allocator__>
    requires (!std::is_same_v<F_allocator__, mem::F_default_allocator>)
    inline void T_release_default_object_managers(){

        delete (&TF_default_object_manager<true, F_allocator__>::instance());
        delete (&TF_default_object_manager<false, F_allocator__>::instance());

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



    template<typename F_allocator__ = mem::F_default_allocator>
    struct TF_default_object_options {

        using F_this = TF_default_object_options<F_allocator__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        using F_allocator = F_allocator__;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        template<b8 is_thread_safe__ = false>
        using TF_manager = TF_default_object_manager<is_thread_safe__, F_allocator__>;

        using F_manager = TF_manager<>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        template<b8 is_thread_safe__>
        static NCPP_FORCE_INLINE auto& T_get_manager() noexcept {

            return internal::TF_default_object_manager_helper<is_thread_safe__>::get_manager();
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        static constexpr u32 initial_shared_reference_count = 1;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        template<typename F_passed_object__>
        static NCPP_FORCE_INLINE void T_shared_oref_pre_destruct(F_passed_object__*) noexcept {}

    };

    using F_default_object_options = TF_default_object_options<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F1__, typename F2__>
    concept T_is_object_down_castable = requires(F1__* p1, F2__* p2) {
        p2 = p1;
    };
    template<typename F1__, typename F2__>
    concept T_is_object_up_castable = T_is_object_down_castable<F2__, F1__> && !T_is_object_down_castable<F1__, F2__>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, typename F_requirements__ = F_no_requirements>
    using TW = TW_oref<F_passed_object__, F_requirements__>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true,
        typename F_requirements__ = F_no_requirements
    >
    using TK = TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_no_requirements
    >
    using TK2 = TK_oref<F_passed_object__, F_options__, false, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true,
        typename F_requirements__ = F_no_requirements
    >
    using TU = TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_no_requirements
    >
    using TU2 = TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true,
        typename F_requirements__ = F_no_requirements
    >
    using TS = TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_no_requirements
    >
    using TS2 = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true,
        typename F_requirements__ = F_no_requirements
    >
    using TX = TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_no_requirements
    >
    using TX2 = TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__>
    using TW_valid = TW_oref<F_passed_object__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true
    >
    using TK_valid = TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options
    >
    using TK2_valid = TK_oref<F_passed_object__, F_options__, false, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true
    >
    using TS_valid = TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options
    >
    using TS2_valid = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true
    >
    using TX_valid = TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options
    >
    using TX2_valid = TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_valid_requirements>;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	template<typename F_passed_object__, typename F_requirements__ = F_no_requirements>
	using TWPA = TW_oref<F_passed_object__, F_requirements__>;

	template<
		typename F_passed_object__,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true,
		typename F_requirements__ = F_no_requirements
	>
	using TKPA = const TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>&;

	template<
		typename F_passed_object__,
		class F_options__ = F_default_object_options,
		typename F_requirements__ = F_no_requirements
	>
	using TK2PA = const TK_oref<F_passed_object__, F_options__, false, F_requirements__>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true,
		typename F_requirements__ = F_no_requirements
	>
	using TUPA = TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>&&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		typename F_requirements__ = F_no_requirements
	>
	using TUPA2 = TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>&&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true,
		typename F_requirements__ = F_no_requirements
	>
	using TSPA = const TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		typename F_requirements__ = F_no_requirements
	>
	using TSPA2 = const TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true,
		typename F_requirements__ = F_no_requirements
	>
	using TXPA = const TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		typename F_requirements__ = F_no_requirements
	>
	using TXPA2 = const TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>&;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	template<typename F_passed_object__>
	using TWPA_valid = TW_oref<F_passed_object__, F_valid_requirements>;

	template<
		typename F_passed_object__,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true
	>
	using TKPA_valid = const TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_valid_requirements>&;

	template<
		typename F_passed_object__,
		class F_options__ = F_default_object_options
	>
	using TKPA2_valid = const TK_oref<F_passed_object__, F_options__, false, F_valid_requirements>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true
	>
	using TSPA_valid = const TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options
	>
	using TSPA2_valid = const TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_valid_requirements>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options,
		b8 is_has_object_key__ = true
	>
	using TXPA_valid = const TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>&;

	template<
		typename F_passed_object__,
		typename F_allocator__ = mem::F_object_allocator,
		class F_options__ = F_default_object_options
	>
	using TX2PA_valid = const TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_valid_requirements>&;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(...) \
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_up_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_up_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_up_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_up_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_down_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_down_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_down_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_down_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_force_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_force_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_force_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_force_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }



    template<typename F_passed_object__, typename F_requirements__ = F_no_requirements>
    class TW_oref {

    private:
    private:
        using F_this = TW_oref<F_passed_object__, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_requirements = F_requirements__;

        static constexpr b8 is_const = std::is_const_v<F_passed_object__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TW_oref<F_passed_object__, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TW_oref<F_passed_object_in__, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
            return *(object_p());
        }
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TW_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {
            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TW_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TW_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TW_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE TW_oref(const TW_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TW_oref& operator = (const TW_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TW_oref(TW_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TW_oref& operator = (TW_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref(const TW_oref<F_other_p__, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref& operator = (const TW_oref<F_other_p__, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref(TW_oref<F_other_p__, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref& operator = (TW_oref<F_other_p__, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return (F_other_p__*)object_p_;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TW_oref<F_other_p__, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            reset_no_destroy_internal();
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TW<F_passed_object>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TW<F_passed_object>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TW<F_passed_object>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TW<F_passed_object>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

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



    template<typename F_passed_object__, class F_options__ = F_default_object_options, b8 is_has_object_key__ = true, typename F_requirements__ = F_no_requirements>
    class TK_oref;

    template<typename F_passed_object__, class F_options__ = F_default_object_options, typename F_requirements__ = F_no_requirements>
    using TK2_oref = TK_oref<F_passed_object__, F_options__, false, F_requirements__>;



    NCPP_FORCE_INLINE F_object_key object_key_unsafe(void* oref) noexcept {

        return *NCPP_OBJECT_P_TO_KEY_P(oref);
    }



    template<typename F_passed_object__, class F_options__, typename F_requirements__>
    class TK_oref<F_passed_object__, F_options__, true, F_requirements__> {

    private:
        using F_this = TK_oref<F_passed_object__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_default_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TK_oref<F_passed_object__, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TK_oref<F_passed_object_in__, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_default_object_manager& default_object_manager() const noexcept { return F_options::template T_get_manager<T_is_object_thread_safe<F_object>>(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TK_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TK_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_oref(const TK_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TK_oref(TK_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            if(object_key_.is_thread_safe)
                return F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            if(object_key_.is_thread_safe)
                return !F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return !F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            if(object_key_.is_thread_safe)
                return F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            if(object_key_.is_thread_safe)
                return !F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return !F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            object_p_ = 0;
            object_key_ = 0;

        }



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE F_this& keyed() & noexcept {

            return (F_this&)(*this);
        }
        NCPP_FORCE_INLINE F_this&& keyed() && noexcept {

            return (F_this&&)(*this);
        }
        NCPP_FORCE_INLINE F_this const& keyed() const & noexcept {

            return (F_this const&)(*this);
        }
        NCPP_FORCE_INLINE F_this const&& keyed() const && noexcept {

            return (F_this const&&)(*this);
        }



    public:
        NCPP_FORCE_INLINE auto no_key() const noexcept {

            return TK_oref<F_passed_object, F_options, false, F_requirements>::unsafe(object_p_);
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TK<F_passed_object, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TK<F_passed_object, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TK<F_passed_object, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TK<F_passed_object, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

    };



    template<typename F_passed_object__, class F_options__, typename F_requirements__>
    class TK_oref<F_passed_object__, F_options__, false, F_requirements__> {

    private:
        using F_this = TK_oref<F_passed_object__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TK_oref<F_passed_object__, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TK_oref<F_passed_object_in__, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TK_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TK_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_oref(const TK_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TK_oref(TK_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

//            x.reset();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            object_p_ = 0;

        }



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE F_this& keyed() & noexcept {

            return (F_this&)(*this);
        }
        NCPP_FORCE_INLINE F_this&& keyed() && noexcept {

            return (F_this&&)(*this);
        }
        NCPP_FORCE_INLINE F_this const& keyed() const & noexcept {

            return (F_this const&)(*this);
        }
        NCPP_FORCE_INLINE F_this const&& keyed() const && noexcept {

            return (F_this const&&)(*this);
        }



    public:
        NCPP_FORCE_INLINE auto with_key_unsafe() const noexcept {

            return TK_oref<F_passed_object, F_options, true, F_requirements>::unsafe(object_p_);
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TK<F_passed_object, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TK<F_passed_object, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TK<F_passed_object, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TK<F_passed_object, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

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



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = true, typename F_requirements__ = F_no_requirements>
    class TU_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_no_requirements>
    using TU2_oref = TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_default_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TU_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TU_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_default_object_manager& default_object_manager() const noexcept { return F_options::template T_get_manager<T_is_object_thread_safe<F_object>>(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TU_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TU_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TU_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_oref(TU_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = default_object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template T_get_manager<true>().key_pool().push(object_key_);
            else
                F_options::template T_get_manager<false>().key_pool().push(object_key_);
        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_, ((F_this&)oref).object_key_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TU<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TU<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TU<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TU<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TU_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TU_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TU_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TU_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TU_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_oref(TU_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TU<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TU<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TU<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TU<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

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



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = true, typename F_requirements__ = F_no_requirements>
    class TS_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_no_requirements>
    using TS2_oref = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;



    NCPP_FORCE_INLINE u32 shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - (NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE / sizeof(u32));

        return counter_p->load(eastl::memory_order_acquire);
    }
    NCPP_FORCE_INLINE u32 increase_shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - (NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE / sizeof(u32));

        return counter_p->fetch_add(1, eastl::memory_order_acq_rel);
    }
    NCPP_FORCE_INLINE u32 decrease_shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - (NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE / sizeof(u32));

        return counter_p->fetch_sub(1, eastl::memory_order_acq_rel);
    }
    NCPP_FORCE_INLINE void set_object_counter_to_one_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - (NCPP_OBJECT_COUNTER_MEMORY_OFFSET_REVERSE / sizeof(u32));

        counter_p->store(1, eastl::memory_order_release);
    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_default_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TS_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TS_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_default_object_manager& default_object_manager() const noexcept { return F_options::template T_get_manager<T_is_object_thread_safe<F_object>>(); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TS_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TS_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TS_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TS_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TS_oref(const TS_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TS_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
            	x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
					increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                F_options__::T_shared_oref_pre_destruct(object_p_);

                if(decrease_shared_object_counter_unsafe(object_p_) != 1) {

                    reset_no_destroy_internal();

                }
                else {

                    destroy_object_internal();
                    reset_no_destroy_internal();

                }

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = default_object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template T_get_manager<true>().key_pool().push(object_key_);
            else
                F_options::template T_get_manager<false>().key_pool().push(object_key_);
        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TS_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_, ((F_this&)oref).object_key_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TS<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TS<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TS<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TS<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TS_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TS_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TS_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

        }

    public:
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TS_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TS_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TS_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TS_oref(const TS_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TS_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
            	x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                F_options__::T_shared_oref_pre_destruct(object_p_);

                if(decrease_shared_object_counter_unsafe(object_p_) != 1) {

                    reset_no_destroy_internal();

                }
                else {

                    destroy_object_internal();
                    reset_no_destroy_internal();

                }

            }

        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TS_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TS<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TS<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TS<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TS<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

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



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = true, typename F_requirements__ = F_no_requirements>
    class TX_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_no_requirements>
    using TX2_oref = TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_default_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TX_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
    	using TF_bind_passed_object = TX_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;
        b8 is_shared_ = false;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_default_object_manager& default_object_manager() const noexcept { return F_options::template T_get_manager<T_is_object_thread_safe<F_object>>(); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        NCPP_FORCE_INLINE b8 is_shared() const noexcept { return is_shared_; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TX_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TX_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TX_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TX_oref(const TX_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TX_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

			x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

			x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

//			x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

//			x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if(object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            if(is_shared_)
                return (object_p_ != 0);

            if(object_key_.is_thread_safe)
                return F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            if(is_shared_)
                return (object_p_ == 0);

            if(object_key_.is_thread_safe)
                return !F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return !F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            if(is_shared_)
                return (object_p_ != 0);

            if(object_key_.is_thread_safe)
                return F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            if(is_shared_)
                return (object_p_ == 0);

            if(object_key_.is_thread_safe)
                return !F_options::template T_get_manager<true>().key_pool().check(object_key_);
            else
                return !F_options::template T_get_manager<false>().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
            is_shared_ = false;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(is_shared_) {

                    F_options__::T_shared_oref_pre_destruct(object_p_);

                    if (decrease_shared_object_counter_unsafe(object_p_) != 1) {

                        reset_no_destroy_internal();

                    } else {

                        destroy_object_internal();
                        reset_no_destroy_internal();

                    }

                }
                else {

                    reset_no_destroy_internal();

                }

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = default_object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template T_get_manager<true>().key_pool().push(object_key_);
            else
                F_options::template T_get_manager<false>().key_pool().push(object_key_);
        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TX_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_, ((F_this&)oref).object_key_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() const & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() const && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TX<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TX<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TX<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TX<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TX_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;
        template<typename F_passed_object_in__>
        using TF_bind_passed_object = TX_oref<F_passed_object_in__, F_allocator, F_options__, is_has_object_key, F_requirements>;

    private:
    	friend ncpp::internal::F_this_oref_getter;
    	NCPP_FORCE_INLINE const auto& this_oref_internal() const noexcept { return *this; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        b8 is_shared_ = false;

    public:
		NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object() const noexcept {
			NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";
			return *(object_p());
		}
		NCPP_FORCE_INLINE F_passed_object* object_p_unsafe() const noexcept {
			return (F_passed_object*)object_p_;
		}
		NCPP_FORCE_INLINE F_passed_object& object_unsafe() const noexcept {
			return *(object_p());
		}

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        NCPP_FORCE_INLINE b8 is_shared() const noexcept { return is_shared_; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TX_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

        }

    public:
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TX_oref() noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref(F_null) noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TX_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TX_oref(const TX_oref& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TX_oref&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.is_shared_)
        {

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
            	NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if (object_p_)
				increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if (object_p_)
				increase_shared_object_counter_unsafe(object_p_);

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(false)
        {

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.is_shared_)
        {

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

			if(x.is_shared_)
			{
				if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
					x.reset_no_destroy_internal();
				else if (object_p_)
					increase_shared_object_counter_unsafe(object_p_);
			}

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if (object_p_)
				increase_shared_object_counter_unsafe(object_p_);

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				x.reset_no_destroy_internal();
			else if (object_p_)
				increase_shared_object_counter_unsafe(object_p_);

			NCPP_ASSERT_OREF_REQUIREMENTS(this);
			if constexpr (!std::is_same_v<F_requirements, F_valid_requirements>)
				NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(false)
        {

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

//            x.reset_no_destroy_internal();

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
//            NCPP_ASSERT_OREF_REQUIREMENTS(&x);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            NCPP_ASSERT_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 NQ_is_valid() const noexcept {

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 NQ_is_null() const noexcept {

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(is_shared_) {

                    F_options__::T_shared_oref_pre_destruct(object_p_);

                    if (decrease_shared_object_counter_unsafe(object_p_) != 1) {

                        reset_no_destroy_internal();

                    } else {

                        destroy_object_internal();
                        reset_no_destroy_internal();

                    }

                }
                else {

                    reset_no_destroy_internal();

                }

            }

        }



    private:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args);

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE TX_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "object reference is already valid";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE F_this T_make(F_args__&&... args) {

            utilities::TF_mem_wrap<F_this> oref;

            ((F_this&)oref).T_create_object(std::forward<F_args__>(args)...);

            return { ((F_this&)oref).object_p_ };
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() const & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() const && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }



    public:
        NCPP_FORCE_INLINE operator bool() const noexcept {

            return is_valid();
        }
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            NCPP_ASSERT_OREF_REQUIREMENTS(this);
            NCPP_ASSERT(is_valid()) << "can't access invalid object";

            return *((F_passed_object*)object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE auto& no_requirements() & noexcept {

            return (TX<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE const auto& no_requirements() const & noexcept {

            return (const TX<F_passed_object, F_allocator, F_options, is_has_object_key>&)*this;
        }
        NCPP_FORCE_INLINE auto&& no_requirements() && noexcept {

            return (TX<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }
        NCPP_FORCE_INLINE const auto&& no_requirements() const && noexcept {

            return (const TX<F_passed_object, F_allocator, F_options, is_has_object_key>&&)*this;
        }

        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>& T_require() & noexcept {

            return (TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE TF_bind_requirements<F_requirements_in__>&& T_require() && noexcept {

            return (TF_bind_requirements<F_requirements_in__>&&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>& T_require() const& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&)*this;
        }
        template<typename F_requirements_in__ = F_no_requirements>
        NCPP_FORCE_INLINE const TF_bind_requirements<F_requirements_in__>&& T_require() const&& noexcept {

            return (const TF_bind_requirements<F_requirements_in__>&&)*this;
        }

    };



    namespace internal {

        struct F_fake_obj {};

        template<
            typename F_allocator__ = mem::F_object_allocator,
            typename F_passed_object__ = F_fake_obj,
            class F_options__ = F_default_object_options,
            b8 is_has_object_key__ = true,
            typename F_requirements__ = F_no_requirements
        >
        struct TF_lock_shared_helper {

            using S = TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;
            using K = TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>;

            static inline S get(const K& k) {

                if(k.is_valid()) {
                    auto* object_p = k.object_p();
                    increase_shared_object_counter_unsafe(object_p);
                    return S::unsafe(object_p, k.object_key());
                }
                else {
                    return F_null{};
                }
            }

        };
        template<
            typename F_allocator__,
            typename F_passed_object__,
            class F_options__,
            typename F_requirements__
        >
        struct TF_lock_shared_helper<
            F_allocator__,
            F_passed_object__,
            F_options__,
            false,
            F_requirements__
        > {

            using S = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;
            using K = TK_oref<F_passed_object__, F_options__, false, F_requirements__>;

            static inline S get(const K& k) {

                if(k.is_valid()) {
                    auto* object_p = k.object_p();
                    increase_shared_object_counter_unsafe(object_p);
                    return S::unsafe(object_p);
                }
                else {
                    return F_null{};
                }
            }

        };

    };

    template<
        typename F_allocator__ = mem::F_object_allocator,
        typename F_passed_object__ = internal::F_fake_obj,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = true,
        typename F_requirements__ = F_no_requirements
    >
    NCPP_FORCE_INLINE TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__> T_lock_shared(
        ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__> k
    ) {

        return internal::TF_lock_shared_helper<F_allocator__, F_passed_object__, F_options__, is_has_object_key__, F_requirements__>::get(k);
    }

}



NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);

NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);

NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);



#define NCPP_WTHIS() (ncpp::TW_valid<std::remove_pointer_t<decltype(this)>>::unsafe(this))

#define NCPP_KTHIS(...) (ncpp::TK_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS(...) (ncpp::TS_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS(...) (ncpp::TX_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))

#define NCPP_KTHIS2(...) (ncpp::TK2_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS2(...) (ncpp::TS2_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS2(...) (ncpp::TX2_valid<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))



#define NCPP_WTHIS_UNSAFE() (ncpp::TW<std::remove_pointer_t<decltype(this)>>::unsafe(this))

#define NCPP_KTHIS_UNSAFE(...) (ncpp::TK<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS_UNSAFE(...) (ncpp::TS<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS_UNSAFE(...) (ncpp::TX<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))

#define NCPP_KTHIS2_UNSAFE(...) (ncpp::TK2<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS2_UNSAFE(...) (ncpp::TS2<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS2_UNSAFE(...) (ncpp::TX2<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))