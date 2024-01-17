
#include <ncpp/.hpp>

using namespace ncpp;



class A {

    NCPP_OBJECT_IMPLEMENT(A);

    i32 i1 = 1;
    i32 i2 = 2;

};
class B : public A {

    NCPP_OBJECT_IMPLEMENT(B);
    NCPP_OBJECT_THREAD_SAFE;

    i32 i3 = 3;

};

NCPP_ENTRY_POINT(args) {

    TU_object_p<A> a_up;

    a_up.T_create_object();

    TW_object_p<A> a_wp = a_up;

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
