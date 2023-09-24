
message(STATUS "<NCPP::Dependencies> Start checking dependencies")



#####################################################################################
#   This file can be used in script mode so that need to add the CMAKE_MODULE_PATH
#####################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/../")



#####################################################################################
#   Main checkings
#####################################################################################
include(NCPP/CheckEADependencies)



message(STATUS "<NCPP::Dependencies> Check dependencies done")