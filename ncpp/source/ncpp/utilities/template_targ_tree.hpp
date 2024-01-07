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

        template<>
        struct TF_template_targ_tree<> {

        public:
            using F_this = TF_template_targ_tree<>;

            using F_arg = void;
            using F_childs = TF_template_targ_list<>;

            static constexpr b8 is_null = true;
            static constexpr b8 is_valid = false;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            template<template<typename F_in__> class... TF_multiple_filter_semantics__>
            using TF_filter = F_this;

        };



        template<typename F_arg__, typename... F_childs__>
        struct TF_template_targ_tree<F_arg__, F_childs__...>
        {

        public:
            using F_this = TF_template_targ_tree<F_arg__, F_childs__...>;

            using F_arg = F_arg__;
            using F_childs = TF_template_targ_list<F_childs__...>;

            static constexpr b8 is_null = false;
            static constexpr b8 is_valid = true;

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

                template<typename F_child__>
                struct TL_valid_child {

                    static constexpr b8 is_valid = F_child__::is_valid;

                };

                template<typename F_child__>
                using TF_filter_child = F_child__::template TF_filter<TF_first_filter_semantics__>;

                using F_filtered_arg_list = TF_template_targ_list<F_arg>::template TF_filter<TF_first_filter_semantics__>;
                using F_filtered_child_list = TF_template_targ_list<TF_filter_child<F_childs__>...>::template TF_filter<TL_valid_child>;

                using F_filtered_list = F_filtered_arg_list::template TF_combine<F_filtered_child_list>;

                using F_valid_filtered_tree = F_filtered_list::template TF_apply<TF_template_targ_tree>;

                using F_filtered_tree = TF_nth_template_targ<
                    (F_filtered_arg_list::count == 1),
                    TF_template_targ_tree<>,
                    F_valid_filtered_tree
                >;

                using F = typename TF_filter_multiple_semantics_helper_internal_targ<
                    F_filtered_tree,
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

        };

    }

}