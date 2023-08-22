
set(NCPP_CXX_STANDARD 20 CACHE STRING "CXX Standard")
set(CMAKE_CXX_STANDARD ${NCPP_CXX_STANDARD})

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-fpermissive)
endif()



# ncpp mem options
option(NCPP_ENABLE_MEMORY_COUNTING "Enable Memory Counting" ON)
set(NCPP_DEFAULT_ALLOCATOR "eastl::allocator" CACHE STRING "Default Allocator")



# ncpp pac options
if(MSVC)
    set(NCPP_SUPPORT_FIBER ON)
else()
    set(NCPP_SUPPORT_FIBER OFF)
endif()

if(${NCPP_SUPPORT_FIBER})
    option(NCPP_ENABLE_FIBER "Enable fiber" ON)
else()
    set(NCPP_ENABLE_FIBER OFF)
endif()

if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
    set(NCPP_SUPPORT_FROUTINE ON)
else()
    set(NCPP_SUPPORT_FROUTINE OFF)
endif()

if(${NCPP_SUPPORT_FROUTINE})
    option(NCPP_ENABLE_FROUTINE "Enable Froutine" ON)
else()
    set(NCPP_ENABLE_FROUTINE OFF)
endif()

set(NCPP_DEFAULT_THREAD_STACK_SIZE 1048576 CACHE STRING "Default Stack Size Of Thread")
set(NCPP_DEFAULT_FIBER_STACK_SIZE 262144 CACHE STRING "Default Stack Size Of Fiber")
option(NCPP_ENABLE_WEAKLOCK_WARNING "Enable Weaklock Warning" ON)

# ncpp log options
set(NCPP_TAB_SIZE 4 CACHE STRING "Tab Size")
set(NCPP_MAX_TAB_COUNT 8 CACHE STRING "Max Tab Count")



# ncpp target configure file
set(NCPP_CONFIG_HPP_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated_files/ncpp/config.hpp)
configure_file(source/ncpp/.config ${NCPP_CONFIG_HPP_PATH})

# eastl combined header
get_target_property(EASTL_INCLUDE_DIR EASTL INTERFACE_INCLUDE_DIRECTORIES)
set(EASTL_COMBINED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated_files/ncpp/eastl_headers.hpp)
file(GLOB_RECURSE EASTL_HEADERS "${EASTL_INCLUDE_DIR}/*.h")
list(FILTER EASTL_HEADERS EXCLUDE REGEX "${EASTL_INCLUDE_DIR}/EASTL/internal/.*")
file(WRITE "${EASTL_COMBINED_HEADER_PATH}" "")
foreach(header ${EASTL_HEADERS})
    file(RELATIVE_PATH relpath "${EASTL_INCLUDE_DIR}" "${header}")
    file(APPEND "${EASTL_COMBINED_HEADER_PATH}" "#include <${relpath}>\n")
endforeach()



set(NCPP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source" PARENT_SCOPE)



# ncpp target source files
file(GLOB_RECURSE source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX source FILES ${source_files})



# Create ncpp target
add_library(ncpp STATIC
    ${source_files}
)



# ncpp target settings
set_target_properties(ncpp
    PROPERTIES 
        FOLDER "ncpp"
)

target_include_directories(ncpp
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_BINARY_DIR}/generated_files
)

target_link_libraries(ncpp
    PUBLIC
        EABase
        EASTL
        EAStdC
        EAThread
        EAAssert
)

if(MSVC)
    if(NCPP_ENABLE_FIBER)
        # enable fiber-safe tls optimization
        target_compile_options(ncpp 
            PUBLIC /GT
        )
    endif()
endif()



add_dependencies(ncpp
    EABase
    EASTL
    EAStdC
    EAThread
    EAAssert
)



# sub directories
add_subdirectory(samples)



