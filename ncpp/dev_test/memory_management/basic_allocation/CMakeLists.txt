
# ncpp.dev_test.memory_management.basic_allocation target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.dev_test.memory_management.basic_allocation target
add_executable(ncpp.dev_test.memory_management.basic_allocation
    ${source_files}
)



# ncpp.dev_test.memory_management.basic_allocation target settings
set_target_properties(ncpp.dev_test.memory_management.basic_allocation
    PROPERTIES 
        FOLDER "ncpp/dev_test/memory_management"
        PROJECT_LABEL "basic_allocation"
)
target_link_libraries(ncpp.dev_test.memory_management.basic_allocation
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.dev_test.memory_management.basic_allocation
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.dev_test.memory_management.basic_allocation target dependencies
add_dependencies(ncpp.dev_test.memory_management.basic_allocation 
    ncpp
)