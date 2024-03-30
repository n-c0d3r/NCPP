
#include <ncpp/.hpp>

using namespace ncpp;

class A{};

int main() {

    auto a1 = TU<A>()();

    TK<A> a2 = a1.keyed();
    TK_valid<A> a3 = T_apply_validate<F_valid_validate>(a2);


	
	F_default_allocator allocator;

	// non-aligned allocation
	void* p = allocator.allocate(512);

    const F_alloc_debug_info& p_debug_info = get_alloc_debug_info(p);

    NCPP_INFO() << p_debug_info << std::endl;

	log_memory_stats();

	allocator.deallocate(p, 512);

	log_memory_stats();



	// aligned allocation
	void* aligned_p = allocator.allocate(512, 32, 6, 0);

    const F_alloc_debug_info& aligned_p_debug_info = get_alloc_debug_info(aligned_p);

    NCPP_INFO() << aligned_p_debug_info << std::endl;

	log_memory_stats();

	allocator.deallocate(aligned_p, 512);

	log_memory_stats();



	pause_console();

	return 0;
}