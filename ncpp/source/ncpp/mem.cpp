#include <ncpp/.hpp>



namespace ncpp {

#ifdef NCPP_ENABLE_MEMORY_COUNTING

	std::atomic_uint64_t memory_usage_g = 0;



	size_t memory_usage() {

		return memory_usage_g.load(std::memory_order_acquire);
	}
	void increase_memory_usage(size_t bytes) {

		memory_usage_g.fetch_add(bytes, std::memory_order_release);

	}
	void decrease_memory_usage(size_t bytes) {

		memory_usage_g.fetch_sub(bytes, std::memory_order_release);

	}
#endif

}