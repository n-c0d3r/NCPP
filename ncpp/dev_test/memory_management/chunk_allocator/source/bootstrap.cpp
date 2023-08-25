
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	chunk_allocator allocator;

	log_memory_stats();

	void* p = allocator.allocate(12);

	log_memory_stats();

	allocator.deallocate(p);

	log_memory_stats();

	allocator.clear();

	log_memory_stats();

	system("pause");

	return 0;
}