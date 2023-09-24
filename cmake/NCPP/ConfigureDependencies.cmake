
message(STATUS "<NCPP::Dependencies> Start configuring dependencies")



#####################################################################################
#   Main configurating
#####################################################################################
find_package(Doxygen)

include(NCPP/ConfigureEADependencies)



message(STATUS "<NCPP::Dependencies> Configure dependencies done")