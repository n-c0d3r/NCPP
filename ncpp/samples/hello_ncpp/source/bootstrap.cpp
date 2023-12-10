
#include <ncpp/.hpp>

using namespace ncpp;

using A = rtti::F_default_rcontainer;

NCPP_ENTRY_POINT(args) {

    cout << G_string("Hello ")
        << F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << G_string("NCPP ")
        << F_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
        << F_log_color::RESET
        << std::endl;

    TG_initializer_list<i32> il = { 1, 2, 3 };
    TG_vector<i32> v = { 1, 2, 3 };
    TG_array<i32, 3> a = { 1, 2, 3 };
    TG_span<i32> s = { a.data(), 3 };

    wcout << il << std::endl;
    wcout << v << std::endl;
    wcout << a << std::endl;
    wcout << s << std::endl;

    pause_console();

	return 0;
}
