#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        namespace templated_for_helper {

            template<template<size_t index> typename f_type_t, bool is_end, size_t end, size_t index, typename... arg_types>
            struct step_t {



            };

            template<template<size_t index> typename f_type_t, bool is_end, size_t end, size_t index, typename... arg_types>
            inline void step_invoke_t(arg_types&&... args) {

                step_t<f_type_t, is_end, end, index, arg_types...>::invoke(std::forward<arg_types>(args)...);
            }

            template<template<size_t index> typename f_type_t, size_t end, size_t index, typename... arg_types>
            struct step_t<f_type_t, true, end, index, arg_types...> {

                static inline void invoke(arg_types&&... args) {



                }

            };

            template<template<size_t index> typename f_type_t, size_t end, size_t index, typename... arg_types>
            struct step_t<f_type_t, false, end, index, arg_types...> {

                static inline void invoke(arg_types&&... args) {

                    f_type_t<index>::invoke(std::forward<arg_types>(args)...);

                    step_invoke_t<f_type_t, index + 1 == end, end, index + 1, arg_types...>(std::forward<arg_types>(args)...);

                }

            };
            
        }



        template<template<size_t index> typename f_type_t, size_t begin, size_t end, typename... arg_types>
        inline void templated_for_t(arg_types&&... args) {

            static_warning(end > begin, "end > begin, templated_for_t will not be executed.");

            templated_for_helper::step_invoke_t<f_type_t, (end <= begin), end, begin, arg_types...>(std::forward<arg_types>(args)...);

        }

    }

}