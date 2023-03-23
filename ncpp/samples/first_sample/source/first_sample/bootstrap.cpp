#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		stack_heap_t<> heap;

		stack_group group;

		u8* p1 = heap.allocate(group, 512);
		u8* p2 = heap.allocate(group, 512);
		u8* p3 = heap.allocate(group, 512);

		heap.deallocate(group, p1);
		heap.deallocate(group, p2);
		heap.deallocate(group, p3);

		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}