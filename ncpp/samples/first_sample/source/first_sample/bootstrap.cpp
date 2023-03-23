#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		stack_heap_t<> heap;

		stack_storage storage;

		u8* p1 = heap.allocate(storage, 512);
		u8* p2 = heap.allocate(storage, 512);
		u8* p3 = heap.allocate(storage, 512);

		heap.deallocate(storage, p1);
		heap.deallocate(storage, p2);
		heap.deallocate(storage, p3);

		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}