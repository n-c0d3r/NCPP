
# ncpp.samples.memory_management.chunk_based_allocators target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.memory_management.chunk_based_allocators target
add_executable(ncpp.samples.memory_management.chunk_based_allocators
    ${source_files}
)



# ncpp.samples.memory_management.chunk_based_allocators target settings
set_target_properties(ncpp.samples.memory_management.chunk_based_allocators
    PROPERTIES 
        FOLDER "ncpp/samples/memory_management"
        PROJECT_LABEL "chunk_based_allocators"
)
target_link_libraries(ncpp.samples.memory_management.chunk_based_allocators
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.memory_management.chunk_based_allocators
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.memory_management.chunk_based_allocators target dependencies
add_dependencies(ncpp.samples.memory_management.chunk_based_allocators 
    ncpp
)