#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	int a = 5;

	pac::thread thread(
		[&](pac::thread& thread) {

			std::cout << "Hello World" << std::endl;

		}
	);

	thread.wait();

	return 0;
}