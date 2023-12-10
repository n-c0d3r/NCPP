
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

    wcout << T_to_view(il) << std::endl;
    wcout << T_to_view(v) << std::endl;
    wcout << T_to_view(a) << std::endl;
    wcout << T_to_view(s) << std::endl;

    pause_console();

	return 0;
}
