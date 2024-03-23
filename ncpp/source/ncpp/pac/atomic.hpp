#pragma once

/** @file ncpp/pac/atomic.hpp
*	@brief Implement atomic
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

#include <ncpp/utilities/.hpp>

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

    namespace pac {

        namespace internal {

            template<typename F__, b8 is_thread_safe__>
            struct TF_fldata_helper;
            template<typename F__>
            struct TF_fldata_helper<F__, false> {

                using F = F__;

            };
            template<typename F__>
            struct TF_fldata_helper<F__, true> {

                using F = eastl::atomic<F__>;

            };

            template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
            struct TF_fladd_helper;
            template<typename F__, typename... F_additional_args__>
            struct TF_fladd_helper<false, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    F__ result = variable;
                    variable += x;
                    return result;
                }

            };
            template<typename F__, typename... F_additional_args__>
            struct TF_fladd_helper<true, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    return variable.fetch_add(x, additional_args...);
                }

            };

            template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
            struct TF_flsub_helper;
            template<typename F__, typename... F_additional_args__>
            struct TF_flsub_helper<false, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    F__ result = variable;
                    variable -= x;
                    return result;
                }

            };
            template<typename F__, typename... F_additional_args__>
            struct TF_flsub_helper<true, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    return variable.fetch_sub(x, additional_args...);
                }

            };

            template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
            struct TF_fland_helper;
            template<typename F__, typename... F_additional_args__>
            struct TF_fland_helper<false, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    F__ result = variable;
                    variable &= x;
                    return result;
                }

            };
            template<typename F__, typename... F_additional_args__>
            struct TF_fland_helper<true, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    return variable.fetch_and(x, additional_args...);
                }

            };

            template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
            struct TF_flor_helper;
            template<typename F__, typename... F_additional_args__>
            struct TF_flor_helper<false, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    F__ result = variable;
                    variable |= x;
                    return result;
                }

            };
            template<typename F__, typename... F_additional_args__>
            struct TF_flor_helper<true, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    return variable.fetch_or(x, additional_args...);
                }

            };

            template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
            struct TF_flxor_helper;
            template<typename F__, typename... F_additional_args__>
            struct TF_flxor_helper<false, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    F__ result = variable;
                    variable ^= x;
                    return result;
                }

            };
            template<typename F__, typename... F_additional_args__>
            struct TF_flxor_helper<true, F__, F_additional_args__...> {

                static NCPP_FORCE_INLINE auto invoke(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

                    return variable.fetch_xor(x, additional_args...);
                }

            };

        }



        template<typename F__, b8 is_thread_safe__>
        using TF_fldata = typename internal::TF_fldata_helper<F__, is_thread_safe__>::F;

        template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
        NCPP_FORCE_INLINE auto T_fladd(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

            return internal::TF_fladd_helper<
                is_thread_safe__,
                F__,
                F_additional_args__...
            >::invoke(
                variable,
                x,
                additional_args...
            );
        }

        template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
        NCPP_FORCE_INLINE auto T_flsub(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

            return internal::TF_flsub_helper<
                is_thread_safe__,
                F__,
                F_additional_args__...
            >::invoke(
                variable,
                x,
                additional_args...
            );
        }

        template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
        NCPP_FORCE_INLINE auto T_fland(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

            return internal::TF_fland_helper<
                is_thread_safe__,
                F__,
                F_additional_args__...
            >::invoke(
                variable,
                x,
                additional_args...
            );
        }

        template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
        NCPP_FORCE_INLINE auto T_flor(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

            return internal::TF_flor_helper<
                is_thread_safe__,
                F__,
                F_additional_args__...
            >::invoke(
                variable,
                x,
                additional_args...
            );
        }

        template<b8 is_thread_safe__, typename F__, typename... F_additional_args__>
        NCPP_FORCE_INLINE auto T_flxor(F__& variable, F__ x, F_additional_args__... additional_args) noexcept -> std::remove_reference_t<decltype(variable)> {

            return internal::TF_flxor_helper<
                is_thread_safe__,
                F__,
                F_additional_args__...
            >::invoke(
                variable,
                x,
                additional_args...
            );
        }

    }

}

