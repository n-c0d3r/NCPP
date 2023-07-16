
# ncpp.samples.first_sample target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.first_sample target
add_executable(ncpp.samples.first_sample
    ${source_files}
)



# ncpp.samples.first_sample target settings
set_target_properties(ncpp.samples.first_sample
    PROPERTIES 
        FOLDER "ncpp/samples"
        PROJECT_LABEL "first_sample"
)
target_link_libraries(ncpp.samples.first_sample
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.first_sample
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.first_sample target dependencies
add_dependencies(ncpp.samples.first_sample 
    ncpp
)