
#include <ncpp/.hpp>

using namespace ncpp;

template<typename F__>
struct TL_i32 {

    static constexpr b8 is_valid = std::is_same_v<F__, i32>;// || std::is_same_v<F__, b8>;

};

NCPP_ENTRY_POINT(args) {

    using F = TF_template_targ_tree<i32, TF_template_targ_tree<b8>>;
    using F3 = TF_template_targ_tree<i32, F>;
    using F2 = F3::TF_filter<TL_i32>;
    cout << T_type_fullname<F2>() << std::endl;

    cout << G_string("Hello ")
        << F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << G_string("NCPP ")
        << F_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
#ifdef NCPP_LITE
        << T_cout_lowlight(" (LITE)")
#endif
        << F_log_color::RESET
        << std::endl;

    pause_console();

	return 0;
}
