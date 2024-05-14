
message(STATUS "<NCPP::CheckDoxygenThemeDependencies> Start checking doxygen theme dependencies")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/Utilities/GitHelper)



if(NOT EXISTS "${NCPP_DEPENDENCIES_DIR}/doxygen-awesome-css")
    NCPP_GitHelper_Clone(
        PROJECT_NAME "doxygen-awesome-css"
        GIT_URL "https://github.com/jothepro/doxygen-awesome-css.git"
        GIT_COMMIT "8cea9a073ecd50a5b2c0958a3df100292d6c7374"
        GIT_BRANCH "main"
        DIRECTORY "${NCPP_DEPENDENCIES_DIR}"
    )
endif()



message(STATUS "<NCPP::CheckDoxygenThemeDependencies> Check doxygen theme dependencies done")