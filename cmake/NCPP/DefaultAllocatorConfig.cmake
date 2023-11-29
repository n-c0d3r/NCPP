
include(NCPP/SetGlobal)



set(NCPP_DEFAULT_ALLOCATOR_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/default_allocator_config.hpp")



if(NOT NCPP_DEFAULT_ALLOCATOR_NAME OR NOT NCPP_DEFAULT_ALLOCATOR_HEADER)
    NCPP_SetGlobal(NCPP_DEFAULT_ALLOCATOR_NAME "ncpp::mem::F_crt_allocator")
    NCPP_SetGlobal(NCPP_DEFAULT_ALLOCATOR_HEADER "${NCPP_SOURCE_DIR}/ncpp/mem/crt_allocator.hpp")
endif()



file(WRITE ${NCPP_DEFAULT_ALLOCATOR_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_DEFAULT_ALLOCATOR_HEADER}\"

            namespace ncpp {
                namespace mem {
                    using F_default_allocator = ${NCPP_DEFAULT_ALLOCATOR_NAME};
                }
            }
    ")