#include <ncpp/.hpp>

using namespace ncpp;



class A {

	int a[4000];

};



int main() {

	{

		stack_heap sheap(NCPP_DEFAULT_STACK_CAPACITY, NCPP_DEFAULT_STACK_COUNT_PER_CHUNK, 40);
		stack_group sgroup;

		stack_allocator_t<u8> sallocator(sheap, sgroup);
		sallocator.allocate(1);

		
		
		tagged_heap tghheap;

		tgh_allocator_t<u8> tghallocator(tghheap, tghheap.create_category(NCPP_DEFAULT_TAGGED_HEAP_BLOCK_CAPACITY, 40));
		tghallocator.allocate(1);



		pool_heap_t<A> pheap;
		pool_group pgroup;

		pool_allocator_t<A> pallocator(pheap, pgroup);
		pallocator.allocate(1);



		int loopTime = 100000;
		{

			clock_t start = clock();
			for (int i = 0; i < loopTime; ++i) {

				A* a = pallocator.allocate(1);

			}
			clock_t end = clock();
			std::cout << end - start << std::endl;

		}
		{

			clock_t start = clock();
			for (int i = 0; i < loopTime; ++i) {

				A* a = (A*)malloc(sizeof(A));

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