
# ncpp.samples.pac.thread target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.pac.thread target
add_executable(ncpp.samples.pac.thread
    ${source_files}
)



# ncpp.samples.pac.thread target settings
set_target_properties(ncpp.samples.pac.thread
    PROPERTIES 
        FOLDER "ncpp/samples/pac"
        PROJECT_LABEL "thread"
)
target_link_libraries(ncpp.samples.pac.thread
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.pac.thread
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.pac.thread target dependencies
add_dependencies(ncpp.samples.pac.thread 
    ncpp
)