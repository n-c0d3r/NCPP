
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
    cout << G_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    ncpp::pause_console();

	return 0;
}
