
include(NCPP/SetGlobal)



set(NCPP_GTEMP_ALLOCATOR_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/gtemp_allocator_config.hpp")



if(NOT NCPP_GTEMP_ALLOCATOR_NAME OR NOT NCPP_GTEMP_ALLOCATOR_HEADER)
    NCPP_SetGlobal(NCPP_GTEMP_ALLOCATOR_NAME "ncpp::mem::F_crt_allocator")
    NCPP_SetGlobal(NCPP_GTEMP_ALLOCATOR_HEADER "${NCPP_SOURCE_DIR}/ncpp/mem/crt_allocator.hpp")
endif()



file(WRITE ${NCPP_GTEMP_ALLOCATOR_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_GTEMP_ALLOCATOR_HEADER}\"

            namespace ncpp {
                namespace mem {
                    using F_gtemp_allocator = ${NCPP_GTEMP_ALLOCATOR_NAME};
                }
            }
    ")