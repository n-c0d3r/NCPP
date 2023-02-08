#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	pac::fiber f(

		[](pac::fiber& f) {

			std::cout << "F 1" << std::endl;

			pac::current_thread().owned_fiber().switch_to_this();

			std::cout << "F 2" << std::endl;

			pac::current_thread().owned_fiber().switch_to_this();

		}
	
	);

	std::cout << "T 1" << std::endl;
	f.switch_to_this();
	std::cout << "T 2" << std::endl;
	f.switch_to_this();
	std::cout << "T 3" << std::endl;

	return 0;
}