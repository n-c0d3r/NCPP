
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

    cout << G_string("Hello NCPP ")
        << F_log_color::V_FOREGROUND_BRIGHT_BLUE
        << NCPP_VERSION_STR
        << F_log_color::RESET
        << std::endl;

    ncpp::pause_console();

	return 0;
}
