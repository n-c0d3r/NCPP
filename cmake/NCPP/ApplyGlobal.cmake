
include(NCPP/SetGlobal)



function(NCPP_ApplyGlobal)

    foreach(ARG ${ARGS})
        SetGlobal(${ARG} ${${ARG}})
    endforeach()
    
endfunction()
