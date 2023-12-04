
#####################################################################################
#   Compiler configs
#####################################################################################
set(NCPP_CXX_STANDARD 20 CACHE STRING "CXX Standard")



#####################################################################################
#   Pre-include global variables
#####################################################################################
NCPP_SetGlobal(NCPP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/SetGlobal)

include(NCPP/PrerequisiteMacros)
include(NCPP/RTTIMacros)

include(NCPP/SIMDCompilerFlags)

include(NCPP/ConfigureCompiler)

include(NCPP/DefaultAllocatorConfig)
include(NCPP/GeneralAllocatorConfig)
include(NCPP/EphemeralAllocatorConfig)



#####################################################################################
#   Options
#####################################################################################
# ncpp mem options
option(NCPP_ENABLE_MEMORY_COUNTING "Enable memory counting" ON)
option(NCPP_ENABLE_ALLOCATOR_NAME "Enable allocator name" ON)

# ncpp pac options
option(NCPP_ENABLE_WEAKLOCK_WARNING "If enabled, weaklock will automatically warn when race condition occurs" ON)
option(NCPP_ENABLE_SCOPED_PROFILER_SAMPLE "If not enabled, scoped profiler samples will be ignored when compiling" ON)

# ncpp log options
set(NCPP_TAB_SIZE 4 CACHE STRING "Tab Size")
set(NCPP_MAX_TAB_COUNT 8 CACHE STRING "Max Tab Count")
option(NCPP_ENABLE_LOG_COLOR "Enable log color" ON)

# ncpp platform specific instruction extension options
option(NCPP_ENABLE_SSE "Enable SSE instructions" ON)
option(NCPP_ENABLE_SSE2 "Enable SSE2 instructions" ON)
option(NCPP_ENABLE_SSE3 "Enable SSE3 instructions" ON)
option(NCPP_ENABLE_SSE4 "Enable SSE4 instructions" ON)
option(NCPP_ENABLE_AVX "Enable AVX instructions" ON)
option(NCPP_ENABLE_AVX2 "Enable AVX2 instructions" ON)
option(NCPP_ENABLE_FMA3 "Enable FMA3 instructions" ON)
option(NCPP_ENABLE_ARM_NEON "Enable ARM Neon instructions" OFF)

# Setup dependent instruction extensions
if(NCPP_ENABLE_AVX2)
    set(NCPP_ENABLE_AVX ON)
endif()
if(NCPP_ENABLE_AVX)
    set(NCPP_ENABLE_SSE4 ON)
endif()

if(NCPP_ENABLE_FMA3)
    set(NCPP_ENABLE_SSE4 ON)
endif()

if(NCPP_ENABLE_SSE4)
    set(NCPP_ENABLE_SSE3 ON)
endif()
if(NCPP_ENABLE_SSE3)
    set(NCPP_ENABLE_SSE2 ON)
endif()
if(NCPP_ENABLE_SSE2)
    set(NCPP_ENABLE_SSE ON)
endif()

# ncpp rtti options
option(NCPP_RTTI_SECURED_NAME "Secure name for RTTI functionalities" OFF)




#####################################################################################
#   Generated files
#####################################################################################
# ncpp target configure file
set(NCPP_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/config.hpp")

configure_file(source/ncpp/.config ${NCPP_CONFIG_HPP_PATH})

# eastl combined header
get_target_property(EASTL_INCLUDE_DIR EASTL INTERFACE_INCLUDE_DIRECTORIES)

set(EASTL_COMBINED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated_files/ncpp/eastl_headers.hpp)

file(GLOB EASTL_HEADERS "${EASTL_INCLUDE_DIR}/EASTL/*.h")

file(WRITE "${EASTL_COMBINED_HEADER_PATH}" "")

foreach(header ${EASTL_HEADERS})
    file(RELATIVE_PATH relpath "${EASTL_INCLUDE_DIR}" "${header}")
    file(APPEND "${EASTL_COMBINED_HEADER_PATH}" "#include <${relpath}>\n")
endforeach()

# eathread combined header
get_target_property(EATHREAD_INCLUDE_DIR EAThread INTERFACE_INCLUDE_DIRECTORIES)

set(EATHREAD_COMBINED_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated_files/ncpp/eathread_headers.hpp)

file(GLOB EATHREAD_HEADERS "${EATHREAD_INCLUDE_DIR}/eathread/*.h")

file(WRITE "${EATHREAD_COMBINED_HEADER_PATH}" "")

foreach(header ${EATHREAD_HEADERS})
    file(RELATIVE_PATH relpath "${EATHREAD_INCLUDE_DIR}" "${header}")
    file(APPEND "${EATHREAD_COMBINED_HEADER_PATH}" "#include <${relpath}>\n")
endforeach()



#####################################################################################
#   ncpp target's files
#####################################################################################
# ncpp target source files
file(GLOB_RECURSE source_files
    "source/*.cpp"
    "source/*.hpp"
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX source FILES ${source_files})

file(GLOB_RECURSE generated_files
    "${CMAKE_CURRENT_BINARY_DIR}/generated_files/*.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/generated_files/*.hpp"
)
source_group(TREE "${CMAKE_CURRENT_BINARY_DIR}/generated_files" PREFIX generated_files FILES ${generated_files})



#####################################################################################
#   Create ncpp target
#####################################################################################
add_library(ncpp STATIC
    ${source_files}
    ${generated_files}
)



#####################################################################################
#   ncpp target settings
#####################################################################################
set_target_properties(ncpp
    PROPERTIES 
        FOLDER "ncpp"
)

target_precompile_headers(ncpp
    PRIVATE
        source/ncpp/prerequisites.hpp
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
    
    target_compile_options(ncpp 
        PUBLIC /Zc:preprocessor
    )
endif()

if(NCPP_ENABLE_SSE)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_SSE})
endif()
if(NCPP_ENABLE_SSE2)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_SSE2})
endif()
if(NCPP_ENABLE_SSE3)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_SSE3})
endif()
if(NCPP_ENABLE_SSE4)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_SSE4})
endif()

if(NCPP_ENABLE_AVX)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_AVX})
endif()
if(NCPP_ENABLE_AVX2)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_AVX2})
endif()

if(NCPP_ENABLE_FMA3)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_FMA3})
endif()

if(NCPP_ENABLE_ARM_NEON)
    target_compile_options(ncpp PUBLIC ${NCPP_COMPILER_FLAG_ARM_NEON})
endif()



#####################################################################################
#   ncpp dependencies
#####################################################################################
add_dependencies(ncpp
    EABase
    EASTL
    EAStdC
    EAThread
    EAAssert
)



#####################################################################################
#   Add subdirectories
#####################################################################################
add_subdirectory(samples)
