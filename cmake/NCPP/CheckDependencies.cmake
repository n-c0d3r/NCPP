
message(STATUS "<NCPP::Dependencies> Start checking dependencies")



#####################################################################################
#   Setup directory for dependencies to be downloaded into
#####################################################################################
if(NOT EXISTS ${NCPP_DEPENDENCIES_DIR})
    file(MAKE_DIRECTORY ${NCPP_DEPENDENCIES_DIR})
endif()



#####################################################################################
#   This file can be used in script mode so that need to add the CMAKE_MODULE_PATH
#####################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/../")



#####################################################################################
#   Main checkings
#####################################################################################
include(NCPP/CheckEADependencies)
include(NCPP/CheckDoxygenThemeDependencies)



message(STATUS "<NCPP::Dependencies> Check dependencies done")