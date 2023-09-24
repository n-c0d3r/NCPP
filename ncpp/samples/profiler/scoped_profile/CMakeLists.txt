
# ncpp.tests.profiler.scoped_profile target source files
file(GLOB source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group("source" FILES ${source_files})



# Create ncpp.tests.profiler.scoped_profile target
add_executable(ncpp.tests.profiler.scoped_profile
    ${source_files}
)



# ncpp.tests.profiler.scoped_profile target settings
set_target_properties(ncpp.tests.profiler.scoped_profile
    PROPERTIES 
        FOLDER "ncpp/tests/profiler"
        PROJECT_LABEL "scoped_profile"
)
target_link_libraries(ncpp.tests.profiler.scoped_profile
    PUBLIC 
        ncpp
)
target_include_directories(ncpp.tests.profiler.scoped_profile
    PUBLIC 
        ncpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)



# ncpp.tests.profiler.scoped_profile target dependencies
add_dependencies(ncpp.tests.profiler.scoped_profile 
    ncpp
)