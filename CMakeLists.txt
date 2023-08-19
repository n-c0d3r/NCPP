cmake_minimum_required(VERSION 3.12)



include(cmake/Version.cmake)



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



include(CPack)