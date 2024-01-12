
#include <ncpp/.hpp>

using namespace ncpp;



NCPP_ENTRY_POINT(args) {

    F_logger logger(std::cout);

    cout << G_string("Hello ")
        << E_log_color::V_FOREGROUND_BRIGHT_BLUE
        << G_string("NCPP ")
        << E_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
#ifdef NCPP_LITE
        << T_cout_lowlight(" (LITE)")
#endif
        << E_log_color::RESET
        << ncpp::endl;

    pause_console();

	return 0;
}
