#include <ncpp/.hpp>

using namespace ncpp;



pac::spinlock lock_g;



void safe_hello_world() {

	lock_g.lock();

	std::cout << pac::current_thread_index() << " Hello World" << std::endl;

	lock_g.unlock();

}



int main() {

	{

		pac::thread t2(
			[]() {

				while (true) {

					safe_hello_world();

				}

			}
		);

		while (true) {

			safe_hello_world();

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}