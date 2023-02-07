#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	int a = 5;

	pac::thread t1(
		[&](pac::thread& thread) {

			while (true) {

				std::cout << &pac::current_thread() << std::endl;

			}

		}
	);

	t1.wait();

	return 0;
}