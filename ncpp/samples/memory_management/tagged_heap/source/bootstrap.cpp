#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		tagged_heap heap;
		tagged_heap::category_id_type cid = heap.create_category();
		tgh_allocator_t<i32> allocator(heap, cid);



		i32* p = allocator.allocate(5);

		log_memory_stats();



		allocator.deallocate(p);

		log_memory_stats();



		heap.reset_blocks(cid);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}