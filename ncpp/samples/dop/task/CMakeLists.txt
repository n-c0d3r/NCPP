
# ncpp.samples.dop.task target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.dop.task target
add_executable(ncpp.samples.dop.task
    ${source_files}
)



# ncpp.samples.dop.task target settings
set_target_properties(ncpp.samples.dop.task
    PROPERTIES 
        FOLDER "ncpp/samples/dop"
        PROJECT_LABEL "task"
)
target_link_libraries(ncpp.samples.dop.task
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.dop.task
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.dop.task target dependencies
add_dependencies(ncpp.samples.dop.task 
    ncpp
)