#pragma once

/**
 *  @file ncpp/utilities/nth___template_arg.hpp
 *  @brief Implements nth_template_arg_t.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        namespace nth___template_arg_helper {

            template<b8 is_single__, b8 is_nth__, sz nth_remain__, typename... arg_types__>
            struct nth_template_arg_t {

                using type = void;

            };

            template<sz nth_remain__, typename arg_type__>
            struct nth_template_arg_t<true, true, nth_remain__, arg_type__> {

                using type = arg_type__;

            };

            template<sz nth_remain__, typename arg_type__>
            struct nth_template_arg_t<true, false, nth_remain__, arg_type__> {

                using type = void;

            };

            template<sz nth_remain__, typename nth___arg_type__, typename... rest__>
            struct nth_template_arg_t<false, true, nth_remain__, nth___arg_type__, rest__...> {

                using type = nth___arg_type__;

            };

            template<sz nth_remain__, typename nth___arg_type__, typename... rest__>
            struct nth_template_arg_t<false, false, nth_remain__, nth___arg_type__, rest__...> {

                using type = typename nth_template_arg_t<sizeof...(rest__) == 1, nth_remain__ == 1, nth_remain__ - 1, rest__...>::type;

            };

        }



        /**
         *  Finds out the nth__ template argument.
         */
        template<sz nth__, typename... arg_types__>
        struct nth_template_arg_t {

            static_assert(nth__ < sizeof...(arg_types__), "invalid 'nth__' value!");



            using type = typename nth___template_arg_helper::nth_template_arg_t<sizeof...(arg_types__) == 1, nth__ == 0, nth__, arg_types__...>::type;

        };

    }

}