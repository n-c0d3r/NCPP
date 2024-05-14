
include(NCPP/Utilities/SetGlobal)



set(NCPP_OBJECT_OPTIONS_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/object_options_config.hpp")



if(NOT NCPP_OBJECT_OPTIONS_NAME OR NOT NCPP_OBJECT_OPTIONS_HEADER)
    NCPP_SetGlobal(NCPP_OBJECT_OPTIONS_NAME "ncpp::F_object_options")
    NCPP_SetGlobal(NCPP_OBJECT_OPTIONS_HEADER "${NCPP_SOURCE_DIR}/ncpp/prerequisites.hpp")
endif()



file(WRITE ${NCPP_OBJECT_OPTIONS_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_OBJECT_OPTIONS_HEADER}\"

            namespace ncpp {
                struct F_object_options;
                using F_default_object_options = ${NCPP_OBJECT_OPTIONS_NAME};
            }
    ")