
# ncpp.samples.containers.ring_buffer target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.containers.ring_buffer target
add_executable(ncpp.samples.containers.ring_buffer
    ${source_files}
)



# ncpp.samples.containers.ring_buffer target settings
set_target_properties(ncpp.samples.containers.ring_buffer
    PROPERTIES 
        FOLDER "ncpp/samples/containers"
        PROJECT_LABEL "ring_buffer"
)
target_link_libraries(ncpp.samples.containers.ring_buffer
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.containers.ring_buffer
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.containers.ring_buffer target dependencies
add_dependencies(ncpp.samples.containers.ring_buffer 
    ncpp
)