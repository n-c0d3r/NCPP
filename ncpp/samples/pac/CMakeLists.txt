
if(NCPP_ENABLE_FROUTINE)
    add_subdirectory(froutine)
endif()

if(NCPP_ENABLE_FIBER)
    add_subdirectory(fiber)
endif()

add_subdirectory(spinlock)
add_subdirectory(thread)