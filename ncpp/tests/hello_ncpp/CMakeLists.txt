
# ncpp.tests.hello_ncpp target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.hello_ncpp target
add_executable(ncpp.tests.hello_ncpp
    ${source_files}
)



# ncpp.tests.hello_ncpp target settings
set_target_properties(ncpp.tests.hello_ncpp
    PROPERTIES 
        FOLDER "ncpp/tests"
        PROJECT_LABEL "hello_ncpp"
)
target_link_libraries(ncpp.tests.hello_ncpp
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.hello_ncpp
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.hello_ncpp target dependencies
add_dependencies(ncpp.tests.hello_ncpp 
    ncpp
)