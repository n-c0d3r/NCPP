#pragma once

/**
 *  @file ncpp/utilities/first_template_arg.hpp
 *  @brief Implements first_template_arg_t.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  Finds out the first template argument.
         */
        template<typename... arg_types>
        using first_template_arg_t = typename nth_template_arg_t<0, arg_types...>;

    }

}