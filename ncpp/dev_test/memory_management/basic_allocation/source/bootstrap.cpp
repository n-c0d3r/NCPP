
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	eastl::allocator allocator;



	// non-aligned allocation
	void* p = allocator.allocate(512);

	log_memory_stats();

	allocator.deallocate(p, 512);

	log_memory_stats();



	// aligned allocation
	void* aligned_p = allocator.allocate(512, 32, 0, 0);

	log_memory_stats();

	allocator.deallocate(aligned_p, 512);

	log_memory_stats();



	system("pause");

	return 0;
}