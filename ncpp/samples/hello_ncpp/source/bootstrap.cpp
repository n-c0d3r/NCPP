
#include <ncpp/.hpp>

using namespace ncpp;



NCPP_ENTRY_POINT(args) {

    cout << G_string("Hello ")
        << F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << G_string("NCPP ")
        << F_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
        << F_log_color::RESET
        << std::endl;

    cout << args << std::endl;

    i32* a = NCPP_CREATE(0, i32);

    *a = 4;
    cout << T_cout_value(*a) << std::endl;

    NCPP_DESTROY(0, a);

    pause_console();

	return 0;
}
