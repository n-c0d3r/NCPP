
add_subdirectory(basic_allocation)

add_subdirectory(dummy_allocator)
add_subdirectory(chunk_allocator)
add_subdirectory(reference_allocator)

if(NOT NCPP_LITE)
    add_subdirectory(gob_allocator)
    add_subdirectory(garbage_collection)
endif()