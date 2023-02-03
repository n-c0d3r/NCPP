#pragma once

/** @file ncpp/utilities/templated_for.hpp
*   @brief Contains macros and functions to create the loop template.
*/



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        namespace templated_for_helper {

            template<template<sz index> typename f_type_t, b8 is_end, sz end, sz index, typename... arg_types>
            struct step_t {



            };

            template<template<sz index> typename f_type_t, b8 is_end, sz end, sz index, typename... arg_types>
            inline void step_invoke_t(arg_types&&... args) {

                step_t<f_type_t, is_end, end, index, arg_types...>::invoke(std::forward<arg_types>(args)...);
            }

            template<template<sz index> typename f_type_t, sz end, sz index, typename... arg_types>
            struct step_t<f_type_t, true, end, index, arg_types...> {

                static inline void invoke(arg_types&&... args) {



                }

            };

            template<template<sz index> typename f_type_t, sz end, sz index, typename... arg_types>
            struct step_t<f_type_t, false, end, index, arg_types...> {

                static inline void invoke(arg_types&&... args) {

                    f_type_t<index>::invoke(std::forward<arg_types>(args)...);

                    step_invoke_t<f_type_t, index + 1 == end, end, index + 1, arg_types...>(std::forward<arg_types>(args)...);

                }

            };
            
        }



        /**
         *  The macro using to create the body function of loop template.
         */
        #define NCPP_LOOP_FUNCTION_T(Name, Params, Body) \
        template<sz index>\
        struct Name {\
        \
	        static inline void invoke Params { Body; }; \
        \
        };


 
        /**
        *   The function template helping run a loop which the index be a template argument.
        *   @param <f_type_t> the struct template that has the only one template argument <index> and the invoke(args...) function. 
        *   @param <begin> the integer representing the begin of the loop
        *   @param <end> the integer representing the end of the loop
        *   @param <arg_types...> types of each argument in the invoke function
        *   @param args... the arguments forwarding to invoke function
        */
        template<template<sz index> typename f_type_t, sz begin, sz end, typename... arg_types>
        inline void templated_for_t(arg_types&&... args) {

            static_warning(end > begin, "end > begin, templated_for_t will not be executed.");

            templated_for_helper::step_invoke_t<f_type_t, (end <= begin), end, begin, arg_types...>(std::forward<arg_types>(args)...);

        }

    }

}