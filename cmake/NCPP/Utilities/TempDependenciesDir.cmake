
function(NCPP_TempDependenciesDir TARGET OUT_VAR)
    set(${OUT_VAR} "$<TARGET_FILE_DIR:${TARGET}>/___temp_dependencies___" PARENT_SCOPE)
endfunction()