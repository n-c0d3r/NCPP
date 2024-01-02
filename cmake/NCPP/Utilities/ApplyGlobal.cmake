
include(NCPP/Utilities/SetGlobal)



function(NCPP_ApplyGlobal)

    foreach(ARG ${ARGS})
        NCPP_SetGlobal(${ARG} ${${ARG}})
    endforeach()
    
endfunction()
