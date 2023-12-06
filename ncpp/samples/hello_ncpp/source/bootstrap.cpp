
#include <ncpp/.hpp>



int main() {

    ncpp::cout << ncpp::G_string("Hello ")
        << ncpp::F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << ncpp::G_string("NCPP ")
        << ncpp::F_log_color::V_FOREGROUND_BRIGHT_CYAN
        << NCPP_VERSION_STR
        << ncpp::F_log_color::RESET
        << std::endl;

    ncpp::pause_console();

	return 0;
}
