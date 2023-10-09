
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	std::cout << eastl::string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    pause_console();

	return 0;
}
