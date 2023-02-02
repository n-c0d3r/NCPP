#pragma once

/**
 *  @file ncpp/utilities/last_template_arg.hpp
 *  @brief Implementing last_template_arg_t.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  Finding out the last template argument.
         */
        template<typename... arg_types>
        using last_template_arg_t = typename nth_template_arg_t<sizeof...(arg_types) - 1, arg_types...>;

    }

}