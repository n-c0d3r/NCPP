#pragma once

/**
 *  @file ncpp/utilities/pack.hpp
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

    namespace utilities {



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

            template<sz count__, typename... F__>
            struct TF_large_pack_implement;

            template<typename... F__>
            struct TF_large_pack_implement<1, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    TF_nth_template_arg<0, F__...> first;

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<2, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<3, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<4, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;
                        TF_nth_template_arg<3, F__...> fourth;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<5, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;
                        TF_nth_template_arg<3, F__...> fourth;
                        TF_nth_template_arg<4, F__...> fifth;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<6, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;
                        TF_nth_template_arg<3, F__...> fourth;
                        TF_nth_template_arg<4, F__...> fifth;
                        TF_nth_template_arg<5, F__...> sixth;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<7, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;
                        TF_nth_template_arg<3, F__...> fourth;
                        TF_nth_template_arg<4, F__...> fifth;
                        TF_nth_template_arg<5, F__...> sixth;
                        TF_nth_template_arg<6, F__...> seventh;

                    };

                };

            };

            template<typename... F__>
            struct TF_large_pack_implement<8, F__...> {

                union {

                    eastl::tuple<F__...> tuple = {};

                    struct {

                        TF_nth_template_arg<0, F__...> first;
                        TF_nth_template_arg<1, F__...> second;
                        TF_nth_template_arg<2, F__...> third;
                        TF_nth_template_arg<3, F__...> fourth;
                        TF_nth_template_arg<4, F__...> fifth;
                        TF_nth_template_arg<5, F__...> sixth;
                        TF_nth_template_arg<6, F__...> seventh;
                        TF_nth_template_arg<7, F__...> eighth;

                    };

                };

            };

        }



        template<typename... F__>
        using TF_large_pack = internal::TF_large_pack_implement<sizeof...(F__), F__...>;



        template<typename... F__>
        using TF_pack = TF_nth_template_arg<
            (sizeof...(F__) > 1),
            TF_first_template_arg<F__...>,
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

                    return eastl::get<index__>(std::forward<F_pack&>(pack.tuple));
                }
                static NCPP_FORCE_INLINE F&& get(F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<F_pack>(pack.tuple));
                }
                static NCPP_FORCE_INLINE const F& get(const F_pack& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack&>(pack.tuple));
                }
                static NCPP_FORCE_INLINE const F&& get(const F_pack&& pack) noexcept {

                    return eastl::get<index__>(std::forward<const F_pack>(pack.tuple));
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

    }

}