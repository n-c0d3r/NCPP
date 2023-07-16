#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		pac::thread t2([]() {

			for (i32 i = 0; i < 10000; ++i)
				std::cout << pac::current_thread_index() << std::endl;

		});

		while (!t2.is_done()) {

			std::cout << pac::current_thread_index() << std::endl;

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}