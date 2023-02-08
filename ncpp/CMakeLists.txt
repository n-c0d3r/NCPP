
# ncpp utility options
set(NCPP_DEFAULT_ALIGN 16 CACHE STRING "Default Data Align")

# ncpp mem options
option(NCPP_ENABLE_MEMORY_COUNTING "Enable memory counting" ON)
set(NCPP_DEFAULT_TAGGED_HEAP_CAPACITY 2048 CACHE STRING "Default Max Block Count In A Tagged Heap")
set(NCPP_DEFAULT_TAGGED_HEAP_BLOCK_CAPACITY 2097152 CACHE STRING "Default Tagged Heap Block Capacity")
set(NCPP_DEFAULT_ALLOCATOR_TEMPLATE "ncpp::aligned_allocator_t" CACHE STRING "Default Allocator Template")

# ncpp containers options
set(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT 4096 CACHE STRING "Default Handle Map Reserve Count")
set(NCPP_DEFAULT_HANDLE_MAP_VECTOR_RESERVE_COUNT 4 CACHE STRING "Default Handle Map Vector Reserve Count")

# ncpp pac options
option(NCPP_ENABLE_FIBER "Enable fiber" ON)

# ncpp job system options
set(NCPP_DEFAULT_JOB_PRIORITY_COUNT 3 CACHE STRING "Job Priority Count")
set(NCPP_DEFAULT_JOB_QUEUE_CAPACITY 1024 CACHE STRING "Default Job Queue Capacity")
set(NCPP_DEFAULT_COROUTINE_COUNT_PER_WORKER_THREAD 1024 CACHE STRING "Default Coroutine Count Per Worker Thread")



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

file(GLOB pac_source_files
    "source/ncpp/pac/*.cpp"
    "source/ncpp/pac/*.hpp"
)
source_group("source\\ncpp\\pac" FILES ${pac_source_files})

file(GLOB cbjs_source_files
    "source/ncpp/cbjs/*.cpp"
    "source/ncpp/cbjs/*.hpp"
)
source_group("source\\ncpp\\cbjs" FILES ${cbjs_source_files})

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
    ${pac_source_files}
    ${cbjs_source_files}
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

if(MSVC)
    if(NCPP_ENABLE_FIBER)
        # enable fiber-safe tls optimization
        target_compile_options(ncpp 
            PUBLIC /GT
        )
    endif()
endif()



# sub directories
add_subdirectory(samples)