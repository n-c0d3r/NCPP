
# ncpp.dev_test.memory_management.chunk_allocator target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.dev_test.memory_management.chunk_allocator target
add_executable(ncpp.dev_test.memory_management.chunk_allocator
    ${source_files}
)



# ncpp.dev_test.memory_management.chunk_allocator target settings
set_target_properties(ncpp.dev_test.memory_management.chunk_allocator
    PROPERTIES 
        FOLDER "ncpp/dev_test/memory_management"
        PROJECT_LABEL "chunk_allocator"
)
target_link_libraries(ncpp.dev_test.memory_management.chunk_allocator
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.dev_test.memory_management.chunk_allocator
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.dev_test.memory_management.chunk_allocator target dependencies
add_dependencies(ncpp.dev_test.memory_management.chunk_allocator 
    ncpp
)