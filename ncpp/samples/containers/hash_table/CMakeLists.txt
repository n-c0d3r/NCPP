
# ncpp.samples.containers.hash_table target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.containers.hash_table target
add_executable(ncpp.samples.containers.hash_table
    ${source_files}
)



# ncpp.samples.containers.hash_table target settings
set_target_properties(ncpp.samples.containers.hash_table
    PROPERTIES 
        FOLDER "ncpp/samples/containers"
        PROJECT_LABEL "hash_table"
)
target_link_libraries(ncpp.samples.containers.hash_table
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.containers.hash_table
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.containers.hash_table target dependencies
add_dependencies(ncpp.samples.containers.hash_table 
    ncpp
)