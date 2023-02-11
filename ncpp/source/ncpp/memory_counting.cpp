#include <ncpp/.hpp>



namespace ncpp {

#ifdef NCPP_ENABLE_MEMORY_COUNTING

	std::atomic_uint64_t memory_usage_g = 0;



	inline sz memory_usage() {

		return memory_usage_g.load(std::memory_order_acquire);
	}
	inline void increase_memory_usage(sz bytes) {

		memory_usage_g.fetch_add(bytes, std::memory_order_release);

	}
	inline void decrease_memory_usage(sz bytes) {

		memory_usage_g.fetch_sub(bytes, std::memory_order_release);

	}
#endif

}