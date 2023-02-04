#pragma once

/** @file ncpp/utilities/templated_for.hpp
*   @brief Contains macros and functions to create the loop template.
*/



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        namespace templated_for_helper {

            template<template<sz index__> typename f_type_t__, b8 is_end__, sz end__, sz index__, typename... arg_types__>
            struct step_t {



            };

            template<template<sz index__> typename f_type_t__, b8 is_end__, sz end__, sz index__, typename... arg_types__>
            inline void step_invoke_t(arg_types__&&... args) {

                step_t<f_type_t__, is_end__, end__, index__, arg_types__...>::invoke(std::forward<arg_types__>(args)...);
            }

            template<template<sz index__> typename f_type_t__, sz end__, sz index__, typename... arg_types__>
            struct step_t<f_type_t__, true, end__, index__, arg_types__...> {

                static inline void invoke(arg_types__&&... args) {



                }

            };

            template<template<sz index__> typename f_type_t__, sz end__, sz index__, typename... arg_types__>
            struct step_t<f_type_t__, false, end__, index__, arg_types__...> {

                static inline void invoke(arg_types__&&... args) {

                    f_type_t__<index__>::invoke(std::forward<arg_types__>(args)...);

                    step_invoke_t<f_type_t__, index__ + 1 == end__, end__, index__ + 1, arg_types__...>(std::forward<arg_types__>(args)...);

                }

            };
            
        }



        /**
         *  The macro using to create a function representing the body of loop template.
         *  @param Name the function name.
         *  @param Params the parameters.
         *  @param IndexName__ the 'index' template argument name.
         *  @param Body the body of loop template. 
         */
        #define NCPP_LOOP_FUNCTION_T(Name, Params, IndexName__, Body) \
        template<sz IndexName__>\
        struct Name {\
        \
	        static inline void invoke Params { Body; }; \
        \
        };


 
        /**
        *   The function template helping run a loop which the index__ be a template argument.
        *   @param <f_type_t__> the struct template that has the only one template argument <index__> and the invoke(args...) function. 
        *   @param <begin__> the integer representing the begin__ of the loop
        *   @param <end__> the integer representing the end__ of the loop
        *   @param <arg_types__...> types of each argument in the invoke function
        *   @param args... the arguments forwarding to invoke function
        */
        template<template<sz index__> typename f_type_t__, sz begin__, sz end__, typename... arg_types__>
        inline void templated_for_t(arg_types__&&... args) {

            static_warning(end__ > begin__, "end__ > begin__, templated_for_t will not be executed.");

            templated_for_helper::step_invoke_t<f_type_t__, (end__ <= begin__), end__, begin__, arg_types__...>(std::forward<arg_types__>(args)...);

        }

    }

}