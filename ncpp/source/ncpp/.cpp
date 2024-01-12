#include <ncpp/prerequisites.hpp>
#include <ncpp/log.hpp>

using namespace ncpp;



namespace ncpp::internal {

    void log_warning_failed_connector(){

    }
    void log_warning_failed_at(std::ostream& ostream, const char* file_path_p, const char* function_name_p, u32 line, const char* condition){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_YELLOW
        << "| WARNING |"

        << T_cout_lowlight(" ")

        << T_cout_field_name("file") << T_cout_lowlight(": ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" | ")

        << T_cout_field_name("function") << T_cout_lowlight(": ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" | ")

        << T_cout_field_name("line") << T_cout_lowlight(": ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << endl;

    }

}



namespace ncpp::internal {

    void log_assertion_failed_connector(){

    }
    void log_assertion_failed_at(std::ostream& ostream, const char* file_path_p, const char* function_name_p, u32 line, const char* condition){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_RED
        << "| ASSERTION FAILED |"

        << T_cout_lowlight(" ")

        << T_cout_field_name("file") << T_cout_lowlight(": ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" | ")

        << T_cout_field_name("function") << T_cout_lowlight(": ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" | ")

        << T_cout_field_name("line") << T_cout_lowlight(": ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << endl;

    }

}