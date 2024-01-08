#pragma once

/**
 *  @file ncpp/utilities/template_targ_tree.hpp
 *  @brief Implements template_targ_tree.
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

#include <ncpp/utilities/template_targ_list.hpp>

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

        template<typename... Fs__>
        struct TF_template_targ_tree;



        namespace internal {

            template<typename F__>
            struct TF_is_template_targ_tree_helper {

                static constexpr b8 value = false;

            };

            template<typename... Fs__>
            struct TF_is_template_targ_tree_helper<TF_template_targ_tree<Fs__...>> {

                static constexpr b8 value = true;

            };

        }

        template<typename F__>
        concept T_is_template_targ_tree = internal::TF_is_template_targ_tree_helper<F__>::value;

        template<typename F__>
        concept T_not_template_targ_tree = !internal::TF_is_template_targ_tree_helper<F__>::value;



        template<typename F__>
        struct TL_template_targ_tree {

            static constexpr b8 is_valid = T_is_template_targ_tree<F__>;

        };



        template<>
        struct TF_template_targ_tree<> {

        public:
            using F_this = TF_template_targ_tree<>;
            using F_list = TF_template_targ_list<>;

            using F_arg = void;
            using F_childs = TF_template_targ_list<>;

            static constexpr b8 is_null = true;
            static constexpr b8 is_valid = false;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using F_normalized = F_this;
            using F_flatten = TF_template_targ_list<>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter = F_this;

            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter_childs = F_this;

            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_invert_filter = F_this;

            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_invert_filter_childs = F_this;

        };



        template<typename F_arg__, typename F_first_child__, typename... F_rest_childs__>
        requires(TF_template_targ_list<F_first_child__, F_rest_childs__...>::template TF_invert_filter<TL_template_targ_tree>::count != 0)
        struct TF_template_targ_tree<F_arg__, F_first_child__, F_rest_childs__...> {

            static_assert(
                TF_template_targ_list<F_first_child__, F_rest_childs__...>::template TF_invert_filter<TL_template_targ_tree>::count == 0,
                "invalid template targ childs"
            );

        };



        template<typename F_arg__, T_is_template_targ_tree... F_childs__>
        struct TF_template_targ_tree<F_arg__, F_childs__...>
        {

        public:
            using F_this = TF_template_targ_tree<F_arg__, F_childs__...>;
            using F_list = TF_template_targ_list<F_arg__, F_childs__...>;

            using F_arg = F_arg__;
            using F_childs = TF_template_targ_list<F_childs__...>;

            static constexpr b8 is_null = false;
            static constexpr b8 is_valid = true;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            struct F_normalized_helper_internal_targ
            {

                template<typename F_child__>
                struct TL_valid_child {

                    static constexpr b8 is_valid = F_child__::is_valid;

                };

                using F_filtered_arg_list = TF_template_targ_list<F_arg>;
                using F_filtered_child_list = F_childs::template TF_filter<TL_valid_child>;

                using F_filtered_list = F_filtered_arg_list::template TF_combine<F_filtered_child_list>;

                using F = F_filtered_list::template TF_apply<TF_template_targ_tree>;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using F_normalized = typename F_normalized_helper_internal_targ::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            struct F_flatten_helper_internal_targ
            {

                template<typename F_child__>
                using TF_expand_child = typename F_child__::F_flatten;

                using F_filtered_arg_list = TF_template_targ_list<F_arg>;
                using F_filtered_list = F_filtered_arg_list::template TF_join<TF_expand_child<F_childs__>...>;

                using F = F_filtered_list;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using F_flatten = typename F_flatten_helper_internal_targ::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<typename F_tree__, template<typename F_in__> class... TF_multiple_filter_semantics__>
            struct TF_filter_multiple_semantics_helper_internal_targ;
            template<typename F_tree__>
            struct TF_filter_multiple_semantics_helper_internal_targ<F_tree__> {

                using F = F_tree__;

            };
            template<
                typename F_tree__,
                template<typename F_in__> class TF_first_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_filter_semantics__
            >
            struct TF_filter_multiple_semantics_helper_internal_targ<
                F_tree__,
                TF_first_filter_semantics__,
                TF_rest_multiple_filter_semantics__...
            >
            {

                using F_filtered_this_list = TF_template_targ_list<F_this>::template TF_filter<TF_first_filter_semantics__>;

                using F_filtered_tree = TF_nth_template_targ<
                    (F_filtered_this_list::count == 1),
                    TF_template_targ_tree<>,
                    typename F_filtered_this_list::template TF_try_at<0>
                >;

                using F_normalized_filtered_tree = typename F_filtered_tree::F_normalized;

                using F = typename TF_filter_multiple_semantics_helper_internal_targ<
                    F_normalized_filtered_tree,
                    TF_rest_multiple_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter = typename TF_filter_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_filter_semantics__...
            >::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<typename F_tree__, template<typename F_in__> class... TF_multiple_filter_semantics__>
            struct TF_filter_child_multiple_semantics_helper_internal_targ;
            template<typename F_tree__>
            struct TF_filter_child_multiple_semantics_helper_internal_targ<F_tree__> {

                using F = F_tree__;

            };
            template<
                typename F_tree__,
                template<typename F_in__> class TF_first_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_filter_semantics__
            >
            struct TF_filter_child_multiple_semantics_helper_internal_targ<
                F_tree__,
                TF_first_filter_semantics__,
                TF_rest_multiple_filter_semantics__...
            >
            {

                template<typename F_child__>
                using TF_filter_child = F_child__::template TF_filter<TF_first_filter_semantics__>;

                using F_filtered_child_list = TF_template_targ_list<TF_filter_child<F_childs__>...>;
                using F_filtered_list = TF_template_targ_list<F_arg>::template TF_combine<F_filtered_child_list>;

                using F_filtered_tree = F_filtered_list::template TF_apply<TF_template_targ_tree>;

                using F_normalized_filtered_tree = typename F_filtered_tree::F_normalized;

                using F = typename TF_filter_child_multiple_semantics_helper_internal_targ<
                    F_normalized_filtered_tree,
                    TF_rest_multiple_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter_childs = typename TF_filter_child_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_filter_semantics__...
            >::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<typename F_tree__, template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            struct TF_invert_filter_multiple_semantics_helper_internal_targ;
            template<typename F_tree__>
            struct TF_invert_filter_multiple_semantics_helper_internal_targ<F_tree__> {

                using F = F_tree__;

            };
            template<
                typename F_tree__,
                template<typename F_in__> class TF_first_invert_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_invert_filter_semantics__
            >
            struct TF_invert_filter_multiple_semantics_helper_internal_targ<
                F_tree__,
                TF_first_invert_filter_semantics__,
                TF_rest_multiple_invert_filter_semantics__...
            >
            {

                using F_invert_filtered_this_list = TF_template_targ_list<F_this>::template TF_invert_filter<TF_first_invert_filter_semantics__>;

                using F_invert_filtered_tree = TF_nth_template_targ<
                    (F_invert_filtered_this_list::count == 1),
                    TF_template_targ_tree<>,
                    typename F_invert_filtered_this_list::template TF_try_at<0>
                >;

                using F_normalized_invert_filtered_tree = typename F_invert_filtered_tree::F_normalized;

                using F = typename TF_invert_filter_multiple_semantics_helper_internal_targ<
                    F_normalized_invert_filtered_tree,
                    TF_rest_multiple_invert_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            using TF_invert_filter = typename TF_invert_filter_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_invert_filter_semantics__...
            >::F;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            template<typename F_tree__, template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            struct TF_invert_filter_child_multiple_semantics_helper_internal_targ;
            template<typename F_tree__>
            struct TF_invert_filter_child_multiple_semantics_helper_internal_targ<F_tree__> {

                using F = F_tree__;

            };
            template<
                typename F_tree__,
                template<typename F_in__> class TF_first_invert_filter_semantics__,
                template<typename F_in__> class... TF_rest_multiple_invert_filter_semantics__
            >
            struct TF_invert_filter_child_multiple_semantics_helper_internal_targ<
                F_tree__,
                TF_first_invert_filter_semantics__,
                TF_rest_multiple_invert_filter_semantics__...
            >
            {

                template<typename F_child__>
                using TF_invert_filter_child = F_child__::template TF_invert_filter<TF_first_invert_filter_semantics__>;

                using F_invert_filtered_child_list = TF_template_targ_list<TF_invert_filter_child<F_childs__>...>;
                using F_invert_filtered_list = TF_template_targ_list<F_arg>::template TF_combine<F_invert_filtered_child_list>;

                using F_invert_filtered_tree = F_invert_filtered_list::template TF_apply<TF_template_targ_tree>;

                using F_normalized_invert_filtered_tree = typename F_invert_filtered_tree::F_normalized;

                using F = typename TF_invert_filter_child_multiple_semantics_helper_internal_targ<
                    F_normalized_invert_filtered_tree,
                    TF_rest_multiple_invert_filter_semantics__...
                >::F;

            };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_invert_filter_semantics__>
            using TF_invert_filter_childs = typename TF_invert_filter_child_multiple_semantics_helper_internal_targ<
                F_this,
                TF_multiple_invert_filter_semantics__...
            >::F;

        };

    }

}