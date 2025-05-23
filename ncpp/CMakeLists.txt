
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
include(NCPP/Utilities/SetGlobal)
include(NCPP/Utilities/SIMDCompilerFlags)

include(NCPP/PrerequisiteMacros)
include(NCPP/TemplateTricks)

if(NOT NCPP_LITE)
    include(NCPP/RTTIMacros)
endif()

include(NCPP/ConfigureCompiler)

include(NCPP/DefaultAllocatorConfig)
include(NCPP/GeneralAllocatorConfig)
include(NCPP/EphemeralAllocatorConfig)
include(NCPP/ObjectAllocatorConfig)
include(NCPP/ObjectOptionsConfig)



#####################################################################################
#   Options
#####################################################################################
# ncpp linking options
option(NCPP_DLL "Build NCPP as DLL or not" OFF)

# ncpp object options
option(NCPP_OBJECT_THREAD_SAFE_BY_DEFAULT "If enabled, all objects are marked thread safe" ON)

# ncpp mem options
option(NCPP_ENABLE_MEMORY_COUNTING "Enable memory counting" ON)
option(NCPP_ENABLE_ALLOCATOR_INFO "Enable allocator name" ON)
if(NCPP_ENABLE_MEMORY_COUNTING OR NCPP_ENABLE_ALLOCATOR_INFO)
    NCPP_SetGlobal(NCPP_HAS_ALLOC_DEBUG_INFO ON)
else()
    NCPP_SetGlobal(NCPP_HAS_ALLOC_DEBUG_INFO OFF)
endif()
set(NCPP_DEFAULT_FRAME_BLOCK_PAYLOAD_SIZE 2097152 CACHE STRING "Default frame block size")
set(NCPP_DEFAULT_FRAME_BLOCKS_PER_CHUNK 32 CACHE STRING "Default frame blocks per heap")

# ncpp pac options
option(NCPP_ENABLE_SCOPED_PROFILER_SAMPLE "If not enabled, scoped profiler samples will be ignored when compiling" ON)

# ncpp log options
set(NCPP_TAB_SIZE 4 CACHE STRING "Tab size")
set(NCPP_MAX_TAB_COUNT 8 CACHE STRING "Max tab count")
option(NCPP_ENABLE_LOG_COLOR "Enable log color" ON)

#
option(NCPP_ENABLE_INFO "Enable info" ON)
option(NCPP_ENABLE_ASSERT "Enable assert" ON)
option(NCPP_ENABLE_WARNING "Enable warning" ON)

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
    "source/*.inl"
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
if(${NCPP_DLL})
    set(ncppLinkingMode "SHARED")
else()
    set(ncppLinkingMode "STATIC")
endif()
add_library(ncpp ${ncppLinkingMode}
    ${source_files}
    ${generated_files}
)



#####################################################################################
#   ncpp target settings
#####################################################################################
set_target_properties(ncpp
    PROPERTIES 
        FOLDER "NCoder/ncpp"
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

if(${NCPP_DLL})
    target_compile_definitions(ncpp
        PRIVATE
            -DNCPP_DLL_IMPLEMENTATION
    )
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
