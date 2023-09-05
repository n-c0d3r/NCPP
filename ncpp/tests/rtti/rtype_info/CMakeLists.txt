
# ncpp.tests.rtti.rtype_info target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.rtti.rtype_info target
add_executable(ncpp.tests.rtti.rtype_info
    ${source_files}
)



# ncpp.tests.rtti.rtype_info target settings
set_target_properties(ncpp.tests.rtti.rtype_info
    PROPERTIES 
        FOLDER "ncpp/tests/rtti"
        PROJECT_LABEL "rtype_info"
)
target_link_libraries(ncpp.tests.rtti.rtype_info
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.rtti.rtype_info
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.rtti.rtype_info target dependencies
add_dependencies(ncpp.tests.rtti.rtype_info 
    ncpp
)