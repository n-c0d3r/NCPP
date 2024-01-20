
#include <ncpp/.hpp>

using namespace ncpp;

class A {



};

NCPP_ENTRY_POINT(args) {

    auto a_up = TU_object_p<A>()();
    TS_object_p<A> a_sp = std::move(a_up);

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

    pause_console();

	return 0;
}
