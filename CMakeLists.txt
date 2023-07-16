cmake_minimum_required(VERSION 3.12)



set(NCPP_VERSION_MAJOR "0")
set(NCPP_VERSION_MINOR "1")



project(ncpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)



set(NCPP_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")



include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckDependencies.cmake)



add_subdirectory(ncpp)



option(NCPP_GENERATE_DOCS "Generate External And Internal Docs" ON)
if(${NCPP_GENERATE_DOCS})
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenerateDocs.cmake)
endif()



include(InstallRequiredSystemLibraries)
set (CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/ncppConfig.cmake")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${NCPP_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${NCPP_VERSION_MINOR}")
include(CPack)