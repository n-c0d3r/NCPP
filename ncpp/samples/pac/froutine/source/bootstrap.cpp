#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		auto froutine = (
			[](u32 i = 0) -> pac::native_froutine_t<u32> {

				while (true) {

					NCPP_YIELD(i++);
				}
		
			}
		)(0);

		for (u32 i = 0; i < 10; ++i) {

			std::cout << froutine() << std::endl;

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}