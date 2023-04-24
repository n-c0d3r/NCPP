#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		tagged_heap tghheap;

		tgh_allocator_t<u8> tghallocator(tghheap, tghheap.create_category());
		tghallocator.apply_native_use();



		containers::native_fv_queue_t<i32> queue;

		std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
		std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
	std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}