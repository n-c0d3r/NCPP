
message(STATUS "<NCPP::CheckDependencies> Start checking dependencies")



#####################################################################################
#   Setup directory for dependencies to be downloaded into
#####################################################################################
if(NOT EXISTS ${NCPP_DEPENDENCIES_DIR})
    file(MAKE_DIRECTORY ${NCPP_DEPENDENCIES_DIR})
endif()



#####################################################################################
#   Main checkings
#####################################################################################
include(NCPP/CheckEADependencies)
include(NCPP/CheckDoxygenThemeDependencies)



message(STATUS "<NCPP::CheckDependencies> Check dependencies done")