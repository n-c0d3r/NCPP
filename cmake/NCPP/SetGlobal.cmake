
function(NCPP_SetGlobal Name Value)
    unset(${Name} CACHE)
    set(${Name} ${Value} CACHE INTERNAL "")
endfunction()
