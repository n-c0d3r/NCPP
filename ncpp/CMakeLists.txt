
# ncpp utility options
set(NCPP_DEFAULT_ALIGNMENT 16 CACHE STRING "Default Data Alignment")

# ncpp mem options
option(NCPP_ENABLE_MEMORY_ANALYZING "Enable memory analyzing")

# ncpp containers options
set(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT 1024 CACHE STRING "Default Handle Map Reserve Count")

# ncpp job system options
set(NCPP_COROUTINE_COUNT_PER_WORKER_THREAD 128 CACHE STRING "Coroutine Count Per Worker Thread")



# ncpp target configure file
configure_file(source/ncpp/.config ${CMAKE_CURRENT_BINARY_DIR}/built_source/ncpp/config.hpp)



# ncpp target source files
file(GLOB source_files
    "source/ncpp/*.cpp"
    "source/ncpp/*.hpp"
)
source_group("source\\ncpp" FILES ${source_files})

file(GLOB utilities_source_files
    "source/ncpp/utilities/*.cpp"
    "source/ncpp/utilities/*.hpp"
)
source_group("source\\ncpp\\utilities" FILES ${utilities_source_files})

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

file(GLOB ecs_source_files
    "source/ncpp/ecs/*.cpp"
    "source/ncpp/ecs/*.hpp"
)
source_group("source\\ncpp\\ecs" FILES ${ecs_source_files})



# Create ncpp target
add_library(ncpp STATIC
    ${source_files}
    ${utilities_source_files}
    ${containers_source_files}
    ${dod_source_files}
    ${ecs_source_files}
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