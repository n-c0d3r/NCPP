#include <ncpp/logger.hpp>
#include <ncpp/colorized_log.hpp>



namespace ncpp {

    void F_logger::F_wrapper::log_info(const F_char* file_path_p, const F_char* function_name_p, u32 line){

        logger.ostream()

        << E_log_color::V_FOREGROUND_BRIGHT_MAGNETA
        << "| INFO |"

        << endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("file") << T_cout_lowlight(" -> ") << T_cout_value(file_path_p)

        << T_cout_lowlight(" |")
        << endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("function") << T_cout_lowlight(" -> ") << T_cout_value(function_name_p)

        << T_cout_lowlight(" |")
        << endl
        << T_cout_lowlight("| ")

        << T_cout_field_name("line") << T_cout_lowlight(" -> ") << T_cout_value(line)

        << T_cout_lowlight(" |")

        << E_log_color::RESET

        << endl;

    }

}