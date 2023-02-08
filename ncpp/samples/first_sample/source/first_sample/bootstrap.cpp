#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		tagged_heap_t heap;

		auto cid1 = heap.create_category();

		auto& category = heap.category(cid1);



		for (u32 i = 0; i < 7000; ++i)
			heap.allocate(cid1, 1024, NCPP_DEFAULT_ALIGN);

		std::cout << "block count: " << category.block_count() << " (bytes)" << std::endl;
		std::cout << "current block usage: " << category.current_block().usage() << " (bytes)" << std::endl;
		std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl << std::endl;



		category.reset_blocks();



		for (u32 i = 0; i < 500; ++i)
			heap.allocate(cid1, 1024, NCPP_DEFAULT_ALIGN);

		std::cout << "block count: " << category.block_count() << " (bytes)" << std::endl;
		std::cout << "current block usage: " << category.current_block().usage() << " (bytes)" << std::endl;
		std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl;

	return 0;
}