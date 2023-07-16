#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		stack_heap sheap;
		stack_group gr;
		stack_allocator_t<i32> sallocator(sheap, gr);



		tagged_heap theap;
		tagged_heap::category_id_type cid = theap.create_category();
		tgh_allocator_t<i32> tallocator(theap, cid);



		sallocator.apply_native_use();

		containers::native_vector_t<i32> v1 = { 1, 2, 3 };

		log_memory_stats();



		tallocator.apply_native_use();

		containers::native_vector_t<i32> v2 = { 1, 2, 3 };

		log_memory_stats();



		// will automatically use current native allocator (tagged heap allocator)
		native_allocator_t<i32> nallocator;

		i32* ap = nallocator.allocate(5);

		nallocator.deallocate(ap);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}