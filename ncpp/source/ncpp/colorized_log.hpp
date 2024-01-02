#pragma once

/** @file ncpp/colorized_log.hpp
*	@brief Implement colorized logging functionalities.
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



namespace ncpp {

#pragma region Colorized Contents
	/**
	 *	Wraps content string inside to be streamed out with low light color.
	 */
    template<typename F__>
	struct TF_cout_lowlight {

        F__ value;

        friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                ncpp::F_ostream& os,
                const TF_cout_lowlight& input
        ) {

            if (&os == &ncpp::cout)
                os << NCPP_FOREGROUND_BRIGHT_BLACK;

            os << ncpp::containers::T_to_string<char, mem::F_default_allocator, F__>(input.value).c_str();

            if (&os == &ncpp::cout)
                os << NCPP_RESET_CONSOLE_COLOR;

            return os;
        }
        friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                ncpp::F_wostream& os,
                const TF_cout_lowlight& input
        ) {

            if (&os == &ncpp::wcout)
                os << NCPP_FOREGROUND_BRIGHT_BLACK_TEXT;

            os << ncpp::containers::T_to_string<wchar_t, mem::F_default_allocator, F__>(input.value).c_str();

            if (&os == &ncpp::wcout)
                os << NCPP_RESET_CONSOLE_COLOR_TEXT;

            return os;
        }

	};

    template<typename F__>
    NCPP_FORCE_INLINE TF_cout_lowlight<std::remove_reference_t<std::remove_const_t<F__>>> T_cout_lowlight(F__ value){

        return { value };
    }



	/**
	 *	Wraps content string inside to be streamed out with field name color.
	 */
    template<typename F__>
    struct TF_cout_field_name {

        F__ value;

        friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                ncpp::F_ostream& os,
                const TF_cout_field_name& input
        ) {

            if (&os == &ncpp::cout)
                os << NCPP_FOREGROUND_CYAN;

            os << ncpp::containers::T_to_string<char, mem::F_default_allocator, F__>(input.value).c_str();

            if (&os == &ncpp::cout)
                os << NCPP_RESET_CONSOLE_COLOR;

            return os;
        }
        friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                ncpp::F_wostream& os,
                const TF_cout_field_name& input
        ) {

            if (&os == &ncpp::wcout)
                os << NCPP_FOREGROUND_CYAN_TEXT;

            os << ncpp::containers::T_to_string<wchar_t, mem::F_default_allocator, F__>(input.value).c_str();

            if (&os == &ncpp::wcout)
                os << NCPP_RESET_CONSOLE_COLOR_TEXT;

            return os;
        }

    };

    template<typename F__>
    NCPP_FORCE_INLINE TF_cout_field_name<std::remove_reference_t<std::remove_const_t<F__>>> T_cout_field_name(F__ value){

        return { value };
    }



    /**
     *	Wraps nanoseconds number inside to be streamed out with nanoseconds color.
     */
    struct F_cout_nanoseconds {

        u64 nanoseconds;

        friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                ncpp::F_ostream& os,
                const ncpp::F_cout_nanoseconds& input
        ) {

            if (&os != &ncpp::cout)
                return os << input.nanoseconds;

            return (os << (NCPP_FOREGROUND_BLUE + ncpp::containers::T_to_string<char>(input.nanoseconds) + NCPP_RESET_CONSOLE_COLOR).c_str());
        }
        friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                ncpp::F_wostream& os,
                const ncpp::F_cout_nanoseconds& input
        ) {

            if (&os != &ncpp::wcout)
                return os << input.nanoseconds;

            return (os << (NCPP_FOREGROUND_BLUE_TEXT + ncpp::containers::T_to_string<wchar_t>(input.nanoseconds) + NCPP_RESET_CONSOLE_COLOR_TEXT).c_str());
        }

    };

    namespace internal {

        template<typename F__, typename...>
        struct TF_cout_value_helper_default_case;

        template<typename F__>
        struct TF_cout_value_helper_default_case<
            F__, 
            std::enable_if_t<
                (ncpp::utilities::T_is_ostreamable<F_ostream, F__>)
                || (ncpp::utilities::T_is_ostreamable<F_wostream, F__>),
                i32
            >
        > {

            using F = F__;

        };

        template<typename F__>
        struct TF_cout_value_helper_default_case<
            F__, 
            std::enable_if_t<
                (!ncpp::utilities::T_is_ostreamable<F_ostream, F__>)
                && (ncpp::utilities::T_is_ostreamable<F_wostream, F__>),
                i32
            >
        > {

            struct F {

                F__ value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_WHITE;

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_fullname<F__>();

                    if(&os == &cout)
                        os << ncpp::containers::to_string(
                            ncpp::containers::T_replace_all(
                                ncpp::containers::T_replace_all(
                                    ncpp::containers::T_replace_all(
                                        type_name,
                                        ">",
                                        ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + ">" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                    ),
                                    "<",
                                    ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "<" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                ),
                                "::",
                                ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "::" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                            )
                        ).c_str();
                    else
                        os << type_name.c_str();

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_BLACK;

                    os << " {...}";

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }

            };

        };

        template<typename F__>
        struct TF_cout_value_helper_default_case<
            F__, 
            std::enable_if_t<
                (ncpp::utilities::T_is_ostreamable<F_ostream, F__>)
                && (!ncpp::utilities::T_is_ostreamable<F_wostream, F__>),
                i32
            >
        > {

            struct F {

                F__ value;

                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_WHITE_TEXT;

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_fullname<F__>();

                    if(&os == &wcout)
                        os << ncpp::containers::to_wstring(
                            ncpp::containers::T_replace_all(
                                ncpp::containers::T_replace_all(
                                    ncpp::containers::T_replace_all(
                                        type_name,
                                        ">",
                                        ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + ">" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                    ),
                                    "<",
                                    ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "<" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                ),
                                "::",
                                ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "::" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                            )
                        ).c_str();
                    else
                        os << type_name.c_str();

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_BLACK_TEXT;

                    os << L" {...}";

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<typename F__>
        struct TF_cout_value_helper_default_case<
            F__, 
            std::enable_if_t<
                (!ncpp::utilities::T_is_ostreamable<F_ostream, F__>)
                && (!ncpp::utilities::T_is_ostreamable<F_wostream, F__>),
                i32
            >
        > {

            struct F {

                F__ value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_WHITE;

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_fullname<F__>();

                    if(&os == &cout)
                        os << ncpp::containers::to_string(
                            ncpp::containers::T_replace_all(
                                ncpp::containers::T_replace_all(
                                    ncpp::containers::T_replace_all(
                                        type_name,
                                        ">",
                                        ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + ">" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                    ),
                                    "<",
                                    ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "<" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                ),
                                "::",
                                ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "::" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                            )
                        ).c_str();
                    else
                        os << type_name.c_str();

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_BLACK;

                    os << " {...}";

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_WHITE_TEXT;

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_fullname<F__>();

                    if(&os == &wcout)
                        os << ncpp::containers::to_wstring(
                            ncpp::containers::T_replace_all(
                                ncpp::containers::T_replace_all(
                                    ncpp::containers::T_replace_all(
                                        type_name,
                                        ">",
                                        ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + ">" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                    ),
                                    "<",
                                    ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "<" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                                ),
                                "::",
                                ncpp::containers::F_string(NCPP_FOREGROUND_BRIGHT_BLACK) + "::" + ncpp::containers::F_string(NCPP_FOREGROUND_WHITE)
                            )
                        ).c_str();
                    else
                        os << type_name.c_str();

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_BLACK_TEXT;

                    os << L" {...}";

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<typename F__, typename F_placeholder__ = void>
        struct TF_cout_value_helper {

            using F = TF_cout_value_helper_default_case<F__, i32>::F;

        };

        template<typename F__>
        struct TF_cout_value_helper<F__*> {

            struct F {

                F__* value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BLUE;

                    os << "0";

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_MAGNETA;

                    os << "x";

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_BLUE;

                    os << ncpp::containers::T_decimal_to_hex(reinterpret_cast<sz>(input.value)).c_str();

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BLUE_TEXT;

                    os << L"0";

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_MAGNETA_TEXT;

                    os << L"x";

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_BLUE_TEXT;

                    os << ncpp::containers::T_decimal_to_hex<ncpp::containers::F_wstring>(reinterpret_cast<sz>(input.value)).c_str();

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<>
        struct TF_cout_value_helper<b8> {

            struct F {

                b8 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_YELLOW;

                    if(input.value)
                        os << "true";
                    else
                        os << "false";

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT;

                    if(input.value)
                        os << L"true";
                    else
                        os << L"false";

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<>
        struct TF_cout_value_helper<f32> {

            struct F {

                f32 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_MAGNETA;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<f64> {

            struct F {

                f64 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_MAGNETA;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<>
        struct TF_cout_value_helper<i8> {

            struct F {

                i8 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<i16> {

            struct F {

                i16 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

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

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<i64> {

            struct F {

                i64 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<>
        struct TF_cout_value_helper<u8> {

            struct F {

                u8 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<u16> {

            struct F {

                u16 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<u32> {

            struct F {

                u32 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<u64> {

            struct F {

                u64 value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<typename F__>
        struct TF_cout_value_helper<
            F__,
            std::enable_if_t<
                std::is_same_v<F__, sz>
                && !std::is_same_v<F__, u8>
                && !std::is_same_v<F__, u16>
                && !std::is_same_v<F__, u32>
                && !std::is_same_v<F__, u64>,
                void
            >
        > {

            struct F {

                sz value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<typename F__>
        struct TF_cout_value_helper<
            F__,
            std::enable_if_t<
                std::is_same_v<F__, ptrd>
                && !std::is_same_v<F__, i8>
                && !std::is_same_v<F__, i16>
                && !std::is_same_v<F__, i32>
                && !std::is_same_v<F__, i64>,
                void
            >
        > {

            struct F {

                ptrd value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN;

                    os << input.value;

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;

                    os << input.value;

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<>
        struct TF_cout_value_helper<const char*> {

            struct F {

                const char* value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN;

                    os << '"';

                    if(input.value)
                        os << input.value;

                    os << '"';

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT;

                    os << L'"';

                    if(input.value)
                        os << containers::to_wstring(input.value).c_str();

                    os << L'"';

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };
        template<>
        struct TF_cout_value_helper<const wchar_t*> {

            struct F {

                const wchar_t* value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_YELLOW;

                    os << 'L';

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN;

                    os << '"';

                    if(input.value)
                        os << containers::to_string(input.value).c_str();

                    os << '"';

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT;

                    os << L'L';

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT;

                    os << L'"';

                    if(input.value)
                        os << input.value;

                    os << L'"';

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

        template<typename F_char__, typename F_allocator__>
        struct TF_cout_value_helper<containers::TF_string<F_char__, F_allocator__>> {

            struct F {

                containers::TF_string<F_char__, F_allocator__> value;

                friend NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
                    ncpp::F_ostream& os,
                    const F& input
                ) {

                    if(&os == &cout)
                        if constexpr (std::is_same_v<F_char__,wchar_t>)
                            os << NCPP_FOREGROUND_BRIGHT_YELLOW;

                    if constexpr (std::is_same_v<F_char__,wchar_t>)
                        os << 'L';

                    if(&os == &cout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN;

                    os << '"';

                    os << containers::T_to_string<char, F_allocator__>(input.value).c_str();

                    os << '"';

                    if(&os == &cout)
                        os << NCPP_RESET_CONSOLE_COLOR;

                    return os;
                }
                friend NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
                    ncpp::F_wostream& os,
                    const F& input
                ) {

                    if(&os == &wcout)
                        if constexpr (std::is_same_v<F_char__,wchar_t>)
                            os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT;

                    if constexpr (std::is_same_v<F_char__,wchar_t>)
                        os << L'L';

                    if(&os == &wcout)
                        os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT;

                    os << L'"';

                    os << containers::T_to_string<wchar_t, F_allocator__>(input.value).c_str();

                    os << L'"';

                    if(&os == &wcout)
                        os << NCPP_RESET_CONSOLE_COLOR_TEXT;

                    return os;
                }

            };

        };

    }

    template<typename F__>
    using TF_cout_value = typename internal::TF_cout_value_helper<F__>::F;

    template<typename F__>
    NCPP_FORCE_INLINE TF_cout_value<std::remove_reference_t<std::remove_const_t<F__>>> T_cout_value(F__ value){

        return { value };
    }

#pragma endregion

}