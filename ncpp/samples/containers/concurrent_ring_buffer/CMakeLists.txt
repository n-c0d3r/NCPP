
# ncpp.samples.containers.concurrent_ring_buffer target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.containers.concurrent_ring_buffer target
add_executable(ncpp.samples.containers.concurrent_ring_buffer
    ${source_files}
)



# ncpp.samples.containers.concurrent_ring_buffer target settings
set_target_properties(ncpp.samples.containers.concurrent_ring_buffer
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples/containers"
        PROJECT_LABEL "concurrent_ring_buffer"
)
target_link_libraries(ncpp.samples.containers.concurrent_ring_buffer
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.containers.concurrent_ring_buffer
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.containers.concurrent_ring_buffer target dependencies
add_dependencies(ncpp.samples.containers.concurrent_ring_buffer 
    ncpp
)