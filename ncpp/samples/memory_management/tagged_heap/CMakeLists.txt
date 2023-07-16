
# ncpp.samples.memory_management.tagged_heap target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.memory_management.tagged_heap target
add_executable(ncpp.samples.memory_management.tagged_heap
    ${source_files}
)



# ncpp.samples.memory_management.tagged_heap target settings
set_target_properties(ncpp.samples.memory_management.tagged_heap
    PROPERTIES 
        FOLDER "ncpp/samples/memory_management"
        PROJECT_LABEL "tagged_heap"
)
target_link_libraries(ncpp.samples.memory_management.tagged_heap
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.memory_management.tagged_heap
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.memory_management.tagged_heap target dependencies
add_dependencies(ncpp.samples.memory_management.tagged_heap 
    ncpp
)