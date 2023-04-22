#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		stack_heap sheap(NCPP_DEFAULT_STACK_CAPACITY, NCPP_DEFAULT_STACK_COUNT_PER_CHUNK, 40);
		stack_group sgroup;

		stack_allocator_t<u8> sallocator(sheap, sgroup);
		sallocator.allocate(1);

		tagged_heap tghheap;

		tgh_allocator_t<u8> tghallocator(tghheap, tghheap.create_category(NCPP_DEFAULT_TAGGED_HEAP_BLOCK_CAPACITY, 40));
		tghallocator.allocate(1);

		int loopTime = 10000;
		{

			clock_t start = clock();
			for (int i = 0; i < loopTime; ++i) {

				u8* a = sallocator.allocate(5000);

			}
			clock_t end = clock();
			std::cout << end - start << std::endl;

		}
		{

			clock_t start = clock();
			for (int i = 0; i < loopTime; ++i) {

				u8* a = (u8*)malloc(5000);

			}
			clock_t end = clock();
			std::cout << end - start << std::endl;

		}

		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}