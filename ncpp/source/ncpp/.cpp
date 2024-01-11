#include <ncpp/prerequisites.hpp>
#include <ncpp/log.hpp>

using namespace ncpp;



namespace ncpp::internal {

    void log_warning_failed_connector(){

        std::cout

        << T_cout_lowlight(": ")

        << E_log_color::RESET;

    }
    void log_warning_failed_at(const char* file, int line, const char* condition){

        std::cout

        << E_log_color::V_FOREGROUND_YELLOW
        << "Warning"
        << T_cout_lowlight(", ")

        << E_log_color::RESET
        << T_cout_lowlight("(")
        << condition
        << T_cout_lowlight(")")
        << T_cout_lowlight(" -> ")
        << E_log_color::V_FOREGROUND_BRIGHT_RED << "false"

        << T_cout_lowlight(" from ")

        << T_cout_field_name("file ")

        << T_cout_value(file)

        << T_cout_lowlight(" at ")

        << T_cout_field_name("line ")

        << T_cout_value(line)

        << E_log_color::RESET;

    }

}



namespace ncpp::internal {

    void log_assertion_failed_connector(){

        std::cout

        << T_cout_lowlight(": ")

        << E_log_color::RESET;

    }
    void log_assertion_failed_at(const char* file, int line, const char* condition){

        std::cout

        << E_log_color::V_FOREGROUND_RED
        << "Assertion failed"
        << T_cout_lowlight(", ")

        << E_log_color::RESET
        << T_cout_lowlight("(")
        << condition
        << T_cout_lowlight(")")
        << T_cout_lowlight(" -> ")
        << E_log_color::V_FOREGROUND_BRIGHT_RED << "false"

        << T_cout_lowlight(" from ")

        << T_cout_field_name("file ")

        << T_cout_value(file)

        << T_cout_lowlight(" at ")

        << T_cout_field_name("line ")

        << T_cout_value(line)

        << E_log_color::RESET;

    }

}