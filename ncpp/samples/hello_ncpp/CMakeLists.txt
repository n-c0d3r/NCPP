
# ncpp.samples.hello_ncpp target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.hello_ncpp target
add_executable(ncpp.samples.hello_ncpp
    ${source_files}
)



# ncpp.samples.hello_ncpp target settings
set_target_properties(ncpp.samples.hello_ncpp
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples"
        PROJECT_LABEL "hello_ncpp"
)
target_link_libraries(ncpp.samples.hello_ncpp
    PUBLIC 
        ncpp
)



# ncpp.samples.hello_ncpp target dependencies
add_dependencies(ncpp.samples.hello_ncpp 
    ncpp
)