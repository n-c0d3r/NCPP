
include(NCPP/SetGlobal)



set(NCPP_EPHEMERAL_ALLOCATOR_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/ephemeral_allocator_config.hpp")



if(NOT NCPP_EPHEMERAL_ALLOCATOR_NAME OR NOT NCPP_EPHEMERAL_ALLOCATOR_HEADER)
    NCPP_SetGlobal(NCPP_EPHEMERAL_ALLOCATOR_NAME "ncpp::mem::F_default_reference_allocator")
    NCPP_SetGlobal(NCPP_EPHEMERAL_ALLOCATOR_HEADER "${NCPP_SOURCE_DIR}/ncpp/mem/reference_allocator.hpp")
endif()



file(WRITE ${NCPP_EPHEMERAL_ALLOCATOR_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_EPHEMERAL_ALLOCATOR_HEADER}\"

            namespace ncpp {
                namespace mem {
                    using F_ephemeral_allocator = ${NCPP_EPHEMERAL_ALLOCATOR_NAME};
                }
            }
    ")