
#include <ncpp/.hpp>

using namespace ncpp;



NCPP_ENTRY_POINT(args) {

    {

        log_memory_stats();

        V_string s = "123";
        V_string s2 = s + G_string("abc");

//        cout << s2 << std::endl;

        log_memory_stats();

    }

    log_memory_stats();

    cout << G_string("Hello ")
        << F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << G_string("NCPP ")
        << F_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
        << F_log_color::RESET
        << std::endl;

    pause_console();

	return 0;
}
