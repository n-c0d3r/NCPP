#pragma once

/** @file ncpp/eastl_container_log.hpp
*	@brief Implement eastl container logging functionalities.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/string_utilities.hpp>
#include <ncpp/utilities/type_info.hpp>
#include <ncpp/utilities/is_streamable.hpp>
#include <ncpp/iostream.hpp>
#include <ncpp/log_colors.hpp>
#include <ncpp/colorized_log.hpp>

#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region String
/**
 *	Streams out containers::F_string.
 */
template<class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::basic_string<char, F_allocator__>& str)
{

    os << str.c_str();

    return os;
}
/**
 *    Streams out containers::F_wstring.
 */
template<class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::basic_string<wchar_t, F_allocator__>& str)
{

    os << ncpp::containers::T_to_string<char, F_allocator__>(str);

    return os;
}
/**
 *    Streams out const wchar_t*.
 */
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const wchar_t* str)
{

    os << ncpp::containers::to_string(str);

    return os;
}

/**
 *	Streams out containers::F_wstring.
 */
template<class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::basic_string<wchar_t, F_allocator__>& str)
{

    os << str.c_str();

    return os;
}
/**
 *    Streams out containers::F_string.
 */
template<class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::basic_string<char, F_allocator__>& str)
{

    os << ncpp::containers::T_to_string<wchar_t, F_allocator__>(str);

    return os;
}
/**
 *    Streams out const char*.
 */
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const char* str)
{

    os << ncpp::containers::to_wstring(str);

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Vector
/**
 *	Streams out eastl::vector with tabs.
 */
template<typename F_item__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::vector<F_item__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "vector"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

/**
 *	Streams out eastl::vector with no tab.
 */
template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::vector<F_item__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::vector<F_item__, F_allocator__>> { v, 0 };

    return os;
}



/**
 *    Streams out eastl::vector with tabs.
 */
template<typename F_item__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::vector<F_item__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"vector"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(L",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

/**
 *    Streams out eastl::vector with no tab.
 */
template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::vector<F_item__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::vector<F_item__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Initialier List
/**
 *	Streams out std::initialier_list<T> with tabs.
 */
template<typename F_item__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        std::initializer_list<F_item__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "initializer_list"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.begin())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{");

    auto j = input.first.begin();

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

        ++j;

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

/**
 *	Streams out std::initialier_list<T> with no tab.
 */
template<typename F_item__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const std::initializer_list<F_item__>& v)
{

    os << ncpp::TF_ostream_input<std::initializer_list<F_item__>> { v, 0 };

    return os;
}



/**
 *    Streams out std::initialier_list<T> with tabs.
 */
template<typename F_item__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        std::initializer_list<F_item__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"initializer_list"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.begin())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    auto j = input.first.begin();

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(L",");

        }
        else {

            os << std::endl;

        }

        ++j;

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os <<L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

/**
 *    Streams out std::initialier_list<T> with no tab.
 */
template<typename F_item__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const std::initializer_list<F_item__>& v)
{

    os << ncpp::TF_ostream_input<std::initializer_list<F_item__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Array
/**
 *	Streams out eastl::array<T, N> with tabs.
 */
template<typename F_item__, ncpp::sz size__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::array<F_item__, size__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "array"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(size__)
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (ncpp::sz i = 0; i < size__; ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != (size__ - 1)) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(size__ != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

    os << ncpp::T_cout_lowlight("}");

    return os;
}

/**
 *	Streams out eastl::array<T, N> with no tab.
 */
template<typename F_item__, ncpp::sz size__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::array<F_item__, size__>& v)
{

    os << ncpp::TF_ostream_input<eastl::array<F_item__, size__>> { v, 0 };

    return os;
}



/**
 *    Streams out eastl::array<T, N> with tabs.
 */
