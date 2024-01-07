
message(STATUS "<NCPP::MagicMacros> Start generating magic macros")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/Utilities/SetGlobal)



#####################################################################################
#   Setup global variables
#####################################################################################
set(NCPP_MAGIC_MACROS_MAX_ARG_COUNT 3 CACHE STRING "Max argument count of magic macros")



#####################################################################################
#   Setup the generated file
#####################################################################################
set(NCPP_MAGIC_MACROS_FILE "${NCPP_GENERATED_FILES_DIR}/magic_macros.hpp")
file(WRITE ${NCPP_MAGIC_MACROS_FILE} "\n
    #pragma once
    #include <ncpp/prerequisites.hpp>\n
")



message(STATUS "<NCPP::MagicMacros> Generate magic macros done")