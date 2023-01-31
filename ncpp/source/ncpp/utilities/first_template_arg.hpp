#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/nth_template_arg.hpp>



namespace ncpp {

    namespace utilities {

        template<typename... arg_types>
        using first_template_arg_t = typename nth_template_arg_t<0, arg_types...>;

    }

}