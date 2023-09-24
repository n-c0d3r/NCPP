
# ncpp.samples.rtti.robject target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.rtti.robject target
add_executable(ncpp.samples.rtti.robject
    ${source_files}
)



# ncpp.samples.rtti.robject target settings
set_target_properties(ncpp.samples.rtti.robject
    PROPERTIES 
        FOLDER "ncpp/samples/rtti"
        PROJECT_LABEL "robject"
)
target_link_libraries(ncpp.samples.rtti.robject
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.rtti.robject
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.rtti.robject target dependencies
add_dependencies(ncpp.samples.rtti.robject 
    ncpp
)