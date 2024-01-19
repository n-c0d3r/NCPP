
#include <ncpp/.hpp>

using namespace ncpp;

#include <ncpp/.inl>

class A;

TU_object_p<A> foo();

class A {



};

TU_object_p<A> foo() {

    return TU_object_p<A>()();
}

NCPP_ENTRY_POINT(args) {

    for(i32 i = 0; i < 1000; ++i)
        auto a_p2 = foo();

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
