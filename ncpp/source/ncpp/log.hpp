#pragma once

/** @file ncpp/log.hpp
*	@brief Implement logging functionalities.
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

#include <ncpp/containers/.hpp>
#include <ncpp/utilities/type_info.hpp>
#include <ncpp/utilities/is_streamable.hpp>
#include <ncpp/iostream.hpp>

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



#ifdef NCPP_ENABLE_LOG_COLOR

#define NCPP_FOREGROUND_BACK "\x1B[30m"
#define NCPP_FOREGROUND_RED "\x1B[31m"
#define NCPP_FOREGROUND_GREEN "\x1B[32m"
#define NCPP_FOREGROUND_YELLOW "\x1B[33m"
#define NCPP_FOREGROUND_BLUE "\x1B[34m"
#define NCPP_FOREGROUND_MAGNETA "\x1B[35m"
#define NCPP_FOREGROUND_CYAN "\x1B[36m"
#define NCPP_FOREGROUND_WHITE "\x1B[37m"
#define NCPP_FOREGROUND_BRIGHT_BACK "\x1B[90m"
#define NCPP_FOREGROUND_BRIGHT_RED "\x1B[91m"
#define NCPP_FOREGROUND_BRIGHT_GREEN "\x1B[92m"
#define NCPP_FOREGROUND_BRIGHT_YELLOW "\x1B[93m"
#define NCPP_FOREGROUND_BRIGHT_BLUE "\x1B[94m"
#define NCPP_FOREGROUND_BRIGHT_MAGNETA "\x1B[95m"
#define NCPP_FOREGROUND_BRIGHT_CYAN "\x1B[96m"
#define NCPP_FOREGROUND_BRIGHT_WHITE "\x1B[97m"

#define NCPP_BACKGROUND_BACK "\x1B[40m"
#define NCPP_BACKGROUND_RED "\x1B[41m"
#define NCPP_BACKGROUND_GREEN "\x1B[42m"
#define NCPP_BACKGROUND_YELLOW "\x1B[43m"
#define NCPP_BACKGROUND_BLUE "\x1B[44m"
#define NCPP_BACKGROUND_MAGNETA "\x1B[45m"
#define NCPP_BACKGROUND_CYAN "\x1B[46m"
#define NCPP_BACKGROUND_WHITE "\x1B[47m"
#define NCPP_BACKGROUND_BRIGHT_BACK "\x1B[100m"
#define NCPP_BACKGROUND_BRIGHT_RED "\x1B[101m"
#define NCPP_BACKGROUND_BRIGHT_GREEN "\x1B[102m"
#define NCPP_BACKGROUND_BRIGHT_YELLOW "\x1B[103m"
#define NCPP_BACKGROUND_BRIGHT_BLUE "\x1B[104m"
#define NCPP_BACKGROUND_BRIGHT_MAGNETA "\x1B[105m"
#define NCPP_BACKGROUND_BRIGHT_CYAN "\x1B[106m"
#define NCPP_BACKGROUND_BRIGHT_WHITE "\x1B[107m"

#define NCPP_RESET_CONSOLE_COLOR "\033[0m"

#else

#define NCPP_FOREGROUND_BACK ""
#define NCPP_FOREGROUND_RED ""
#define NCPP_FOREGROUND_GREEN ""
#define NCPP_FOREGROUND_YELLOW ""
#define NCPP_FOREGROUND_BLUE ""
#define NCPP_FOREGROUND_MAGNETA ""
#define NCPP_FOREGROUND_CYAN ""
#define NCPP_FOREGROUND_WHITE ""
#define NCPP_FOREGROUND_BRIGHT_BACK ""
#define NCPP_FOREGROUND_BRIGHT_RED ""
#define NCPP_FOREGROUND_BRIGHT_GREEN ""
#define NCPP_FOREGROUND_BRIGHT_YELLOW ""
#define NCPP_FOREGROUND_BRIGHT_BLUE ""
#define NCPP_FOREGROUND_BRIGHT_MAGNETA ""
#define NCPP_FOREGROUND_BRIGHT_CYAN ""
#define NCPP_FOREGROUND_BRIGHT_WHITE ""

#define NCPP_BACKGROUND_BACK ""
#define NCPP_BACKGROUND_RED ""
#define NCPP_BACKGROUND_GREEN ""
#define NCPP_BACKGROUND_YELLOW ""
#define NCPP_BACKGROUND_BLUE ""
#define NCPP_BACKGROUND_MAGNETA ""
#define NCPP_BACKGROUND_CYAN ""
#define NCPP_BACKGROUND_WHITE ""
#define NCPP_BACKGROUND_BRIGHT_BACK ""
#define NCPP_BACKGROUND_BRIGHT_RED ""
#define NCPP_BACKGROUND_BRIGHT_GREEN ""
#define NCPP_BACKGROUND_BRIGHT_YELLOW ""
#define NCPP_BACKGROUND_BRIGHT_BLUE ""
#define NCPP_BACKGROUND_BRIGHT_MAGNETA ""
#define NCPP_BACKGROUND_BRIGHT_CYAN ""
#define NCPP_BACKGROUND_BRIGHT_WHITE ""

#define NCPP_RESET_CONSOLE_COLOR ""

#endif



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef NCPP_ENABLE_LOG_COLOR

#define NCPP_FOREGROUND_BACK_TEXT L"\x1B[30m"
#define NCPP_FOREGROUND_RED_TEXT L"\x1B[31m"
#define NCPP_FOREGROUND_GREEN_TEXT L"\x1B[32m"
#define NCPP_FOREGROUND_YELLOW_TEXT L"\x1B[33m"
#define NCPP_FOREGROUND_BLUE_TEXT L"\x1B[34m"
#define NCPP_FOREGROUND_MAGNETA_TEXT L"\x1B[35m"
#define NCPP_FOREGROUND_CYAN_TEXT L"\x1B[36m"
#define NCPP_FOREGROUND_WHITE_TEXT L"\x1B[37m"
#define NCPP_FOREGROUND_BRIGHT_BACK_TEXT L"\x1B[90m"
#define NCPP_FOREGROUND_BRIGHT_RED_TEXT L"\x1B[91m"
#define NCPP_FOREGROUND_BRIGHT_GREEN_TEXT L"\x1B[92m"
#define NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT L"\x1B[93m"
#define NCPP_FOREGROUND_BRIGHT_BLUE_TEXT L"\x1B[94m"
#define NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT L"\x1B[95m"
#define NCPP_FOREGROUND_BRIGHT_CYAN_TEXT L"\x1B[96m"
#define NCPP_FOREGROUND_BRIGHT_WHITE_TEXT L"\x1B[97m"

#define NCPP_BACKGROUND_BACK_TEXT L"\x1B[40m"
#define NCPP_BACKGROUND_RED_TEXT L"\x1B[41m"
#define NCPP_BACKGROUND_GREEN_TEXT L"\x1B[42m"
#define NCPP_BACKGROUND_YELLOW_TEXT L"\x1B[43m"
#define NCPP_BACKGROUND_BLUE_TEXT L"\x1B[44m"
#define NCPP_BACKGROUND_MAGNETA_TEXT L"\x1B[45m"
#define NCPP_BACKGROUND_CYAN_TEXT L"\x1B[46m"
#define NCPP_BACKGROUND_WHITE_TEXT L"\x1B[47m"
#define NCPP_BACKGROUND_BRIGHT_BACK_TEXT L"\x1B[100m"
#define NCPP_BACKGROUND_BRIGHT_RED_TEXT L"\x1B[101m"
#define NCPP_BACKGROUND_BRIGHT_GREEN_TEXT L"\x1B[102m"
#define NCPP_BACKGROUND_BRIGHT_YELLOW_TEXT L"\x1B[103m"
#define NCPP_BACKGROUND_BRIGHT_BLUE_TEXT L"\x1B[104m"
#define NCPP_BACKGROUND_BRIGHT_MAGNETA_TEXT L"\x1B[105m"
#define NCPP_BACKGROUND_BRIGHT_CYAN_TEXT L"\x1B[106m"
#define NCPP_BACKGROUND_BRIGHT_WHITE_TEXT L"\x1B[107m"

#define NCPP_RESET_CONSOLE_COLOR_TEXT L"\033[0m"

#else

#define NCPP_FOREGROUND_BACK_TEXT L""
#define NCPP_FOREGROUND_RED_TEXT L""
#define NCPP_FOREGROUND_GREEN_TEXT L""
#define NCPP_FOREGROUND_YELLOW_TEXT L""
#define NCPP_FOREGROUND_BLUE_TEXT L""
#define NCPP_FOREGROUND_MAGNETA_TEXT L""
#define NCPP_FOREGROUND_CYAN_TEXT L""
#define NCPP_FOREGROUND_WHITE_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_BACK_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_RED_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_GREEN_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_BLUE_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_CYAN_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_WHITE_TEXT L""

#define NCPP_BACKGROUND_BACK_TEXT L""
#define NCPP_BACKGROUND_RED_TEXT L""
#define NCPP_BACKGROUND_GREEN_TEXT L""
#define NCPP_BACKGROUND_YELLOW_TEXT L""
#define NCPP_BACKGROUND_BLUE_TEXT L""
#define NCPP_BACKGROUND_MAGNETA_TEXT L""
#define NCPP_BACKGROUND_CYAN_TEXT L""
#define NCPP_BACKGROUND_WHITE_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_BACK_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_RED_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_GREEN_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_YELLOW_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_BLUE_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_MAGNETA_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_CYAN_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_WHITE_TEXT L""

#define NCPP_RESET_CONSOLE_COLOR_TEXT L""

#endif



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

#pragma region Colorized Contents
	/**
	 *	Wraps content string inside to be streamed out with low light color.
	 */
	struct F_cout_lowlight {
		containers::F_string content;
	};
	/**
	 *	Wraps content string inside to be streamed out with field name color.
	 */
	struct F_cout_field_name {
		containers::F_string content;
	};



	/**
	 *	Wraps content string inside to be streamed out with low light color.
	 */
	struct F_wcout_lowlight {
		containers::F_wstring content;
	};
	/**
	 *	Wraps content string inside to be streamed out with field name color.
	 */
	struct F_wcout_field_name {
		containers::F_wstring content;
	};



    /**
     *	Wraps nanoseconds number inside to be streamed out with nanoseconds color.
     */
    struct F_cout_nanoseconds {
        u64 nanoseconds;
    };

    namespace internal {

        template<typename F__>
        struct TF_cout_value_helper {

            using F = F__;

        };

        template<>
        struct TF_cout_value_helper<b8> {

            struct F {

                b8 value;

            };

        };

        template<>
        struct TF_cout_value_helper<f32> {

            struct F {

                f32 value;

            };

        };
        template<>
        struct TF_cout_value_helper<f64> {

            struct F {

                f64 value;

            };

        };

        template<>
        struct TF_cout_value_helper<i8> {

            struct F {

                i8 value;

            };

        };
        template<>
        struct TF_cout_value_helper<i16> {

            struct F {

                i16 value;

            };

        };
        template<>
        struct TF_cout_value_helper<i32> {

            struct F {

                i32 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                        ncpp::F_ostream& os,
                        const F& input
                ) {

                    os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<i64> {

            struct F {

                i64 value;

            };

        };

        template<>
        struct TF_cout_value_helper<u8> {

            struct F {

                u8 value;

            };

        };
        template<>
        struct TF_cout_value_helper<u16> {

            struct F {

                u16 value;

            };

        };
        template<>
        struct TF_cout_value_helper<u32> {

            struct F {

                u32 value;

            };

        };
        template<>
        struct TF_cout_value_helper<u64> {

            struct F {

                u64 value;

            };

        };

        template<>
        struct TF_cout_value_helper<const char*> {

            struct F {

                const char* value;

            };

        };
        template<>
        struct TF_cout_value_helper<const wchar_t*> {

            struct F {

                const wchar_t* value;

            };

        };

        template<typename F_char__, typename F_allocator__>
        struct TF_cout_value_helper<containers::TF_string<F_char__, F_allocator__>> {

            struct F {

                containers::TF_string<F_char__, F_allocator__> value;

            };

        };

    }

    template<typename F__>
    using TF_cout_value = typename internal::TF_cout_value_helper<F__>::F;

    template<typename F__>
    NCPP_FORCE_INLINE TF_cout_value<F__> T_cout_value(const F__& value){

        return { value };
    }

#pragma endregion

}




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
 *    Streams out containers::F_string.
 */
template<class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::basic_string<wchar_t, F_allocator__>& str)
{

    os << ncpp::containers::to_string(str.c_str());

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
 *	Streams out containers::F_string.
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

    os << ncpp::containers::to_wstring(str.c_str());

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



#pragma region Colorized Contents

/**
 *	Streams out F_cout_lowlight.
 */
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
	ncpp::F_ostream& os,
	const ncpp::F_cout_lowlight& input
) {

	if (&os != &ncpp::cout)
		return os << input.content.c_str();

	return (os << (NCPP_FOREGROUND_BRIGHT_BACK + input.content + NCPP_RESET_CONSOLE_COLOR).c_str());
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
	ncpp::F_wostream& os,
	const ncpp::F_wcout_lowlight& input
) {

	if (&os != &ncpp::wcout)
		return os << input.content.c_str();

	return (os << (NCPP_FOREGROUND_BRIGHT_BACK_TEXT + input.content + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str());
}


/**
 *	Streams out F_cout_field_name.
 */
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
	ncpp::F_ostream& os,
	const ncpp::F_cout_field_name& input
) {

	if (&os != &ncpp::cout)
		return os << input.content.c_str();

	return (os << (NCPP_FOREGROUND_CYAN + input.content + NCPP_RESET_CONSOLE_COLOR).c_str());
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
	ncpp::F_wostream& os,
	const ncpp::F_wcout_field_name& input
) {

	if (&os != &ncpp::wcout)
		return os << input.content.c_str();

	return (os << (NCPP_FOREGROUND_CYAN_TEXT + input.content + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str());
}



/**
 *	Streams out F_cout_nanoseconds.
 */
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
	ncpp::F_ostream& os,
	const ncpp::F_cout_nanoseconds& input
) {

	if (&os != &ncpp::cout)
		return os << input.nanoseconds;

	return (os << (NCPP_FOREGROUND_BLUE + ncpp::containers::T_to_string<char>(input.nanoseconds) + NCPP_RESET_CONSOLE_COLOR).c_str());
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
	ncpp::F_wostream& os,
	const ncpp::F_cout_nanoseconds& input
) {

	if (&os != &ncpp::wcout)
		return os << input.nanoseconds;

	return (os << (NCPP_FOREGROUND_BLUE_TEXT + ncpp::containers::T_to_string<wchar_t>(input.nanoseconds) + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str());
}



NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::b8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_RED;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::f32>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_MAGNETA;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::f64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_MAGNETA;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::i8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::i16>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
//NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
//    ncpp::F_ostream& os,
//    const ncpp::TF_cout_value<ncpp::i32>& input
//) {
//
//    os << NCPP_FOREGROUND_BRIGHT_CYAN;
//
//    os << input.value;
//
//    os << NCPP_RESET_CONSOLE_COLOR;
//
//    return os;
//}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::i64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::u8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::u16>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::u32>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<ncpp::u64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR;

    return os;
}

