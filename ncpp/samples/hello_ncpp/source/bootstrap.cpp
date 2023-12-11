
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

    i32* a_p = NCPP_CREATE(0, i32);

    const F_alloc_debug_info& debug_info = get_alloc_debug_info(a_p);

    cout << debug_info << std::endl;

    NCPP_DESTROY(0, a_p);

    pause_console();

	return 0;
}
