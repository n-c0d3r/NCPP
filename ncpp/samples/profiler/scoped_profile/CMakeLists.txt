
# ncpp.samples.profiler.scoped_profile target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.samples.profiler.scoped_profile target
add_executable(ncpp.samples.profiler.scoped_profile
    ${source_files}
)



# ncpp.samples.profiler.scoped_profile target settings
set_target_properties(ncpp.samples.profiler.scoped_profile
    PROPERTIES 
        FOLDER "NCoder/ncpp/samples/profiler"
        PROJECT_LABEL "scoped_profile"
)
target_link_libraries(ncpp.samples.profiler.scoped_profile
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.samples.profiler.scoped_profile
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.samples.profiler.scoped_profile target dependencies
add_dependencies(ncpp.samples.profiler.scoped_profile 
    ncpp
)