
# ncpp options
set(NCPP_DEFAULT_ALIGNMENT 16 CACHE STRING "Default Data Alignment")



# ncpp target configure file
configure_file(source/ncpp/.config ${CMAKE_CURRENT_BINARY_DIR}/built_source/ncpp/config.hpp)



# ncpp target source files
file(GLOB source_files
    "source/ncpp/*.cpp"
    "source/ncpp/*.hpp"
)
source_group("source\\ncpp" FILES ${source_files})

file(GLOB tmp_helper_source_files
    "source/ncpp/tmp_helper/*.cpp"
    "source/ncpp/tmp_helper/*.hpp"
)
source_group("source\\ncpp\\tmp_helper" FILES ${tmp_helper_source_files})

file(GLOB containers_source_files
    "source/ncpp/containers/*.cpp"
    "source/ncpp/containers/*.hpp"
)
source_group("source\\ncpp\\containers" FILES ${containers_source_files})

file(GLOB dod_source_files
    "source/ncpp/dod/*.cpp"
    "source/ncpp/dod/*.hpp"
)
source_group("source\\ncpp\\dod" FILES ${dod_source_files})

file(GLOB job_system_source_files
    "source/ncpp/job_system/*.cpp"
    "source/ncpp/job_system/*.hpp"
)
source_group("source\\ncpp\\job_system" FILES ${job_system_source_files})

file(GLOB ecs_source_files
    "source/ncpp/ecs/*.cpp"
    "source/ncpp/ecs/*.hpp"
)
source_group("source\\ncpp\\ecs" FILES ${ecs_source_files})

file(GLOB rttr_source_files
    "source/ncpp/rttr/*.cpp"
    "source/ncpp/rttr/*.hpp"
)
source_group("source\\ncpp\\rttr" FILES ${rttr_source_files})



# Create ncpp target
add_library(ncpp STATIC
    ${source_files}
    ${tmp_helper_source_files}
    ${containers_source_files}
    ${dod_source_files}
    ${job_system_source_files}
    ${ecs_source_files}
    ${rttr_source_files}
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