template<typename F_item__, ncpp::sz size__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::array<F_item__, size__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"array"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(size__)
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (ncpp::sz i = 0; i < size__; ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != (size__ - 1)) {

            os << ncpp::T_cout_lowlight(L",");

        }
        else {

            os << std::endl;

        }

    }

    if(size__ != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

/**
 *    Streams out eastl::array<T, N> with no tab.
 */
template<typename F_item__, ncpp::sz size__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::array<F_item__, size__>& v)
{

    os << ncpp::TF_ostream_input<eastl::array<F_item__, size__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Span
template<typename F_item__>
std::ostream& operator << (
    std::ostream& os,
    const ncpp::TF_ostream_input<
        eastl::span<F_item__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "span"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{");

    auto j = input.first.begin();

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

        ++j;

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__>
std::ostream& operator << (std::ostream& os, const eastl::span<F_item__>& v)
{

    os << ncpp::TF_ostream_input<eastl::span<F_item__>> { v, 0 };

    return os;
}



template<typename F_item__>
std::wostream& operator << (
    std::wostream& os,
    const ncpp::TF_ostream_input<
        eastl::span<F_item__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << L"span"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("data_p: ")
       << ncpp::T_cout_value(input.first.data())
       << ncpp::T_cout_lowlight(", ")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight("{");

    auto j = input.first.begin();

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

        ++j;

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__>
std::wostream& operator << (std::wostream& os, const eastl::span<F_item__>& v)
{

    os << ncpp::TF_ostream_input<eastl::span<F_item__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Deque
template<typename F_item__, class F_allocator__, unsigned subarray_size__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::deque<F_item__, F_allocator__, subarray_size__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "deque"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, class F_allocator__, unsigned subarray_size__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::deque<F_item__, F_allocator__, subarray_size__>& v)
{

    os << ncpp::TF_ostream_input<eastl::deque<F_item__, F_allocator__, subarray_size__>> { v, 0 };

    return os;
}



template<typename F_item__, class F_allocator__, unsigned subarray_size__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::deque<F_item__, F_allocator__, subarray_size__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"deque"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != input.first.size() - 1) {

            os << ncpp::T_cout_lowlight(L",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, class F_allocator__, unsigned subarray_size__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::deque<F_item__, F_allocator__, subarray_size__>& v)
{

    os << ncpp::TF_ostream_input<eastl::deque<F_item__, F_allocator__, subarray_size__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region List
template<typename F_item__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::list<F_item__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "list"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::list<F_item__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::list<F_item__, F_allocator__>> { v, 0 };

    return os;
}



template<typename F_item__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::list<F_item__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"list"
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::list<F_item__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::list<F_item__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Set
template<typename F_item__, typename F_compare__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::set<F_item__, F_compare__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "set"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, typename F_compare__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::set<F_item__, F_compare__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::set<F_item__, F_compare__, F_allocator__>> { v, 0 };

    return os;
}



template<typename F_item__, typename F_compare__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::set<F_item__, F_compare__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"set"
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, typename F_compare__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::set<F_item__, F_compare__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::set<F_item__, F_compare__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Map
template<typename F_key__, typename F_value__, typename F_compare__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::map<F_key__, F_value__, F_compare__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "map"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_key__>>(os, { ncpp::T_cout_value(i->first), input.second + 1 });

        os << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_value__>>(os, { ncpp::T_cout_value(i->second), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_key__, typename F_value__, typename F_compare__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::map<F_key__, F_value__, F_compare__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::map<F_key__, F_value__, F_compare__, F_allocator__>> { v, 0 };

    return os;
}



template<typename F_key__, typename F_value__, typename F_compare__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::map<F_key__, F_value__, F_compare__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"map"
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_key__>>(os, { ncpp::T_cout_value(i->first), input.second + 1 });

        os << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_value__>>(os, { ncpp::T_cout_value(i->second), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_key__, typename F_value__, typename F_compare__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::map<F_key__, F_value__, F_compare__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::map<F_key__, F_value__, F_compare__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Unordered Set
template<typename F_item__, typename F_hash__, typename F_predicate__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "unordered_set"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, typename F_hash__, typename F_predicate__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>> { v, 0 };

    return os;
}



template<typename F_item__, typename F_hash__, typename F_predicate__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"unordered_set"
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*i), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, typename F_hash__, typename F_predicate__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Unordered Map
template<typename F_key__, typename F_value__, typename F_hash__, typename F_predicate__, class F_allocator__>
ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_ostream_input<
        eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "unordered_map"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_key__>>(os, { ncpp::T_cout_value(i->first), input.second + 1 });

        os << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_value__>>(os, { ncpp::T_cout_value(i->second), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_key__, typename F_value__, typename F_hash__, typename F_predicate__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>> { v, 0 };

    return os;
}



template<typename F_key__, typename F_value__, typename F_hash__, typename F_predicate__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"unordered_map"
       << L" ";

    os << ncpp::T_cout_lowlight(L"{");

    for (auto i = input.first.begin(); i != input.first.end();) {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_key__>>(os, { ncpp::T_cout_value(i->first), input.second + 1 });

        os << ncpp::T_cout_lowlight(" -> ");

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_value__>>(os, { ncpp::T_cout_value(i->second), input.second + 1 });

        ++i;

        if (i != input.first.end()) {

            os << ncpp::T_cout_lowlight(",");

        }
        else {

            os << std::endl;

        }

    }

    if(input.first.size() != 0)
        for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_key__, typename F_value__, typename F_hash__, typename F_predicate__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Queue
template<typename F_item__, typename F_container__>
std::ostream& operator << (
    std::ostream& os,
    const ncpp::TF_ostream_input<
        eastl::queue<F_item__, F_container__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "queue"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{") << std::endl;

    for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

        os << " ";

    }

    ncpp::T_safe_ostream_with_tab<
        ncpp::F_ostream,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        >
    >(
        os,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        > {
            ncpp::T_cout_value(input.first.get_container()),
            input.second + 1
        }
    );

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << " ";

    }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, typename F_container__>
std::ostream& operator << (std::ostream& os, const eastl::queue<F_item__, F_container__>& v)
{

    os << ncpp::TF_ostream_input<eastl::queue<F_item__, F_container__>> { v, 0 };

    return os;
}



template<typename F_item__, typename F_container__>
std::wostream& operator << (
    std::wostream& os,
    const ncpp::TF_ostream_input<
        eastl::queue<F_item__, F_container__>
    >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"queue"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{") << std::endl;

    for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }

    ncpp::T_safe_ostream_with_tab<
        ncpp::F_wostream,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        >
    >(
        os,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        > {
            ncpp::T_cout_value(input.first.get_container()),
            input.second + 1
        }
    );

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, typename F_container__>
std::wostream& operator << (std::wostream& os, const eastl::queue<F_item__, F_container__>& v)
{

    os << ncpp::TF_ostream_input<eastl::queue<F_item__, F_container__>> { v, 0 };

    return os;
}
#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Stack
template<typename F_item__, typename F_container__>
std::ostream& operator << (
        std::ostream& os,
        const ncpp::TF_ostream_input<
                eastl::stack<F_item__, F_container__>
        >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "stack"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << " ";

    os << ncpp::T_cout_lowlight("{") << std::endl;

    for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

        os << " ";

    }

    ncpp::T_safe_ostream_with_tab<
        ncpp::F_ostream,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        >
    >(
        os,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        > {
            ncpp::T_cout_value(input.first.get_container()),
            input.second + 1
        }
    );

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << " ";

    }
    os << ncpp::T_cout_lowlight("}");

    return os;
}

template<typename F_item__, typename F_container__>
std::ostream& operator << (std::ostream& os, const eastl::stack<F_item__, F_container__>& v)
{

    os << ncpp::TF_ostream_input<eastl::stack<F_item__, F_container__>> { v, 0 };

    return os;
}



template<typename F_item__, typename F_container__>
std::wostream& operator << (
        std::wostream& os,
        const ncpp::TF_ostream_input<
                eastl::stack<F_item__, F_container__>
        >& input
)
{

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight(L"...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"stack"
       << ncpp::T_cout_lowlight("(")
       << ncpp::T_cout_lowlight("size: ")
       << ncpp::T_cout_value(input.first.size())
       << ncpp::T_cout_lowlight(")")
       << L" ";

    os << ncpp::T_cout_lowlight(L"{") << std::endl;

    for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }

    ncpp::T_safe_ostream_with_tab<
        ncpp::F_wostream,
        ncpp::TF_ostream_input<
            ncpp::TF_cout_value<F_container__>
        >
    >(
        os,
        ncpp::TF_ostream_input<
                ncpp::TF_cout_value<F_container__>
        > {
                ncpp::T_cout_value(input.first.get_container()),
                input.second + 1
        }
    );

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }
    os << ncpp::T_cout_lowlight(L"}");

    return os;
}

template<typename F_item__, typename F_container__>
std::wostream& operator << (std::wostream& os, const eastl::stack<F_item__, F_container__>& v)
{

    os << ncpp::TF_ostream_input<eastl::stack<F_item__, F_container__>> { v, 0 };

    return os;
}
#pragma endregion