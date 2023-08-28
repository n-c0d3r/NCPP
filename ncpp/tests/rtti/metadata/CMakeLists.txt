
# ncpp.tests.rtti.metadata target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.rtti.metadata target
add_executable(ncpp.tests.rtti.metadata
    ${source_files}
)



# ncpp.tests.rtti.metadata target settings
set_target_properties(ncpp.tests.rtti.metadata
    PROPERTIES 
        FOLDER "ncpp/tests/rtti"
        PROJECT_LABEL "metadata"
)
target_link_libraries(ncpp.tests.rtti.metadata
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.rtti.metadata
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.rtti.metadata target dependencies
add_dependencies(ncpp.tests.rtti.metadata 
    ncpp
)