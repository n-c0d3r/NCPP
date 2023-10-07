
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	mem::F_default_allocator allocator;



	// non-aligned allocation
	void* p = allocator.allocate(512);

	mem::log_memory_stats();

	allocator.deallocate(p, 512);

	mem::log_memory_stats();



	// aligned allocation
	void* aligned_p = allocator.allocate(512, 32, 0, 0);

	mem::log_memory_stats();

	allocator.deallocate(aligned_p, 512);

	mem::log_memory_stats();



	pause();

	return 0;
}