
# ncpp.samples.memory_management.garbage_collection target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.memory_management.garbage_collection target
add_executable(ncpp.samples.memory_management.garbage_collection
    ${source_files}
)



# ncpp.samples.memory_management.garbage_collection target settings
set_target_properties(ncpp.samples.memory_management.garbage_collection
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples/memory_management"
        PROJECT_LABEL "garbage_collection"
)
target_link_libraries(ncpp.samples.memory_management.garbage_collection
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.memory_management.garbage_collection
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.memory_management.garbage_collection target dependencies
add_dependencies(ncpp.samples.memory_management.garbage_collection 
    ncpp
)