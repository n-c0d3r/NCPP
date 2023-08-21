#include <ncpp/.hpp>



namespace ncpp {

	void log_memory_stats() {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
		std::cout << "total allocated memory: " << total_allocated_memory() << " (bytes)" << std::endl;
		std::cout << "usable allocated memory: " << usable_allocated_memory() << " (bytes)" << std::endl;
#endif

	}

}