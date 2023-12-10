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
                (ncpp::utilities::T_is_ostreamable_v<F_ostream, F__>)
                || (ncpp::utilities::T_is_ostreamable_v<F_wostream, F__>),
                i32
            >
        > {

            using F = F__;

        };

        template<typename F__>
        struct TF_cout_value_helper_default_case<
            F__, 
            std::enable_if_t<
                (!ncpp::utilities::T_is_ostreamable_v<F_ostream, F__>)
                && (ncpp::utilities::T_is_ostreamable_v<F_wostream, F__>),
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

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_name<F__>();

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
                (ncpp::utilities::T_is_ostreamable_v<F_ostream, F__>)
                && (!ncpp::utilities::T_is_ostreamable_v<F_wostream, F__>),
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

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_name<F__>();

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
                (!ncpp::utilities::T_is_ostreamable_v<F_ostream, F__>)
                && (!ncpp::utilities::T_is_ostreamable_v<F_wostream, F__>),
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

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_name<F__>();

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

                    ncpp::containers::F_string type_name = ncpp::utilities::T_type_name<F__>();

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

        template<typename F__, typename...>
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
                        os << NCPP_FOREGROUND_BRIGHT_RED;

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
                        os << NCPP_FOREGROUND_BRIGHT_RED_TEXT;

                    os << input.value;

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
        template<>
        struct TF_cout_value_helper<sz> {

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
        template<>
        struct TF_cout_value_helper<ptrd> {

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(": ");

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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(": ");

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
template<typename F_item__, class F_allocator__>
ncpp::F_ostream& operator << (
	ncpp::F_ostream& os,
	const ncpp::TF_ostream_input<
		eastl::deque<F_item__, F_allocator__>
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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<char>(i)) << ncpp::T_cout_lowlight(": ");

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

template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_ostream& operator << (ncpp::F_ostream& os, const eastl::deque<F_item__, F_allocator__>& v)
{

	os << ncpp::TF_ostream_input<eastl::deque<F_item__, F_allocator__>> { v, 0 };

	return os;
}



template<typename F_item__, class F_allocator__>
ncpp::F_wostream& operator << (
    ncpp::F_wostream& os,
    const ncpp::TF_ostream_input<
        eastl::deque<F_item__, F_allocator__>
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

        os << ncpp::T_cout_field_name(ncpp::containers::T_to_string<wchar_t>(i)) << ncpp::T_cout_lowlight(L": ");

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

template<typename F_item__, class F_allocator__>
NCPP_FORCE_INLINE ncpp::F_wostream& operator << (ncpp::F_wostream& os, const eastl::deque<F_item__, F_allocator__>& v)
{

    os << ncpp::TF_ostream_input<eastl::deque<F_item__, F_allocator__>> { v, 0 };

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
#pragma endregions