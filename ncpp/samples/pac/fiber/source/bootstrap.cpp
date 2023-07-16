#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		pac::fiber f1(
			[](const pac::fiber& f) {

				std::cout << "2" << std::endl;

				pac::main_thread().owned_fiber().resume();

				std::cout << "4" << std::endl;

				pac::main_thread().owned_fiber().resume();

			}
		);

		std::cout << "1" << std::endl;

		f1.resume();

		std::cout << "3" << std::endl;

		f1.resume();

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}