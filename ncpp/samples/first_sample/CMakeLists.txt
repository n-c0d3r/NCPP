
# first_sample target source files
file(GLOB source_files
    "source/first_sample/*.cpp"
    "source/first_sample/*.hpp"
)
source_group("source\\first_sample" FILES ${source_files})



# Create first_sample target
add_executable(first_sample
    ${source_files}
)



# first_sample target settings
set_target_properties(first_sample
    PROPERTIES 
        FOLDER "ncpp/samples"
)
target_link_libraries(first_sample
    PRIVATE ncpp
)
target_include_directories(first_sample
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# first_sample target dependencies
add_dependencies(first_sample ncpp)