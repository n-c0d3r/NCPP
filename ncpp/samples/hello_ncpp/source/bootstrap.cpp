
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
    cout << F_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    cout << to_string(5) << std::endl;

    ncpp::pause_console();

	return 0;
}
