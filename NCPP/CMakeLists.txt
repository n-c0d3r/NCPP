
configure_file(Source/NCPP/.Config ${CMAKE_CURRENT_BINARY_DIR}/BuiltSource/NCPP/Config.hpp)



file(GLOB SourceFiles
    "Source/NCPP/*.cpp"
    "Source/NCPP/*.hpp"
)
source_group("Source\\NCPP" FILES ${SourceFiles})

file(GLOB DODSourceFiles
    "Source/NCPP/DOD/*.cpp"
    "Source/NCPP/DOD/*.hpp"
)
source_group("Source\\NCPP\\DOD" FILES ${DODSourceFiles})



add_library(NCPP STATIC
    ${SourceFiles}
    ${DODSourceFiles}
)



set_target_properties(NCPP
    PROPERTIES 
        FOLDER "NCPP"
)
target_include_directories(NCPP
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_BINARY_DIR}/BuiltSource
)



add_subdirectory(Samples)