#include <ncpp/.hpp>



namespace ncpp {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
	asz total_allocated_memory_g = 0;
	asz usable_allocated_memory_g = 0;
#endif

	void log_memory_stats() {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
		std::cout << "total allocated memory: " << NCPP_TOTAL_ALLOCATED_MEMORY() << " (bytes)" << std::endl;
		std::cout << "usable allocated memory: " << NCPP_USABLE_ALLOCATED_MEMORY() << " (bytes)" << std::endl;
#endif

	}

}