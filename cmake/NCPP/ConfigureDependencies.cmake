
message(STATUS "<NCPP::ConfigureDependencies> Start configuring dependencies")



#####################################################################################
#   Main configurating
#####################################################################################
find_package(Doxygen)

include(NCPP/ConfigureEADependencies)



message(STATUS "<NCPP::ConfigureDependencies> Configure dependencies done")