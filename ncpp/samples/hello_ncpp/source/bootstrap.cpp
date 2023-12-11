
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

//    TG_queue<i32> q;
//    q.push(1);
//    q.push(2);
//    q.push(3);

//    wcout << q << std::endl;
    wcout << TG_vector<TG_vector<i32>>({TG_vector<i32>{1,2,3}}) << std::endl;

    pause_console();

	return 0;
}
