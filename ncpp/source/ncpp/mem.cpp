#include <ncpp/.hpp>



namespace ncpp {

	void log_memory_stats() {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
		std::cout << "total allocated memory: " << NCPP_TOTAL_ALLOCATED_MEMORY() << " (bytes)" << std::endl;
		std::cout << "usable allocated memory: " << NCPP_USABLE_ALLOCATED_MEMORY() << " (bytes)" << std::endl;
#endif

	}

}