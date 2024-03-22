
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
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



    F_crt_uniform_provider_desc crt_uniform_provider_desc;
    crt_uniform_provider_desc.payload_size = 128;

    F_crt_uniform_provider crt_uniform_provider(crt_uniform_provider_desc);



    F_pool_uniform_provider_desc pool_uniform_provider_desc;
    pool_uniform_provider_desc.child_block_size = 16;
    pool_uniform_provider_desc.max_child_block_count_per_pool_block = 16;

    F_pool_uniform_provider pool_uniform_provider(pool_uniform_provider_desc);
    pool_uniform_provider.parent_p = &crt_uniform_provider;



    F_linked_uniform_block_list pool_block_list;

    F_pool_uniform_provider_management_params pool_management_params;
    pool_management_params.upper_list_p = &pool_block_list;

    auto* pool_block_p = (F_pool_uniform_block*)pool_uniform_provider.create_block(&pool_management_params);

    pool_management_params.pool_block_p = pool_block_p;



    F_linked_uniform_provider_desc linked_uniform_provider_desc;
    linked_uniform_provider_desc.payload_size = 16;

    TF_linked_uniform_provider<F_pool_uniform_provider> linked_uniform_provider(linked_uniform_provider_desc);
    linked_uniform_provider.parent_p = &pool_uniform_provider;



    F_linked_uniform_provider_management_params linked_management_params;
    pool_management_params.process_child_management_params(&linked_management_params);

    auto* block_p = (F_linked_uniform_block*)linked_uniform_provider.create_block(&linked_management_params, &pool_management_params);



    log_memory_stats();



	pause_console();

	return 0;
}