#pragma once

/**
 *  @file ncpp/utilities/last_template_arg.hpp
 *  @brief Implements last_template_arg_t.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  Finds out the last template argument.
         */
        template<typename... arg_types__>
        using last_template_arg_t = typename nth_template_arg_t<sizeof...(arg_types__) - 1, arg_types__...>;

    }

}