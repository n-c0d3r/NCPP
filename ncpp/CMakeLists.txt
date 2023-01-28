
# ncpp options
set(NCPP_DEFAULT_ALIGNMENT 16 CACHE STRING "Default Data Alignment")



# ncpp target configure file
configure_file(source/ncpp/.config ${CMAKE_CURRENT_BINARY_DIR}/built_source/ncpp/config.hpp)



# ncpp target source files
file(GLOB source_files
    "Source/ncpp/*.cpp"
    "Source/ncpp/*.hpp"
)
source_group("Source\\ncpp" FILES ${source_files})

file(GLOB dod_sourceFiles
    "Source/ncpp/dod/*.cpp"
    "Source/ncpp/dod/*.hpp"
)
source_group("Source\\ncpp\\dod" FILES ${dod_sourceFiles})

file(GLOB ecs_sourceFiles
    "Source/ncpp/ecs/*.cpp"
    "Source/ncpp/ecs/*.hpp"
)
source_group("Source\\ncpp\\ecs" FILES ${ecs_sourceFiles})

file(GLOB rttr_sourceFiles
    "Source/ncpp/rttr/*.cpp"
    "Source/ncpp/rttr/*.hpp"
)
source_group("Source\\ncpp\\rttr" FILES ${rttr_sourceFiles})



# Create ncpp target
add_library(ncpp STATIC
    ${source_files}
    ${dod_sourceFiles}
    ${ecs_sourceFiles}
    ${rttr_sourceFiles}
)



# ncpp target settings
set_target_properties(ncpp
    PROPERTIES 
        FOLDER "ncpp"
)
target_include_directories(ncpp
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_BINARY_DIR}/built_source
)



# sub directories
add_subdirectory(samples)