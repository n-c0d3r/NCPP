
#include <ncpp/.hpp>

using namespace ncpp;

class A {

    NCPP_OBJECT_IMPLEMENT(A);

};

NCPP_ENTRY_POINT(args) {

    int count = 1000;

    {

        NCPP_SCOPED_PROFILER_SAMPLE("EASTL");

        for(i32 i = 0; i < count; ++i) {

            auto a_p1 = eastl::make_unique<A>();
            auto a_p2 = eastl::make_unique<A>();

        }

    }

    {

        NCPP_SCOPED_PROFILER_SAMPLE("NCPP");

        for(i32 i = 0; i < count; ++i) {

            auto a_p1 = TU_object_p<A>()();
            auto a_p2 = TU_object_p<A>()();

        }

    }

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
