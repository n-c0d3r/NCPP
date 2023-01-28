
file(GLOB SourceFiles
    "Source/FirstSample/*.cpp"
    "Source/FirstSample/*.hpp"
)
source_group("Source\\FirstSample" FILES ${SourceFiles})



add_executable(NCPP.Samples.FirstSample
    ${SourceFiles}
)



set_target_properties(NCPP.Samples.FirstSample
    PROPERTIES 
        FOLDER "NCPP/Samples"
)

target_link_libraries(NCPP.Samples.FirstSample
    PRIVATE NCPP
)
target_include_directories(NCPP.Samples.FirstSample
    PUBLIC 
        NCPP
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)



add_dependencies(NCPP.Samples.FirstSample NCPP)