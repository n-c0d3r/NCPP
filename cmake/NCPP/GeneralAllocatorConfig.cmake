
include(NCPP/SetGlobal)



set(NCPP_GENERAL_ALLOCATOR_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/general_allocator_config.hpp")



if(NOT NCPP_GENERAL_ALLOCATOR_NAME OR NOT NCPP_GENERAL_ALLOCATOR_HEADER)
    NCPP_SetGlobal(NCPP_GENERAL_ALLOCATOR_NAME "ncpp::mem::F_default_reference_allocator")
    NCPP_SetGlobal(NCPP_GENERAL_ALLOCATOR_HEADER "${NCPP_SOURCE_DIR}/ncpp/mem/reference_allocator.hpp")
endif()



file(WRITE ${NCPP_GENERAL_ALLOCATOR_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_GENERAL_ALLOCATOR_HEADER}\"

            namespace ncpp {
                namespace mem {
                    using F_general_allocator = ${NCPP_GENERAL_ALLOCATOR_NAME};
                }
            }
    ")