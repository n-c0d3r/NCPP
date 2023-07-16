
# ncpp.samples.memory_management.native target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.memory_management.native target
add_executable(ncpp.samples.memory_management.native
    ${source_files}
)



# ncpp.samples.memory_management.native target settings
set_target_properties(ncpp.samples.memory_management.native
    PROPERTIES 
        FOLDER "ncpp/samples/memory_management"
        PROJECT_LABEL "native"
)
target_link_libraries(ncpp.samples.memory_management.native
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.memory_management.native
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.memory_management.native target dependencies
add_dependencies(ncpp.samples.memory_management.native 
    ncpp
)