#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/nth_template_arg.hpp>



namespace ncpp {

    namespace tmp_helper {

        template<typename... arg_types>
        using first_template_arg_t = typename nth_template_arg_t<0, arg_types...>;

    }

}