template<typename F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<eastl::basic_string<char, F_allocator__>>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_GREEN << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<const char*>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_GREEN << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR;

    return os;
}

template<typename F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<eastl::basic_string<wchar_t, F_allocator__>>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_YELLOW << 'L' << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
    ncpp::F_ostream& os,
    const ncpp::TF_cout_value<const wchar_t*>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_YELLOW << 'L' << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR;

    return os;
}



NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::b8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_RED_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::f32>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::f64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::i8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::i16>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::i32>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::i64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}

NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::u8>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::u16>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::u32>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<ncpp::u64>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

    os << input.value;

    os << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}

template<typename F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<eastl::basic_string<char, F_allocator__>>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<const char*>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT << '"';

    os << input.value;

    os << '"' << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}

template<typename F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<eastl::basic_string<wchar_t, F_allocator__>>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT << L'L' << L'"';

    os << input.value;

    os << L'"' << NCPP_RESET_CONSOLE_COLOR_TEXT;

    return os;
}
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_cout_value<const wchar_t*>& input
) {

    os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT << L'L' << L'"';

    os << input.value;

    os << L'"' << NCPP_RESET_CONSOLE_COLOR_TEXT;

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

        os << ncpp::F_cout_lowlight{"..."};

		return os;
	}

	os << NCPP_FOREGROUND_YELLOW << "vector" << NCPP_RESET_CONSOLE_COLOR
    << ncpp::F_cout_lowlight{"<"} << (NCPP_FOREGROUND_BLUE + ncpp::utilities::T_type_name<F_item__>() + NCPP_RESET_CONSOLE_COLOR).c_str()
    << ncpp::F_cout_lowlight{">"}
    << ncpp::F_cout_lowlight{"("} << (NCPP_FOREGROUND_MAGNETA + ncpp::containers::T_to_string<char>(input.first.size()) + NCPP_RESET_CONSOLE_COLOR).c_str()
    << ncpp::F_cout_lowlight{")"}
    << " ";
    
    os << ncpp::F_cout_lowlight{"{"} << std::endl;

	for (ncpp::sz i = 0; i < input.first.size(); ++i) {

		for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}

        os << ncpp::F_cout_field_name{ncpp::containers::T_to_string<char>(i)} << ncpp::F_cout_lowlight{": "};

		ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

		if (i != input.first.size() - 1)
            os << ncpp::F_cout_lowlight{","};

		os << std::endl;

	}

	for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

		os << " ";

	}
    os << ncpp::F_cout_lowlight{"}"};

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

        os << ncpp::F_wcout_lowlight{L"..."};

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"vector" << NCPP_RESET_CONSOLE_COLOR_TEXT
    << ncpp::F_wcout_lowlight{L"<"} << (NCPP_FOREGROUND_BLUE_TEXT + ncpp::utilities::T_type_name<F_item__, wchar_t>() + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str()
    << ncpp::F_wcout_lowlight{L">"}
    << ncpp::F_wcout_lowlight{L"("} << (NCPP_FOREGROUND_MAGNETA_TEXT + ncpp::containers::T_to_string<wchar_t>(input.first.size()) + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str()
    << ncpp::F_wcout_lowlight{L")"}
    << L" ";

    os << ncpp::F_wcout_lowlight{L"{"} << std::endl;

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::F_wcout_field_name{ncpp::containers::T_to_string<wchar_t>(i)} << ncpp::F_wcout_lowlight{L": "};

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != input.first.size() - 1)
            os << ncpp::F_wcout_lowlight{L","};

        os << std::endl;

    }

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }
    os << ncpp::F_wcout_lowlight{L"}"};

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

        os << ncpp::F_cout_lowlight{"..."};

		return os;
	}

	os << NCPP_FOREGROUND_YELLOW << "initializer_list" << NCPP_RESET_CONSOLE_COLOR
    << ncpp::F_cout_lowlight{"<"} << (NCPP_FOREGROUND_BLUE + ncpp::utilities::T_type_name<F_item__>() + NCPP_RESET_CONSOLE_COLOR).c_str()
    << ncpp::F_cout_lowlight{">"}
    << " ";

    os << ncpp::F_cout_lowlight{"{"} << std::endl;

	auto j = input.first.begin();

	for (ncpp::sz i = 0; i < input.first.size(); ++i) {

		for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}

        os << ncpp::F_cout_field_name{ncpp::containers::T_to_string<char>(i)} << ncpp::F_cout_lowlight{": "};

		ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

		if (i != input.first.size() - 1)
            os << ncpp::F_cout_lowlight{","};

		os << std::endl;

		++j;

	}

	for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

		os << " ";

	}
    os << ncpp::F_cout_lowlight{"}"};

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

        os << ncpp::F_wcout_lowlight{L"..."};

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"initializer_list" << NCPP_RESET_CONSOLE_COLOR_TEXT
    << ncpp::F_wcout_lowlight{L"<"} << (NCPP_FOREGROUND_BLUE_TEXT + ncpp::utilities::T_type_name<F_item__, wchar_t>() + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str()
    << ncpp::F_wcout_lowlight{L">"}
    << L" ";

    os << ncpp::F_wcout_lowlight{L"{"} << std::endl;

    auto j = input.first.begin();

    for (ncpp::sz i = 0; i < input.first.size(); ++i) {

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::F_wcout_field_name{ncpp::containers::T_to_string<wchar_t>(i)} << ncpp::F_wcout_lowlight{L": "};

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(*j), input.second + 1 });

        if (i != input.first.size() - 1)
            os << ncpp::F_wcout_lowlight{L","};

        os << std::endl;

        ++j;

    }

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os <<L" ";

    }
    os << ncpp::F_wcout_lowlight{L"}"};

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

        os << ncpp::F_cout_lowlight{"..."};

		return os;
	}

	os << NCPP_FOREGROUND_YELLOW << "array" << NCPP_RESET_CONSOLE_COLOR
    << ncpp::F_cout_lowlight{"<"} << (NCPP_FOREGROUND_BLUE + ncpp::utilities::T_type_name<F_item__>() + NCPP_RESET_CONSOLE_COLOR).c_str()
    << ncpp::F_cout_lowlight{","}
    << (NCPP_FOREGROUND_MAGNETA + ncpp::containers::T_to_string<char>(input.first.size()) + NCPP_RESET_CONSOLE_COLOR).c_str()
    << ncpp::F_cout_lowlight{">"}
    << " ";

    os << ncpp::F_cout_lowlight{"{"} << std::endl;



	for (ncpp::sz i = 0; i < size__; ++i) {

		for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}

        os << ncpp::F_cout_field_name{ncpp::containers::T_to_string<char>(i)} << ncpp::F_cout_lowlight{": "};

		ncpp::T_safe_ostream_with_tab<ncpp::F_ostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

		if (i != size__ - 1)
            os << ncpp::F_cout_lowlight{","};

		os << std::endl;

	}

	for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

		os << " ";

	}

    os << ncpp::F_cout_lowlight{"}"};

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

        os << ncpp::F_wcout_lowlight{L"..."};

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"array" << NCPP_RESET_CONSOLE_COLOR_TEXT
    << ncpp::F_wcout_lowlight{L"<"} << (NCPP_FOREGROUND_BLUE_TEXT + ncpp::utilities::T_type_name<F_item__, wchar_t>() + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str()
    << ncpp::F_wcout_lowlight{L","}
    << (NCPP_FOREGROUND_MAGNETA_TEXT + ncpp::containers::T_to_string<wchar_t>(input.first.size()) + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str()
    << ncpp::F_wcout_lowlight{L">"}
    << L" ";

    os << ncpp::F_wcout_lowlight{L"{"} << std::endl;



    for (ncpp::sz i = 0; i < size__; ++i) {

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }

        os << ncpp::F_wcout_field_name{ncpp::containers::T_to_string<wchar_t>(i)} << ncpp::F_wcout_lowlight{L": "};

        ncpp::T_safe_ostream_with_tab<ncpp::F_wostream, ncpp::TF_cout_value<F_item__>>(os, { ncpp::T_cout_value(input.first[i]), input.second + 1 });

        if (i != size__ - 1)
            os << ncpp::F_wcout_lowlight{L","};

        os << std::endl;

    }

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }

    os << ncpp::F_wcout_lowlight{L"}"};

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


