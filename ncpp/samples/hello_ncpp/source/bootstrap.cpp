
#include <ncpp/.hpp>

using namespace ncpp;

template<typename F_string__>
requires T_is_same_container<F_string__, F_string>
inline F_string__ T_replace2(
    const F_string__& source,
    TF_no_deduct<TF_view<F_string__>> from,
    TF_no_deduct<TF_view<F_string__>> to
) {

    F_string__ result = source;

    size_t start_pos = result.find(from);

    if(start_pos == std::string::npos)
        return false;

    result.replace(start_pos, from->length(), to);

    return std::move(result);
}

void foo(TF_view<F_string>, TF_view<F_string>){



}

NCPP_ENTRY_POINT(args) {

    const char* abc = "12";
    T_replace2(F_string("123"), abc, abc);

    foo("123", "245");

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
