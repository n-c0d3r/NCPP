#pragma once

/** @file ncpp/log_colors.hpp
*	@brief Implement log colors.
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

#define NCPP_FOREGROUND_BLACK "\x1B[30m"
#define NCPP_FOREGROUND_RED "\x1B[31m"
#define NCPP_FOREGROUND_GREEN "\x1B[32m"
#define NCPP_FOREGROUND_YELLOW "\x1B[33m"
#define NCPP_FOREGROUND_BLUE "\x1B[34m"
#define NCPP_FOREGROUND_MAGNETA "\x1B[35m"
#define NCPP_FOREGROUND_CYAN "\x1B[36m"
#define NCPP_FOREGROUND_WHITE "\x1B[37m"
#define NCPP_FOREGROUND_BRIGHT_BLACK "\x1B[90m"
#define NCPP_FOREGROUND_BRIGHT_RED "\x1B[91m"
#define NCPP_FOREGROUND_BRIGHT_GREEN "\x1B[92m"
#define NCPP_FOREGROUND_BRIGHT_YELLOW "\x1B[93m"
#define NCPP_FOREGROUND_BRIGHT_BLUE "\x1B[94m"
#define NCPP_FOREGROUND_BRIGHT_MAGNETA "\x1B[95m"
#define NCPP_FOREGROUND_BRIGHT_CYAN "\x1B[96m"
#define NCPP_FOREGROUND_BRIGHT_WHITE "\x1B[97m"

#define NCPP_BACKGROUND_BLACK "\x1B[40m"
#define NCPP_BACKGROUND_RED "\x1B[41m"
#define NCPP_BACKGROUND_GREEN "\x1B[42m"
#define NCPP_BACKGROUND_YELLOW "\x1B[43m"
#define NCPP_BACKGROUND_BLUE "\x1B[44m"
#define NCPP_BACKGROUND_MAGNETA "\x1B[45m"
#define NCPP_BACKGROUND_CYAN "\x1B[46m"
#define NCPP_BACKGROUND_WHITE "\x1B[47m"
#define NCPP_BACKGROUND_BRIGHT_BLACK "\x1B[100m"
#define NCPP_BACKGROUND_BRIGHT_RED "\x1B[101m"
#define NCPP_BACKGROUND_BRIGHT_GREEN "\x1B[102m"
#define NCPP_BACKGROUND_BRIGHT_YELLOW "\x1B[103m"
#define NCPP_BACKGROUND_BRIGHT_BLUE "\x1B[104m"
#define NCPP_BACKGROUND_BRIGHT_MAGNETA "\x1B[105m"
#define NCPP_BACKGROUND_BRIGHT_CYAN "\x1B[106m"
#define NCPP_BACKGROUND_BRIGHT_WHITE "\x1B[107m"

#define NCPP_RESET_CONSOLE_COLOR "\033[0m"

#else

#define NCPP_FOREGROUND_BLACK ""
#define NCPP_FOREGROUND_RED ""
#define NCPP_FOREGROUND_GREEN ""
#define NCPP_FOREGROUND_YELLOW ""
#define NCPP_FOREGROUND_BLUE ""
#define NCPP_FOREGROUND_MAGNETA ""
#define NCPP_FOREGROUND_CYAN ""
#define NCPP_FOREGROUND_WHITE ""
#define NCPP_FOREGROUND_BRIGHT_BLACK ""
#define NCPP_FOREGROUND_BRIGHT_RED ""
#define NCPP_FOREGROUND_BRIGHT_GREEN ""
#define NCPP_FOREGROUND_BRIGHT_YELLOW ""
#define NCPP_FOREGROUND_BRIGHT_BLUE ""
#define NCPP_FOREGROUND_BRIGHT_MAGNETA ""
#define NCPP_FOREGROUND_BRIGHT_CYAN ""
#define NCPP_FOREGROUND_BRIGHT_WHITE ""

#define NCPP_BACKGROUND_BLACK ""
#define NCPP_BACKGROUND_RED ""
#define NCPP_BACKGROUND_GREEN ""
#define NCPP_BACKGROUND_YELLOW ""
#define NCPP_BACKGROUND_BLUE ""
#define NCPP_BACKGROUND_MAGNETA ""
#define NCPP_BACKGROUND_CYAN ""
#define NCPP_BACKGROUND_WHITE ""
#define NCPP_BACKGROUND_BRIGHT_BLACK ""
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

#define NCPP_FOREGROUND_BLACK_TEXT L"\x1B[30m"
#define NCPP_FOREGROUND_RED_TEXT L"\x1B[31m"
#define NCPP_FOREGROUND_GREEN_TEXT L"\x1B[32m"
#define NCPP_FOREGROUND_YELLOW_TEXT L"\x1B[33m"
#define NCPP_FOREGROUND_BLUE_TEXT L"\x1B[34m"
#define NCPP_FOREGROUND_MAGNETA_TEXT L"\x1B[35m"
#define NCPP_FOREGROUND_CYAN_TEXT L"\x1B[36m"
#define NCPP_FOREGROUND_WHITE_TEXT L"\x1B[37m"
#define NCPP_FOREGROUND_BRIGHT_BLACK_TEXT L"\x1B[90m"
#define NCPP_FOREGROUND_BRIGHT_RED_TEXT L"\x1B[91m"
#define NCPP_FOREGROUND_BRIGHT_GREEN_TEXT L"\x1B[92m"
#define NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT L"\x1B[93m"
#define NCPP_FOREGROUND_BRIGHT_BLUE_TEXT L"\x1B[94m"
#define NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT L"\x1B[95m"
#define NCPP_FOREGROUND_BRIGHT_CYAN_TEXT L"\x1B[96m"
#define NCPP_FOREGROUND_BRIGHT_WHITE_TEXT L"\x1B[97m"

#define NCPP_BACKGROUND_BLACK_TEXT L"\x1B[40m"
#define NCPP_BACKGROUND_RED_TEXT L"\x1B[41m"
#define NCPP_BACKGROUND_GREEN_TEXT L"\x1B[42m"
#define NCPP_BACKGROUND_YELLOW_TEXT L"\x1B[43m"
#define NCPP_BACKGROUND_BLUE_TEXT L"\x1B[44m"
#define NCPP_BACKGROUND_MAGNETA_TEXT L"\x1B[45m"
#define NCPP_BACKGROUND_CYAN_TEXT L"\x1B[46m"
#define NCPP_BACKGROUND_WHITE_TEXT L"\x1B[47m"
#define NCPP_BACKGROUND_BRIGHT_BLACK_TEXT L"\x1B[100m"
#define NCPP_BACKGROUND_BRIGHT_RED_TEXT L"\x1B[101m"
#define NCPP_BACKGROUND_BRIGHT_GREEN_TEXT L"\x1B[102m"
#define NCPP_BACKGROUND_BRIGHT_YELLOW_TEXT L"\x1B[103m"
#define NCPP_BACKGROUND_BRIGHT_BLUE_TEXT L"\x1B[104m"
#define NCPP_BACKGROUND_BRIGHT_MAGNETA_TEXT L"\x1B[105m"
#define NCPP_BACKGROUND_BRIGHT_CYAN_TEXT L"\x1B[106m"
#define NCPP_BACKGROUND_BRIGHT_WHITE_TEXT L"\x1B[107m"

#define NCPP_RESET_CONSOLE_COLOR_TEXT L"\033[0m"

#else

#define NCPP_FOREGROUND_BLACK_TEXT L""
#define NCPP_FOREGROUND_RED_TEXT L""
#define NCPP_FOREGROUND_GREEN_TEXT L""
#define NCPP_FOREGROUND_YELLOW_TEXT L""
#define NCPP_FOREGROUND_BLUE_TEXT L""
#define NCPP_FOREGROUND_MAGNETA_TEXT L""
#define NCPP_FOREGROUND_CYAN_TEXT L""
#define NCPP_FOREGROUND_WHITE_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_BLACK_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_RED_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_GREEN_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_BLUE_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_CYAN_TEXT L""
#define NCPP_FOREGROUND_BRIGHT_WHITE_TEXT L""

#define NCPP_BACKGROUND_BLACK_TEXT L""
#define NCPP_BACKGROUND_RED_TEXT L""
#define NCPP_BACKGROUND_GREEN_TEXT L""
#define NCPP_BACKGROUND_YELLOW_TEXT L""
#define NCPP_BACKGROUND_BLUE_TEXT L""
#define NCPP_BACKGROUND_MAGNETA_TEXT L""
#define NCPP_BACKGROUND_CYAN_TEXT L""
#define NCPP_BACKGROUND_WHITE_TEXT L""
#define NCPP_BACKGROUND_BRIGHT_BLACK_TEXT L""
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

#ifdef NCPP_ENABLE_LOG_COLOR
    static constexpr b8 is_enable_log_color_v = true;
#else
    static constexpr b8 is_enable_log_color_v = false;
#endif



    enum class E_log_color;
    NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
        ncpp::F_ostream& os,
        E_log_color input
    );
    NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
        ncpp::F_wostream& os,
        E_log_color input
    );

    enum class E_log_color {

        BLACK = 0x0,
        RED = 0x1,
        GREEN = 0x2,
        YELLOW = 0x3,
        BLUE = 0x4,
        MAGNETA = 0x5,
        CYAN = 0x6,
        WHITE = 0x7,

        BRIGHT = 0x00,
        DARK = 0x10,

        FOREGROUND = 0x000,
        BACKGROUND = 0x100,

        RESET = 0x1000,

        V_FOREGROUND_BLACK = 0x000,
        V_FOREGROUND_RED = 0x001,
        V_FOREGROUND_GREEN = 0x002,
        V_FOREGROUND_YELLOW = 0x003,
        V_FOREGROUND_BLUE = 0x004,
        V_FOREGROUND_MAGNETA = 0x005,
        V_FOREGROUND_CYAN = 0x006,
        V_FOREGROUND_WHITE = 0x007,

        V_FOREGROUND_BRIGHT_BLACK = 0x010,
        V_FOREGROUND_BRIGHT_RED = 0x011,
        V_FOREGROUND_BRIGHT_GREEN = 0x012,
        V_FOREGROUND_BRIGHT_YELLOW = 0x013,
        V_FOREGROUND_BRIGHT_BLUE = 0x014,
        V_FOREGROUND_BRIGHT_MAGNETA = 0x015,
        V_FOREGROUND_BRIGHT_CYAN = 0x016,
        V_FOREGROUND_BRIGHT_WHITE = 0x017,

        V_BACKGROUND_BLACK = 0x100,
        V_BACKGROUND_RED = 0x101,
        V_BACKGROUND_GREEN = 0x102,
        V_BACKGROUND_YELLOW = 0x103,
        V_BACKGROUND_BLUE = 0x104,
        V_BACKGROUND_MAGNETA = 0x105,
        V_BACKGROUND_CYAN = 0x106,
        V_BACKGROUND_WHITE = 0x107,

        V_BACKGROUND_BRIGHT_BLACK = 0x110,
        V_BACKGROUND_BRIGHT_RED = 0x111,
        V_BACKGROUND_BRIGHT_GREEN = 0x112,
        V_BACKGROUND_BRIGHT_YELLOW = 0x113,
        V_BACKGROUND_BRIGHT_BLUE = 0x114,
        V_BACKGROUND_BRIGHT_MAGNETA = 0x115,
        V_BACKGROUND_BRIGHT_CYAN = 0x116,
        V_BACKGROUND_BRIGHT_WHITE = 0x117,

    };



    constexpr E_log_color operator | (E_log_color a, E_log_color b) {

        return (E_log_color)((((u32)a) | ((u32)b)) & 0x11FF);
    }
    constexpr E_log_color operator & (E_log_color a, E_log_color b) {

        return (E_log_color)((((u32)a) & ((u32)b)) & 0x11FF);
    }
    constexpr E_log_color operator ~ (E_log_color a) {

        return (E_log_color)((~((u32)a)) & 0x11FF);
    }



    NCPP_FORCE_INLINE ncpp::F_ostream& operator << (
        ncpp::F_ostream& os,
        E_log_color input
    ){

        if(&os != &cout)
            return os;

        switch (input) {

            case E_log_color::RESET:
                os << NCPP_RESET_CONSOLE_COLOR;
                break;

            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::BLACK):
                os << NCPP_FOREGROUND_BLACK;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::RED):
                os << NCPP_FOREGROUND_RED;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::GREEN):
                os << NCPP_FOREGROUND_GREEN;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::YELLOW):
                os << NCPP_FOREGROUND_YELLOW;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::BLUE):
                os << NCPP_FOREGROUND_BLUE;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::MAGNETA):
                os << NCPP_FOREGROUND_MAGNETA;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::CYAN):
                os << NCPP_FOREGROUND_CYAN;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::WHITE):
                os << NCPP_FOREGROUND_WHITE;
                break;

            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::BLACK):
                os << NCPP_FOREGROUND_BRIGHT_BLACK;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::RED):
                os << NCPP_FOREGROUND_BRIGHT_RED;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::GREEN):
                os << NCPP_FOREGROUND_BRIGHT_GREEN;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::YELLOW):
                os << NCPP_FOREGROUND_BRIGHT_YELLOW;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::BLUE):
                os << NCPP_FOREGROUND_BRIGHT_BLUE;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::MAGNETA):
                os << NCPP_FOREGROUND_BRIGHT_MAGNETA;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::CYAN):
                os << NCPP_FOREGROUND_BRIGHT_CYAN;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::WHITE):
                os << NCPP_FOREGROUND_BRIGHT_WHITE;
                break;

            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::BLACK):
                os << NCPP_BACKGROUND_BLACK;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::RED):
                os << NCPP_BACKGROUND_RED;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::GREEN):
                os << NCPP_BACKGROUND_GREEN;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::YELLOW):
                os << NCPP_BACKGROUND_YELLOW;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::BLUE):
                os << NCPP_BACKGROUND_BLUE;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::MAGNETA):
                os << NCPP_BACKGROUND_MAGNETA;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::CYAN):
                os << NCPP_BACKGROUND_CYAN;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::WHITE):
                os << NCPP_BACKGROUND_WHITE;
                break;

            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::BLACK):
                os << NCPP_BACKGROUND_BRIGHT_BLACK;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::RED):
                os << NCPP_BACKGROUND_BRIGHT_RED;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::GREEN):
                os << NCPP_BACKGROUND_BRIGHT_GREEN;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::YELLOW):
                os << NCPP_BACKGROUND_BRIGHT_YELLOW;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::BLUE):
                os << NCPP_BACKGROUND_BRIGHT_BLUE;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::MAGNETA):
                os << NCPP_BACKGROUND_BRIGHT_MAGNETA;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::CYAN):
                os << NCPP_BACKGROUND_BRIGHT_CYAN;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::WHITE):
                os << NCPP_BACKGROUND_BRIGHT_WHITE;
                break;

        }

        return os;
    }
    NCPP_FORCE_INLINE ncpp::F_wostream& operator << (
        ncpp::F_wostream& os,
        E_log_color input
    ){

        if(&os != &wcout)
            return os;

        switch (input) {

            case E_log_color::RESET:
                os << NCPP_RESET_CONSOLE_COLOR_TEXT;
                break;

            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::BLACK):
                os << NCPP_FOREGROUND_BLACK_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::RED):
                os << NCPP_FOREGROUND_RED_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::GREEN):
                os << NCPP_FOREGROUND_GREEN_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::YELLOW):
                os << NCPP_FOREGROUND_YELLOW_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::BLUE):
                os << NCPP_FOREGROUND_BLUE_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::MAGNETA):
                os << NCPP_FOREGROUND_MAGNETA_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::CYAN):
                os << NCPP_FOREGROUND_CYAN_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::DARK | E_log_color::WHITE):
                os << NCPP_FOREGROUND_WHITE_TEXT;
                break;

            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::BLACK):
                os << NCPP_FOREGROUND_BRIGHT_BLACK_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::RED):
                os << NCPP_FOREGROUND_BRIGHT_RED_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::GREEN):
                os << NCPP_FOREGROUND_BRIGHT_GREEN_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::YELLOW):
                os << NCPP_FOREGROUND_BRIGHT_YELLOW_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::BLUE):
                os << NCPP_FOREGROUND_BRIGHT_BLUE_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::MAGNETA):
                os << NCPP_FOREGROUND_BRIGHT_MAGNETA_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::CYAN):
                os << NCPP_FOREGROUND_BRIGHT_CYAN_TEXT;
                break;
            case (E_log_color::FOREGROUND | E_log_color::BRIGHT | E_log_color::WHITE):
                os << NCPP_FOREGROUND_BRIGHT_WHITE_TEXT;
                break;

            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::BLACK):
                os << NCPP_BACKGROUND_BLACK_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::RED):
                os << NCPP_BACKGROUND_RED_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::GREEN):
                os << NCPP_BACKGROUND_GREEN_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::YELLOW):
                os << NCPP_BACKGROUND_YELLOW_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::BLUE):
                os << NCPP_BACKGROUND_BLUE_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::MAGNETA):
                os << NCPP_BACKGROUND_MAGNETA_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::CYAN):
                os << NCPP_BACKGROUND_CYAN_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::DARK | E_log_color::WHITE):
                os << NCPP_BACKGROUND_WHITE_TEXT;
                break;

            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::BLACK):
                os << NCPP_BACKGROUND_BRIGHT_BLACK_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::RED):
                os << NCPP_BACKGROUND_BRIGHT_RED_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::GREEN):
                os << NCPP_BACKGROUND_BRIGHT_GREEN_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::YELLOW):
                os << NCPP_BACKGROUND_BRIGHT_YELLOW_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::BLUE):
                os << NCPP_BACKGROUND_BRIGHT_BLUE_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::MAGNETA):
                os << NCPP_BACKGROUND_BRIGHT_MAGNETA_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::CYAN):
                os << NCPP_BACKGROUND_BRIGHT_CYAN_TEXT;
                break;
            case (E_log_color::BACKGROUND | E_log_color::BRIGHT | E_log_color::WHITE):
                os << NCPP_BACKGROUND_BRIGHT_WHITE_TEXT;
                break;

        }

        return os;
    }

}

