
#include <ncpp/.hpp>

using namespace ncpp;

struct A {



};

NCPP_ENTRY_POINT(args) {

    NCPP_INFO()
        << "Hello "
        << E_log_color::V_FOREGROUND_BRIGHT_BLUE
        << "NCPP "
        << E_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
#ifdef NCPP_LITE
        << T_cout_lowlight(" (LITE)")
#endif
        << E_log_color::RESET;

	TS<A> a_p = TS<A>()();
	TS<A_object> v_p = a_p;

    pause_console();

	return 0;
}
