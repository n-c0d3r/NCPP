
# ncpp.samples.memory_management.frame_allocator target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.memory_management.frame_allocator target
add_executable(ncpp.samples.memory_management.frame_allocator
    ${source_files}
)



# ncpp.samples.memory_management.frame_allocator target settings
set_target_properties(ncpp.samples.memory_management.frame_allocator
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples/memory_management"
        PROJECT_LABEL "frame_allocator"
)
target_link_libraries(ncpp.samples.memory_management.frame_allocator
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.memory_management.frame_allocator
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.memory_management.frame_allocator target dependencies
add_dependencies(ncpp.samples.memory_management.frame_allocator 
    ncpp
)