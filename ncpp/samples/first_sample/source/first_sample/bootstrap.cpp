#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		stack_heap_t<typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<u8>, pac::nonelock> sheap(NCPP_DEFAULT_STACK_CAPACITY * 30, NCPP_DEFAULT_STACK_COUNT_PER_CHUNK, NCPP_DEFAULT_STACK_HEAP_MIN_CHUNK_COUNT);
		stack_group sgroup;

		stack_allocator_t<i32, decltype(sheap)> sallocator(sheap, sgroup);

		sallocator.allocate(1);
		sallocator.apply_native_use();



		tagged_heap theap;

		tgh_allocator_t<i32> tallocator(theap, theap.create_category());

		tallocator.allocate(1);
		tallocator.apply_native_use();



		u32 loopCount = 1;

		{

			auto startTime = std::chrono::system_clock::now();
			for (u32 i = 0; i < loopCount; ++i) {

				//std::vector<i32, decltype(tallocator)> v(5000, tallocator);
				containers::native_vector_t<i32> v(5000);
				//sallocator.deallocate(sallocator.allocate(5000));
				//tallocator.deallocate(tallocator.allocate(5000));

			}
			auto endTime = std::chrono::system_clock::now();

			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << std::endl;

		}

		{

			std::allocator<i32> dallocator;
			auto startTime = std::chrono::system_clock::now();
			for (u32 i = 0; i < loopCount; ++i) {

				std::vector<i32> v(5000);
				//dallocator.deallocate(dallocator.allocate(5000), 5000);

			}
			auto endTime = std::chrono::system_clock::now();

			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << std::endl;

		}
		
#ifdef NCPP_ENABLE_NATIVE_MEMORY_COUNTING
		std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
		std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
#endif
		std::cout << std::endl;

	}

#ifdef NCPP_ENABLE_NATIVE_MEMORY_COUNTING
	std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
	std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
#endif
	std::cout << std::endl;

	system("pause");

	return 0;
}