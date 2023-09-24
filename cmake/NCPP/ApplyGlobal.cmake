
include("./SetGlobal.cmake")



function(NCPP_ApplyGlobal)

    foreach(ARG ${ARGS})
        SetGlobal(${ARG} ${${ARG}})
    endforeach()
    
endfunction()
