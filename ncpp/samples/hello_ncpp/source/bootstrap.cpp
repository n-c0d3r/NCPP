
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

    TG_queue<i32> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << q << std::endl;

    pause_console();

	return 0;
}
