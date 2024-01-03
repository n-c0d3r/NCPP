#pragma once

/**
 *  @file ncpp/containers/pack.hpp
 *  @brief Implements pack.
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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/first_template_arg.hpp>
#include <ncpp/utilities/nth_template_arg.hpp>
#include <ncpp/utilities/sizeof.hpp>
#include <ncpp/utilities/pass.hpp>

#include <ncpp/containers/binding_helper.hpp>
#include <ncpp/containers/view.hpp>

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

    namespace containers {



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

            template<class F_tuple__, typename... F_arguments__>
            concept T_is_tuple_convertible = requires(F_arguments__&&... args) {

                F_tuple__(std::forward<F_arguments__>(args)...);

            };

#define NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL() \
            using F_tuple = eastl::tuple<F__...>;         \
            F_tuple tuple;                                 \
                                                                \
                                                                \
                                                                \
            NCPP_FORCE_INLINE TF_large_pack_implement() : tuple() { } \
                                                                \
            NCPP_FORCE_INLINE TF_large_pack_implement(const TF_large_pack_implement& x) : tuple(x.tuple) { }\
            NCPP_FORCE_INLINE TF_large_pack_implement(TF_large_pack_implement&& x) : tuple(std::forward<F_tuple>(x.tuple)) { }\
                                                                \
            NCPP_FORCE_INLINE TF_large_pack_implement(const F_tuple& x) : tuple(x) { }\
            NCPP_FORCE_INLINE TF_large_pack_implement(F_tuple&& x) : tuple(std::forward<F_tuple>(x)) { }\
                                                                \
            template<typename... F_arguments__>                 \
            requires T_is_tuple_convertible<F_tuple, F_arguments__...>            \
            NCPP_FORCE_INLINE TF_large_pack_implement(F_arguments__&&... args) : tuple(std::forward<F_arguments__>(args)...) { }\
                                                                \
                                                                \
                                                                \
            NCPP_FORCE_INLINE TF_large_pack_implement& operator = (const TF_large_pack_implement& x) { \
                tuple = x.tuple; \
                return *this;\
            }\
            NCPP_FORCE_INLINE TF_large_pack_implement& operator = (TF_large_pack_implement&& x) { \
                tuple = std::forward<F_tuple>(x.tuple); \
                return *this;\
            }\
                                                                \
                                                                \
                                                                \
            NCPP_FORCE_INLINE operator F_tuple () { return tuple; }\
            NCPP_FORCE_INLINE operator utilities::TF_pass<F_tuple> () const { return tuple; }



            template<sz element_count__, typename... F__>
            struct TF_large_pack_implement {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
            };



#define NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(Index, Name) \
            NCPP_FORCE_INLINE utilities::TF_nth_template_arg<Index, F__...>& Name() {\
                \
                return eastl::get<Index>((eastl::tuple<F__...>&)*this);\
            }\
            NCPP_FORCE_INLINE utilities::TF_pass<utilities::TF_nth_template_arg<Index, F__...>> Name() const {\
                \
                return eastl::get<Index>((const eastl::tuple<F__...>&)*this);\
            }

            template<typename... F__>
            struct TF_large_pack_implement<1, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
            };

            template<typename... F__>
            struct TF_large_pack_implement<2, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
            };

            template<typename... F__>
            struct TF_large_pack_implement<3, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
            };

            template<typename... F__>
            struct TF_large_pack_implement<4, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(3, fourth);
            };

            template<typename... F__>
            struct TF_large_pack_implement<5, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(3, fourth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(4, fifth);
            };

            template<typename... F__>
            struct TF_large_pack_implement<6, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(3, fourth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(4, fifth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(5, sixth);
            };

            template<typename... F__>
            struct TF_large_pack_implement<7, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(3, fourth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(4, fifth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(5, sixth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(6, seventh);
            };

            template<typename... F__>
            struct TF_large_pack_implement<8, F__...> {
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_TUPLE_INTERNAL();
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(0, first);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(1, second);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(2, third);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(3, fourth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(4, fifth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(5, sixth);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(6, seventh);
                NCPP_CONTAINERS_PACK_DEFINE_LARGE_PACK_ELEMENT_GETTER_INTERNAL(7, eighth);
            };

        }



        template<typename... F__>
        using TF_large_pack = internal::TF_large_pack_implement<sizeof...(F__), F__...>;



        namespace internal {

            template<typename F_new_allocator__, typename... F__>
            struct TF_bind_pack_allocator_helper {

                using F = TF_large_pack<TF_bind_container_allocator<F__, F_new_allocator__>...>;

            };

        }



        template<typename... F__>
        using TF_pack = utilities::TF_nth_template_arg<
            (sizeof...(F__) > 1),
            utilities::TF_first_template_arg<F__...>,
            TF_large_pack<F__...>
        >;



        namespace internal {

            template<sz index__, typename F_pack__>
            struct TF_unpack_helper {

                using F_pack = F_pack__;
                using F = F_pack;

                static NCPP_FORCE_INLINE F& get(F_pack& pack) noexcept {

                    return std::forward<F_pack&>(pack);
                }
                static NCPP_FORCE_INLINE F&& get(F_pack&& pack) noexcept {

                    return std::forward<F_pack>(pack);
                }
                static NCPP_FORCE_INLINE const F& get(const F_pack& pack) noexcept {

                    return std::forward<const F_pack&>(pack);
                }
                static NCPP_FORCE_INLINE const F&& get(const F_pack&& pack) noexcept {

                    return std::forward<const F_pack>(pack);
                }

            };

            template<sz index__, typename... F__>
            struct TF_unpack_helper<index__, eastl::tuple<F__...>> {

                using F_pack = eastl::tuple<F__...>;
                using F = eastl::tuple_element_t<index__, F_pack>;

                static NCPP_FORCE_INLINE F& get(F_pack& pack) noexcept {

                    return eastl::get<index__>(std::forward<F_pack&>(pack));
                }
                static NCPP_FORCE_INLINE F&& get(F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<F_pack>(pack));
                }
                static NCPP_FORCE_INLINE const F& get(const F_pack& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack&>(pack));
                }
                static NCPP_FORCE_INLINE const F&& get(const F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack>(pack));
                }

            };

            template<sz index__, typename... F__>
            struct TF_unpack_helper<index__, TF_large_pack<F__...>> {

                using F_pack = TF_large_pack<F__...>;
                using F = eastl::tuple_element_t<index__, F_pack>;

                static NCPP_FORCE_INLINE F& get(F_pack& pack) noexcept {

                    return eastl::get<index__>(std::forward<F_pack&>(pack));
                }
                static NCPP_FORCE_INLINE F&& get(F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<F_pack>(pack));
                }
                static NCPP_FORCE_INLINE const F& get(const F_pack& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack&>(pack));
                }
                static NCPP_FORCE_INLINE const F&& get(const F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack>(pack));
                }

            };

            template<sz index__, typename F_pack__>
            struct TF_pack_size_helper {

                static constexpr sz size = 1;

            };

            template<sz index__, typename... F__>
            struct TF_pack_size_helper<index__, eastl::tuple<F__...>> {

                static constexpr sz size = sizeof...(F__);

            };

            template<sz index__, typename... F__>
            struct TF_pack_size_helper<index__, TF_large_pack<F__...>> {

                static constexpr sz size = sizeof...(F__);

            };

        }

        template<sz index__, typename F_passed_pack__>
        using TF_unpack = typename internal::TF_unpack_helper<index__, std::remove_const_t<std::remove_reference_t<F_passed_pack__>>>::F;

        template<sz index__, typename F_passed_pack__>
        using TF_unpack_return = decltype(
            internal::TF_unpack_helper<
                index__,
                std::remove_const_t<std::remove_reference_t<F_passed_pack__>>
            >::get(
                std::declval<F_passed_pack__&&>()
            )
        );

        template<sz index__, typename F_passed_pack__>
        static constexpr sz T_pack_size = internal::TF_pack_size_helper<index__, std::remove_const_t<std::remove_reference_t<F_passed_pack__>>>::size;

        template<sz index__ = 0, typename F_passed_pack__ = int>
        NCPP_CONSTEXPR TF_unpack_return<index__, F_passed_pack__> T_unpack(F_passed_pack__&& pack)
        {

            return internal::TF_unpack_helper<index__, std::remove_const_t<std::remove_reference_t<F_passed_pack__>>>::get(std::forward<F_passed_pack__>(pack));
        }



        template<typename... F__>
        using TG_pack = TF_pack<F__...>;
        template<typename... F__>
        using TEP_pack = TF_pack<F__...>;

        template<typename... F__>
        using TV_pack = TF_view<TG_pack<F__...>>;

    }

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_large_pack<F__...>),
    NCPP_MA(void),
    NCPP_MA(typename ncpp::containers::internal::TF_bind_pack_allocator_helper<F_new_allocator__, F__...>::F),
    typename... F__
);