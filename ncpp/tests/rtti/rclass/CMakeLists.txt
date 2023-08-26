
# ncpp.tests.rtti.rclass target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.rtti.rclass target
add_executable(ncpp.tests.rtti.rclass
    ${source_files}
)



# ncpp.tests.rtti.rclass target settings
set_target_properties(ncpp.tests.rtti.rclass
    PROPERTIES 
        FOLDER "ncpp/tests/rtti"
        PROJECT_LABEL "rclass"
)
target_link_libraries(ncpp.tests.rtti.rclass
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.rtti.rclass
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.rtti.rclass target dependencies
add_dependencies(ncpp.tests.rtti.rclass 
    ncpp
)