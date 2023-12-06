
include(NCPP/SetGlobal)



set(NCPP_OBJECT_ALLOCATOR_CONFIG_HPP_PATH "${NCPP_GENERATED_FILES_DIR}/object_allocator_config.hpp")



if(NOT NCPP_OBJECT_ALLOCATOR_NAME OR NOT NCPP_OBJECT_ALLOCATOR_HEADER)
    NCPP_SetGlobal(NCPP_OBJECT_ALLOCATOR_NAME "ncpp::mem::F_default_reference_allocator")
    NCPP_SetGlobal(NCPP_OBJECT_ALLOCATOR_HEADER "${NCPP_SOURCE_DIR}/ncpp/mem/reference_allocator.hpp")
endif()



file(WRITE ${NCPP_OBJECT_ALLOCATOR_CONFIG_HPP_PATH} "
            #pragma once

            #include \"${NCPP_OBJECT_ALLOCATOR_HEADER}\"

            namespace ncpp {
                namespace mem {
                    using F_object_allocator = ${NCPP_OBJECT_ALLOCATOR_NAME};
                }
            }
    ")