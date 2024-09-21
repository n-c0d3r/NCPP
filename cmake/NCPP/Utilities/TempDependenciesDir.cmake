
function(NCPP_TempDependenciesDir TARGET OUT_VAR)
    get_target_property(BinaryDir ${TARGET} BINARY_DIR)
    set(${OUT_VAR} "${BinaryDir}/___temp_dependencies___/$<CONFIG>" PARENT_SCOPE)
endfunction()