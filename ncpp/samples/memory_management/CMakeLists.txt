
add_subdirectory(basic_allocation)

add_subdirectory(dummy_allocator)
add_subdirectory(chunk_based_allocators)
add_subdirectory(reference_allocator)

if(NOT NCPP_LITE)
    add_subdirectory(garbage_collection)
endif()