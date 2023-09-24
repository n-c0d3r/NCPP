
message(STATUS "<NCPP::CheckDoxygenThemeDependencies> Start checking doxygen theme dependencies")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/GitUtils)



NCPP_GitClone(
    PROJECT_NAME "doxygen-awesome-css"
    GIT_URL "https://github.com/jothepro/doxygen-awesome-css.git"
    GIT_BRANCH "main"
    DIRECTORY "${NCPP_DEPENDENCIES_DIR}"
)



message(STATUS "<NCPP::CheckDoxygenThemeDependencies> Check doxygen theme dependencies done")