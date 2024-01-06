#pragma once

/**
 *  @file ncpp/utilities/template_arg_list.hpp
 *  @brief Implements template_arg_list_t.
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

#include <ncpp/utilities/nth_template_arg.hpp>
#include <ncpp/utilities/first_template_arg.hpp>
#include <ncpp/utilities/last_template_arg.hpp>

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



        template<typename... F_args__>
        struct TF_template_arg_list;



        namespace internal {

            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            concept T_filter_single = requires {

                requires TF_filter_semantics__<F__>::value;

            };

            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            concept T_filter_single_and_has_custom_type = requires {

                requires T_filter_single<F__, TF_filter_semantics__>;
                typename TF_filter_semantics__<F__>::F;

            };

            template<b8 is_valid__, typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper;

            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper<false, F__, TF_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper<true, F__, TF_filter_semantics__> {

                using F = typename TF_filter_semantics__<F__>::F;

            };

            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            using TF_safe_filter_single = typename TF_safe_filter_single_helper<
                T_filter_single_and_has_custom_type<F__, TF_filter_semantics__>,
                F__,
                TF_filter_semantics__
            >::F;



            template<b8 is_valid__, typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper;

            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper<false, F__, TF_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper<true, F__, TF_filter_semantics__> {

                using F = F__;

            };

        }



        namespace internal {

            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            concept T_invert_filter_single = requires {

                requires (!TF_invert_filter_semantics__<F__>::value);

            };

            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            concept T_invert_filter_single_and_has_custom_type = requires {

                requires T_invert_filter_single<F__, TF_invert_filter_semantics__>;
                typename TF_invert_filter_semantics__<F__>::F;

            };

            template<b8 is_valid__, typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper;

            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper<false, F__, TF_invert_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper<true, F__, TF_invert_filter_semantics__> {

                using F = typename TF_invert_filter_semantics__<F__>::F;

            };

            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            using TF_safe_invert_filter_single = typename TF_safe_invert_filter_single_helper<
                T_invert_filter_single_and_has_custom_type<F__, TF_invert_filter_semantics__>,
                F__,
                TF_invert_filter_semantics__
            >::F;



            template<b8 is_valid__, typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper;

            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper<false, F__, TF_invert_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper<true, F__, TF_invert_filter_semantics__> {

                using F = F__;

            };

        }



        template<typename... F_args__>
        struct TF_template_arg_list {

        public:
            using F_this = TF_template_arg_list<F_args__...>;



        public:
            static constexpr u16 count = sizeof...(F_args__);
            static constexpr b8 is_empty = (count == 0);



        private:
            template<class F__>
            struct TF_combine_helper_internal;

            template<typename... F_args2__>
            struct TF_combine_helper_internal<TF_template_arg_list<F_args2__...>>{

                using F = TF_template_arg_list<F_args__..., F_args2__...>;

            };



        private:
            template<sz index__>
            struct TF_at_internal {

                static_assert((index__ < count), "out of bound");

                using F = TF_nth_template_arg<index__, F_args__...>;

            };



        public:
            template<sz index__>
            using TF_at = typename TF_at_internal<index__>::F;

            template<typename F__>
            using TF_combine = typename TF_combine_helper_internal<F__>::F;

            template<typename... F_args2__>
            using TF_extends = TF_combine<TF_template_arg_list<F_args2__...>>;



        public:
            template<sz count__>
            using TF_remove_heads = TF_remove_head_template_args<count__, F_args__...>;

            template<sz count__>
            using TF_remove_tails = TF_remove_tail_template_args<count__, F_args__...>;



        private:
            template<sz index__, sz count__>
            struct TF_slice_internal {

                static_assert((index__ < count) && ((index__ + count__) <= count), "out of bound");

                using F = TF_remove_heads<index__>::template TF_remove_tails<count - (index__ + count__)>;

            };



        public:
            template<sz index__, sz count__>
            using TF_slice = typename TF_slice_internal<index__, count__>::F;



        private:
            template<i32 index__, template<typename F_in__> class TF_filter_semantics__>
            struct TF_filter_helper_internal {

                using F_current_arg = TF_at<index__>;
                using F_prev_list = typename TF_filter_helper_internal<index__ - 1, TF_filter_semantics__>::F;

                using F = F_prev_list::template TF_combine<
                    TF_nth_template_arg<
                        internal::T_filter_single<F_current_arg, TF_filter_semantics__>,
                        TF_template_arg_list<>,
                        TF_template_arg_list<internal::TF_safe_filter_single<F_current_arg, TF_filter_semantics__>>
                    >
                >;

            };

            template<template<typename F_in__> class TF_filter_semantics__>
            struct TF_filter_helper_internal<-1, TF_filter_semantics__> {

                using F = TF_template_arg_list<>;

            };

            template<template<typename F_in__> class TF_filter_semantics__>
            using TF_filter_single_internal = typename TF_filter_helper_internal<count - 1, TF_filter_semantics__>::F;

            template<typename F_list__, template<typename F_in__> class... TF_multiple_filter_semantics__>
            struct TF_filter_multiple_semantics_helper_internal;
            template<typename F_list__>
            struct TF_filter_multiple_semantics_helper_internal<F_list__> {

                using F = F_list__;

            };
            template<
                typename F_list__,
                template<typename F_in__> class TF_first_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_filter_semantics__
            >
            struct TF_filter_multiple_semantics_helper_internal<
                F_list__,
                TF_first_filter_semantics__,
                TF_rest_multiple_filter_semantics__...
            >
            {

                using F_filted_list = F_list__::template TF_filter_single_internal<TF_first_filter_semantics__>;
                using F = typename TF_filter_multiple_semantics_helper_internal<
                    F_filted_list,
                    TF_rest_multiple_filter_semantics__...
                >::F;

            };

        public:
            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter = typename TF_filter_multiple_semantics_helper_internal<
                F_this,
                TF_multiple_filter_semantics__...
            >::F;



        private:
            template<i32 index__, template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_invert_filter_helper_internal {

                using F_current_arg = TF_at<index__>;
                using F_prev_list = typename TF_invert_filter_helper_internal<index__ - 1, TF_invert_filter_semantics__>::F;

                using F = F_prev_list::template TF_combine<
                    TF_nth_template_arg<
                        internal::T_invert_filter_single<F_current_arg, TF_invert_filter_semantics__>,
                        TF_template_arg_list<>,
                        TF_template_arg_list<internal::TF_safe_invert_filter_single<F_current_arg, TF_invert_filter_semantics__>>
                    >
                >;

            };

            template<template<typename F_in__> class TF_invert_filter_semantics__>
            struct TF_invert_filter_helper_internal<-1, TF_invert_filter_semantics__> {

                using F = TF_template_arg_list<>;

            };

            template<template<typename F_in__> class TF_invert_filter_semantics__>
            using TF_invert_filter_single_internal = typename TF_invert_filter_helper_internal<count - 1, TF_invert_filter_semantics__>::F;

            template<typename F_list__, template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            struct TF_invert_filter_multiple_semantics_helper_internal;
            template<typename F_list__>
            struct TF_invert_filter_multiple_semantics_helper_internal<F_list__> {

                using F = F_list__;

            };
            template<
                typename F_list__,
                template<typename F_in__> class TF_first_invert_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_invert_filter_semantics__
            >
            struct TF_invert_filter_multiple_semantics_helper_internal<
                F_list__,
                TF_first_invert_filter_semantics__,
                TF_rest_multiple_invert_filter_semantics__...
            >
            {

                using F_filted_list = F_list__::template TF_invert_filter_single_internal<TF_first_invert_filter_semantics__>;
                using F = typename TF_invert_filter_multiple_semantics_helper_internal<
                    F_filted_list,
                    TF_rest_multiple_invert_filter_semantics__...
                >::F;

            };

        public:
            template<template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            using TF_invert_filter = typename TF_invert_filter_multiple_semantics_helper_internal<
                F_this,
                TF_multiple_invert_filter_semantics__...
            >::F;



        public:
            template<template<typename F_in__> class TF_update_semantics__>
            using TF_update = TF_template_arg_list<typename TF_update_semantics__<F_args__>::F...>;

        };



        template<typename F__>
        struct TF_to_template_arg_list {

            using F = TF_template_arg_list<F__>;

        };

    }

}