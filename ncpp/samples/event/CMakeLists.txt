
# ncpp.samples.event target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.event target
add_executable(ncpp.samples.event
    ${source_files}
)



# ncpp.samples.event target settings
set_target_properties(ncpp.samples.event
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples"
        PROJECT_LABEL "event"
)
target_link_libraries(ncpp.samples.event
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.event
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.event target dependencies
add_dependencies(ncpp.samples.event 
    ncpp
)