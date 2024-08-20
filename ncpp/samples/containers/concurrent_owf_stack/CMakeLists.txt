
# ncpp.samples.containers.concurrent_owf_stack target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.containers.concurrent_owf_stack target
add_executable(ncpp.samples.containers.concurrent_owf_stack
    ${source_files}
)



# ncpp.samples.containers.concurrent_owf_stack target settings
set_target_properties(ncpp.samples.containers.concurrent_owf_stack
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples/containers"
        PROJECT_LABEL "concurrent_owf_stack"
)
target_link_libraries(ncpp.samples.containers.concurrent_owf_stack
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.containers.concurrent_owf_stack
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.containers.concurrent_owf_stack target dependencies
add_dependencies(ncpp.samples.containers.concurrent_owf_stack 
    ncpp
)