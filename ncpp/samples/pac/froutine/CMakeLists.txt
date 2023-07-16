
# ncpp.samples.pac.froutine target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.pac.froutine target
add_executable(ncpp.samples.pac.froutine
    ${source_files}
)



# ncpp.samples.pac.froutine target settings
set_target_properties(ncpp.samples.pac.froutine
    PROPERTIES 
        FOLDER "ncpp/samples/pac"
        PROJECT_LABEL "froutine"
)
target_link_libraries(ncpp.samples.pac.froutine
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.pac.froutine
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.pac.froutine target dependencies
add_dependencies(ncpp.samples.pac.froutine 
    ncpp
)