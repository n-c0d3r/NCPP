
#include <ncpp/.hpp>

using namespace ncpp;



NCPP_ENTRY_POINT(args) {

    F_crt_uniform_provider::F_uniform_provider_desc provider_desc;
    provider_desc.payload_size = 16;

    F_crt_uniform_provider provider(provider_desc);

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
