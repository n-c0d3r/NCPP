
# ncpp.samples.pac.spinlock target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.pac.spinlock target
add_executable(ncpp.samples.pac.spinlock
    ${source_files}
)



# ncpp.samples.pac.spinlock target settings
set_target_properties(ncpp.samples.pac.spinlock
    PROPERTIES 
        FOLDER "ncpp/samples/pac"
        PROJECT_LABEL "spinlock"
)
target_link_libraries(ncpp.samples.pac.spinlock
    PRIVATE ncpp
)
target_include_directories(ncpp.samples.pac.spinlock
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.pac.spinlock target dependencies
add_dependencies(ncpp.samples.pac.spinlock 
    ncpp
)