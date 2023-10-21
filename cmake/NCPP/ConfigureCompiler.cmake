
set(CMAKE_CXX_STANDARD ${NCPP_CXX_STANDARD})

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-fpermissive)
endif()



add_definitions(-DUNICODE -D_UNICODE)