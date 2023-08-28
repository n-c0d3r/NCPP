
message(STATUS "<NCPP::Dependencies> Start checking dependencies")

# setup ncpp cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}")



include(CheckEADependencies)

message(STATUS "<NCPP::Dependencies> Check dependencies done")