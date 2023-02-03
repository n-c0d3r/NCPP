#pragma once

/**
 *  @file ncpp/utilities/nth_template_arg.hpp
 *  @brief Implements nth_template_arg_t.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        namespace nth_template_arg_helper {

            template<b8 is_single, b8 is_nth, sz nth_remain, typename... arg_types>
            struct nth_template_arg_t {

                using type = void;

            };

            template<sz nth_remain, typename arg_type>
            struct nth_template_arg_t<true, true, nth_remain, arg_type> {

                using type = arg_type;

            };

            template<sz nth_remain, typename arg_type>
            struct nth_template_arg_t<true, false, nth_remain, arg_type> {

                using type = void;

            };

            template<sz nth_remain, typename nth_arg_type, typename... rest>
            struct nth_template_arg_t<false, true, nth_remain, nth_arg_type, rest...> {

                using type = nth_arg_type;

            };

            template<sz nth_remain, typename nth_arg_type, typename... rest>
            struct nth_template_arg_t<false, false, nth_remain, nth_arg_type, rest...> {

                using type = typename nth_template_arg_t<sizeof...(rest) == 1, nth_remain == 1, nth_remain - 1, rest...>::type;

            };

        }



        /**
         *  Finds out the nth template argument.
         */
        template<sz nth, typename... arg_types>
        struct nth_template_arg_t {

            static_assert(nth < sizeof...(arg_types), "invalid 'nth' value!");



            using type = typename nth_template_arg_helper::nth_template_arg_t<sizeof...(arg_types) == 1, nth == 0, nth, arg_types...>::type;

        };

    }

}