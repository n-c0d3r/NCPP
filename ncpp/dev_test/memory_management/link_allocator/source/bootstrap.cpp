
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	chunk_allocator allocator;
	link_allocator_t<chunk_allocator> link_allocator(allocator);

	log_memory_stats();

	void* p = link_allocator.allocate(12);

	log_memory_stats();

	link_allocator.deallocate(p);

	log_memory_stats();

	link_allocator.clear();

	log_memory_stats();

	system("pause");

	return 0;
}