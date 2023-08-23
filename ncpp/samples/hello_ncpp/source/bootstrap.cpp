
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	std::cout << eastl::string("Hello NCPP") << std::endl;
	std::cout << sizeof(atomic_int_t<64>) << std::endl;

	system("pause");

	return 0;
}