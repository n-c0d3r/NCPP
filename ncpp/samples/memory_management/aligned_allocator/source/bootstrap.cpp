#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		aligned_allocator_t<i32> allocator;

		i32* p = allocator.allocate(5);

		log_memory_stats();

		allocator.deallocate(p);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}