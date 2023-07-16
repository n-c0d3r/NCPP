
# ncpp.samples.pac.fiber target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.pac.fiber target
add_executable(ncpp.samples.pac.fiber
    ${source_files}
)



# ncpp.samples.pac.fiber target settings
set_target_properties(ncpp.samples.pac.fiber
    PROPERTIES 
        FOLDER "ncpp/samples/pac"
        PROJECT_LABEL "fiber"
)
target_link_libraries(ncpp.samples.pac.fiber
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.pac.fiber
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.pac.fiber target dependencies
add_dependencies(ncpp.samples.pac.fiber 
    ncpp
)