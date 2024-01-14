#include <ncpp/prerequisites.hpp>
#include <ncpp/log.hpp>

using namespace ncpp;



namespace ncpp::internal {

    void log_warning_failed_at(std::ostream& ostream, const char* file_path_p, const char* function_name_p, u32 line, const char* condition){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_YELLOW
        << "| WARNING |"

        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("condition") << T_cout_lowlight(" -> ") << condition

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("file") << T_cout_lowlight(" -> ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("function") << T_cout_lowlight(" -> ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("line") << T_cout_lowlight(" -> ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << std::endl;

    }

}



namespace ncpp::internal {

    void log_assertion_failed_at(std::ostream& ostream, const char* file_path_p, const char* function_name_p, u32 line, const char* condition){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_RED
        << "| ASSERTION FAILED |"

        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("condition") << T_cout_lowlight(" -> ") << condition

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("file") << T_cout_lowlight(" -> ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("function") << T_cout_lowlight(" -> ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("line") << T_cout_lowlight(" -> ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << std::endl;

    }

}



namespace ncpp::internal {

    void log_info_failed_at(std::ostream& ostream, const char* file_path_p, const char* function_name_p, u32 line){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_MAGNETA
        << "| INFO |"

        << std::endl
        << T_cout_lowlight("| ")

        << E_log_color::V_FOREGROUND_GREEN << "default-char"

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("file") << T_cout_lowlight(" -> ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("function") << T_cout_lowlight(" -> ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" |")
        << std::endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("line") << T_cout_lowlight(" -> ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << std::endl;

    }

}



namespace ncpp::internal {

    void log_winfo_failed_at(std::wostream& ostream, const wchar_t* file_path_p, const wchar_t* function_name_p, u32 line){

        ostream

        << E_log_color::V_FOREGROUND_BRIGHT_MAGNETA
        << L"| INFO |"

        << std::endl
        << T_cout_lowlight(L"| ")

        << E_log_color::V_FOREGROUND_YELLOW << "wide-char"

        << T_cout_lowlight(L" |")
        << std::endl
        << T_cout_lowlight(L"| ")

        << T_cout_field_name(L"file") << T_cout_lowlight(L" -> ") << T_cout_value(file_path_p)

        << T_cout_lowlight(L" |")
        << std::endl
        << T_cout_lowlight(L"| ")

        << T_cout_field_name(L"function") << T_cout_lowlight(L" -> ") << T_cout_value(function_name_p)

        << T_cout_lowlight(L" |")
        << std::endl
        << T_cout_lowlight(L"| ")

        << T_cout_field_name(L"line") << T_cout_lowlight(L" -> ") << T_cout_value(line)

        << T_cout_lowlight(L" |")

        << E_log_color::RESET

        << std::endl;

    }

}