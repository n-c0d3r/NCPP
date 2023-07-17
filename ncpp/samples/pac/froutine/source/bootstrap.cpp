#include <ncpp/.hpp>

using namespace ncpp;



pac::native_froutine_t<u32> foo(u32 i = 0) {

	while (true) {

		NCPP_YIELD(i++);
	}

}



int main() {

	{

		auto froutine = foo(0);

		for (u32 i = 0; i < 10; ++i) {

			std::cout << froutine() << std::endl;

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}