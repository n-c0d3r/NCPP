#include <ncpp/.hpp>



namespace ncpp {

	void log_memory_stats() {

#ifdef NCPP_ENABLE_NATIVE_MEMORY_COUNTING
		std::cout << "native allocated memory: " << native_allocated_memory() << " (bytes)" << std::endl;
		std::cout << "native used heap memory: " << native_used_heap_memory() << " (bytes)" << std::endl;
#endif

	}

}