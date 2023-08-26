
# ncpp.tests.rtti.robject target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.rtti.robject target
add_executable(ncpp.tests.rtti.robject
    ${source_files}
)



# ncpp.tests.rtti.robject target settings
set_target_properties(ncpp.tests.rtti.robject
    PROPERTIES 
        FOLDER "ncpp/tests/rtti"
        PROJECT_LABEL "robject"
)
target_link_libraries(ncpp.tests.rtti.robject
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.rtti.robject
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.rtti.robject target dependencies
add_dependencies(ncpp.tests.rtti.robject 
    ncpp
)