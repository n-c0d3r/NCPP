#pragma once

/**
 *  @file ncpp/utilities/template_targ_list.hpp
 *  @brief Implements template_targ_list.
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

#include <ncpp/utilities/nth_template_targ.hpp>
#include <ncpp/utilities/first_template_targ.hpp>
#include <ncpp/utilities/last_template_targ.hpp>
#include <ncpp/utilities/template_varg_list.hpp>

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
        struct TF_template_targ_list;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        namespace internal_targ {

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            concept T_filter_single = requires {

                requires TF_filter_semantics__<F__, index__>::is_valid;

            };

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            concept T_filter_single_and_has_custom_type = requires {

                requires T_filter_single<F__, index__, TF_filter_semantics__>;
                typename TF_filter_semantics__<F__, index__>::F;

            };

            template<b8 is_valid__, typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper;

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper<false, F__, index__, TF_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, sz index__,template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_safe_filter_single_helper<true, F__, index__, TF_filter_semantics__> {

                using F = typename TF_filter_semantics__<F__, index__>::F;

            };

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            using TF_safe_filter_single = typename TF_safe_filter_single_helper<
                T_filter_single_and_has_custom_type<F__, index__, TF_filter_semantics__>,
                F__,
                index__,
                TF_filter_semantics__
            >::F;



            template<b8 is_valid__, typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper;

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper<false, F__, index__, TF_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_invert_filter_helper<true, F__, index__, TF_filter_semantics__> {

                using F = F__;

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



        namespace internal_targ {

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            concept T_invert_filter_single = requires {

                requires (!TF_invert_filter_semantics__<F__, index__>::is_valid);

            };

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            concept T_invert_filter_single_and_has_custom_type = requires {

                requires T_invert_filter_single<F__, index__, TF_invert_filter_semantics__>;
                typename TF_invert_filter_semantics__<F__, index__>::F;

            };

            template<b8 is_valid__, typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper;

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper<false, F__, index__, TF_invert_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_safe_invert_filter_single_helper<true, F__, index__, TF_invert_filter_semantics__> {

                using F = typename TF_invert_filter_semantics__<F__, index__>::F;

            };

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            using TF_safe_invert_filter_single = typename TF_safe_invert_filter_single_helper<
                T_invert_filter_single_and_has_custom_type<F__, index__, TF_invert_filter_semantics__>,
                F__,
                index__,
                TF_invert_filter_semantics__
            >::F;



            template<b8 is_valid__, typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper;

            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper<false, F__, index__, TF_invert_filter_semantics__> {

                using F = F__;

            };
            template<typename F__, sz index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_invert_invert_filter_helper<true, F__, index__, TF_invert_filter_semantics__> {

                using F = F__;

            };



            template<typename... F__>
            struct TF_template_targ_list_first {

                using F_first = TF_nth_template_targ<0, F__...>;

            };
            template<>
            struct TF_template_targ_list_first<> {

            };

            template<typename... F__>
            struct TF_template_targ_list_last {

                using F_last = TF_nth_template_targ<(sizeof...(F__) - 1), F__...>;

            };
            template<>
            struct TF_template_targ_list_last<> {

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



        namespace internal {

            template<typename F__>
            struct TF_is_template_targ_list_helper {

                static constexpr b8 value = false;

            };

            template<typename... Fs__>
            struct TF_is_template_targ_list_helper<TF_template_targ_list<Fs__...>> {

                static constexpr b8 value = true;

            };

        }

        template<typename F__>
        concept T_is_template_targ_list = internal::TF_is_template_targ_list_helper<F__>::value;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<typename F__, sz index__ = 0>
        struct TL_template_targ_list {

            static constexpr b8 is_valid = T_is_template_targ_list<F__>;

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



        template<typename... F_args__>
        struct TF_template_targ_list :
            public internal_targ::TF_template_targ_list_first<F_args__...>,
            public internal_targ::TF_template_targ_list_last<F_args__...>
        {

        public:
            using F_this = TF_template_targ_list<F_args__...>;

            constexpr TF_template_targ_list() noexcept {}

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            static constexpr u16 count = sizeof...(F_args__);
            static constexpr b8 is_empty = (count == 0);

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<class F__>
            struct TF_combine_helper_internal_targ;

            template<typename... F_args2__>
            struct TF_combine_helper_internal_targ<TF_template_targ_list<F_args2__...>>{

                using F = TF_template_targ_list<F_args__..., F_args2__...>;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<sz index__>
            struct TF_at_internal_targ {

                NCPP_STATIC_ASSERT((index__ < count), "out of bound");

                using F = TF_nth_template_targ<index__, F_args__...>;

            };
            template<sz index__, typename F_if_fail__, b8 is_valid__>
            struct TF_try_at_internal_targ {

                using F = TF_nth_template_targ<
                    is_valid__,
                    F_if_fail__,
                    TF_nth_template_targ<is_valid__ ? index__ : 0, F_args__..., void>
                >;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<sz index__>
            using TF_at = typename TF_at_internal_targ<index__>::F;
            template<sz index__, typename F_if_fail__ = void>
            using TF_try_at = typename TF_try_at_internal_targ<index__, F_if_fail__, (index__ < count)>::F;

            using F_try_first = TF_try_at<0>;
            using F_try_last = TF_try_at<(count != 0) ? (count - 1) : 0>;

            template<T_is_template_targ_list F__>
            using TF_combine = typename TF_combine_helper_internal_targ<F__>::F;

            template<typename... F_args2__>
            using TF_extends = TF_combine<TF_template_targ_list<F_args2__...>>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<sz count__>
            using TF_remove_heads = TF_remove_head_template_targs<count__, F_args__...>;

            template<sz count__>
            using TF_remove_tails = TF_remove_tail_template_targs<count__, F_args__...>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<i32 begin__, i32 end__>
            struct TF_slice_internal_targ {

                NCPP_STATIC_ASSERT(
                    (
                        (begin__ <= count)
                        && (begin__ >= 0)
                        && (end__ <= count)
                        && (end__ >= 0)
                        && (begin__ <= end__)
                    ),
                    "out of bound"
                );

                using F = TF_remove_heads<begin__>::template TF_remove_tails<count - end__>;

            };
            template<i32 begin__, i32 end__>
            struct TF_try_slice_internal_targ {

                static constexpr i32 clamped_begin = (begin__ <= count) ? begin__ : (count - 1);
                static constexpr i32 clamped_begin2 = (clamped_begin >= 0) ? clamped_begin : 0;
                static constexpr i32 clamped_end = (end__ <= count) ? end__ : (count - 1);
                static constexpr i32 clamped_end2 = (clamped_end >= clamped_begin2) ? clamped_end : clamped_begin2;

                using F = TF_remove_heads<clamped_begin2>::template TF_remove_tails<count - clamped_end2>;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<i32 begin__, i32 end__>
            using TF_slice = typename TF_slice_internal_targ<begin__, end__>::F;
            template<i32 begin__, i32 end__>
            using TF_try_slice = typename TF_try_slice_internal_targ<begin__, end__>::F;

            template<i32 begin__, i32 end__>
            using TF_invert_slice = typename TF_slice_internal_targ<count - end__ - 1, count - begin__ - 1>::F;
            template<i32 begin__, i32 end__>
            using TF_try_invert_slice = typename TF_try_slice_internal_targ<count - end__ - 1, count - begin__ - 1>::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<T_is_template_targ_list F_list__, T_is_template_targ_list... F_others__>
            struct TF_join_helper_internal_targ;
            template<T_is_template_targ_list F_list__>
            struct TF_join_helper_internal_targ<F_list__> {

                using F = F_list__;

            };
            template<
                T_is_template_targ_list F_list__,
                T_is_template_targ_list F_first_other__,
                T_is_template_targ_list... F_rest_others__
            >
            struct TF_join_helper_internal_targ<
                F_list__,
                F_first_other__,
                F_rest_others__...
            >
            {

                using F_next_list = typename TF_join_helper_internal_targ<
                    F_first_other__,
                    F_rest_others__...
                >::F;

                using F = F_list__::template TF_combine<F_next_list>;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<T_is_template_targ_list... F_others__>
            using TF_join = typename TF_join_helper_internal_targ<

                F_this,
                F_others__...
            >::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<i32 index__, template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_filter_helper_internal_targ {

                using F_current_arg = TF_at<index__>;
                using F_prev_list = typename TF_filter_helper_internal_targ<index__ - 1, TF_filter_semantics__>::F;

                using F = F_prev_list::template TF_combine<
                    TF_nth_template_targ<
                        internal_targ::T_filter_single<F_current_arg, index__, TF_filter_semantics__>,
                        TF_template_targ_list<>,
                        TF_template_targ_list<internal_targ::TF_safe_filter_single<F_current_arg, index__, TF_filter_semantics__>>
                    >
                >;

            };

            template<template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            struct TF_filter_helper_internal_targ<-1, TF_filter_semantics__> {

                using F = TF_template_targ_list<>;

            };

            template<template<typename F_in__, sz index_in__> class TF_filter_semantics__>
            using TF_filter_single_internal_targ = typename TF_filter_helper_internal_targ<count - 1, TF_filter_semantics__>::F;

            template<typename F_list__, template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            struct TF_filter_multiple_semantics_helper_internal_targ;
            template<typename F_list__>
            struct TF_filter_multiple_semantics_helper_internal_targ<F_list__> {

                using F = F_list__;

            };
            template<
                typename F_list__,
                template<typename F_in__, sz index_in__> class TF_first_filter_semantics__,
                template<typename F_in__, sz index_in__> class... TF_rest_multiple_filter_semantics__
            >
            struct TF_filter_multiple_semantics_helper_internal_targ<
                F_list__,
                TF_first_filter_semantics__,
                TF_rest_multiple_filter_semantics__...
            >
            {

                using F_filtered_list = F_list__::template TF_filter_single_internal_targ<TF_first_filter_semantics__>;
                using F = typename TF_filter_multiple_semantics_helper_internal_targ<
                    F_filtered_list,
                    TF_rest_multiple_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            using TF_filter = typename TF_filter_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_filter_semantics__...
            >::F;

            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            using TF_find = TF_filter<TF_multiple_filter_semantics__...>::template TF_try_slice<0, 1>;

            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            using TF_find_last = TF_filter<TF_multiple_filter_semantics__...>::template TF_try_invert_slice<0, 1>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<i32 index__, template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_invert_filter_helper_internal_targ {

                using F_current_arg = TF_at<index__>;
                using F_prev_list = typename TF_invert_filter_helper_internal_targ<index__ - 1, TF_invert_filter_semantics__>::F;

                using F = F_prev_list::template TF_combine<
                    TF_nth_template_targ<
                        internal_targ::T_invert_filter_single<F_current_arg, index__, TF_invert_filter_semantics__>,
                        TF_template_targ_list<>,
                        TF_template_targ_list<internal_targ::TF_safe_invert_filter_single<F_current_arg, index__, TF_invert_filter_semantics__>>
                    >
                >;

            };

            template<template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            struct TF_invert_filter_helper_internal_targ<-1, TF_invert_filter_semantics__> {

                using F = TF_template_targ_list<>;

            };

            template<template<typename F_in__, sz index_in__> class TF_invert_filter_semantics__>
            using TF_invert_filter_single_internal_targ = typename TF_invert_filter_helper_internal_targ<count - 1, TF_invert_filter_semantics__>::F;

            template<typename F_list__, template<typename F_in__, sz index_in__> class... TF_multiple_invert_filter_semantics__>
            struct TF_invert_filter_multiple_semantics_helper_internal_targ;
            template<typename F_list__>
            struct TF_invert_filter_multiple_semantics_helper_internal_targ<F_list__> {

                using F = F_list__;

            };
            template<
                typename F_list__,
                template<typename F_in__, sz index_in__> class TF_first_invert_filter_semantics__,
                template<typename F_in__, sz index_in__> class... TF_rest_multiple_invert_filter_semantics__
            >
            struct TF_invert_filter_multiple_semantics_helper_internal_targ<
                F_list__,
                TF_first_invert_filter_semantics__,
                TF_rest_multiple_invert_filter_semantics__...
            >
            {

                using F_filtered_list = F_list__::template TF_invert_filter_single_internal_targ<TF_first_invert_filter_semantics__>;
                using F = typename TF_invert_filter_multiple_semantics_helper_internal_targ<
                    F_filtered_list,
                    TF_rest_multiple_invert_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__, sz index_in__> class... TF_multiple_invert_filter_semantics__>
            using TF_invert_filter = typename TF_invert_filter_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_invert_filter_semantics__...
            >::F;

            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            using TF_invert_find = TF_invert_filter<TF_multiple_filter_semantics__...>::template TF_try_slice<0, 1>;

            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
            using TF_invert_find_last = TF_invert_filter<TF_multiple_filter_semantics__...>::template TF_try_invert_slice<0, 1>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<template<typename F_in__, sz index_in__> class TF_update_semantics__>
            struct TF_make_update_filter {

                template<typename F_in__, sz index_in__>
                struct TL : public TF_update_semantics__<F_in__, index_in__> {

                    static constexpr b8 is_valid = true;

                };

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__, sz index_in__> class TF_update_semantics__>
            using TF_update = TF_filter<TF_make_update_filter<TF_update_semantics__>::template TL>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename...> class TF__>
            using TF_apply = TF__<F_args__...>;

//            ////////////////////////////////////////////////////////////////////////////////////
//            ////////////////////////////////////////////////////////////////////////////////////
//            ////////////////////////////////////////////////////////////////////////////////////
//
//        private:
//            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
//            struct TF_find_index_helper_internal {
//
//                template<template<typename F_in__, sz index_in__> class TF_filter_semantics__>
//                struct TF_make_filter_helper {
//
//                    template<typename F__, sz index__>
//                    struct TL : public TF_filter_semantics__<typename F__::F_element, index__> {
//
//                        using F = F__;
//
//                    };
//
//                };
//
//                template<typename F__, sz index__>
//                struct TL_indexed {
//
//                    static constexpr b8 is_valid = true;
//
//                    struct F {
//
//                        using F_element = F__;
//                        static constexpr sz index = index__;
//
//                    };
//
//                };
//                using F_indexed_list = TF_update<TL_indexed>;
//
//
//
//                using F_indexed = F_indexed_list::template TF_find<TF_make_filter_helper<TF_multiple_filter_semantics__>::template TL...>;
//
////                static constexpr sz index = F_indexed::index;
//
//            };
//
//            ////////////////////////////////////////////////////////////////////////////////////
//            ////////////////////////////////////////////////////////////////////////////////////
//            ////////////////////////////////////////////////////////////////////////////////////
//
//        public:
//            template<template<typename F_in__, sz index_in__> class... TF_multiple_filter_semantics__>
//            using TF_find_index = typename TF_find_index_helper_internal<TF_multiple_filter_semantics__...>::F_indexed;

        };



        template<typename F__>
        struct TF_to_template_targ_list {

            using F = TF_template_targ_list<F__>;

        };

    }

}