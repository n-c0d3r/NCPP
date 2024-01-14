
#include <ncpp/.hpp>

using namespace ncpp;

template<typename F__, sz index__ = 0>
struct TL_i32 {

    static constexpr b8 is_valid = std::is_same_v<F__, i32>;

};

NCPP_ENTRY_POINT(args) {

    NCPP_INFO() << T_type_fullname<TF_template_targ_list<i32, b8, f32>::template TF_find_index<TL_i32>>();

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
