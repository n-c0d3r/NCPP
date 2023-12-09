
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

    wcout << args << std::endl;
    wcout << TG_vector<i32>() << std::endl;

    TG_array<i32, 3> a = { 1, 2, 3 };
    wcout << a << std::endl;

    auto il = { 1, 2, 3 };
    wcout << il << std::endl;

    pause_console();

	return 0;
}
