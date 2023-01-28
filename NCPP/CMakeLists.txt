
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

file(GLOB ECSSourceFiles
    "Source/NCPP/ECS/*.cpp"
    "Source/NCPP/ECS/*.hpp"
)
source_group("Source\\NCPP\\ECS" FILES ${ECSSourceFiles})

file(GLOB RTTRSourceFiles
    "Source/NCPP/RTTR/*.cpp"
    "Source/NCPP/RTTR/*.hpp"
)
source_group("Source\\NCPP\\RTTR" FILES ${RTTRSourceFiles})



add_library(NCPP STATIC
    ${SourceFiles}
    ${DODSourceFiles}
    ${ECSSourceFiles}
    ${RTTRSourceFiles}
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