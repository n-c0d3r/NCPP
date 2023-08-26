
# ncpp.tests.memory_management.dummy_allocator target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.memory_management.dummy_allocator target
add_executable(ncpp.tests.memory_management.dummy_allocator
    ${source_files}
)



# ncpp.tests.memory_management.dummy_allocator target settings
set_target_properties(ncpp.tests.memory_management.dummy_allocator
    PROPERTIES 
        FOLDER "ncpp/tests/memory_management"
        PROJECT_LABEL "dummy_allocator"
)
target_link_libraries(ncpp.tests.memory_management.dummy_allocator
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.memory_management.dummy_allocator
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.memory_management.dummy_allocator target dependencies
add_dependencies(ncpp.tests.memory_management.dummy_allocator 
    ncpp
)