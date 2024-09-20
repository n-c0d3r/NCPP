
include(NCPP/Utilities/TempDependenciesDir)



function(NCPP_AddTargetFileAsDependency TARGET DEPENDENT_TARGET)
    NCPP_TempDependenciesDir(${TARGET} TargetTempDependenciesDir)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${TargetTempDependenciesDir}"
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:${DEPENDENT_TARGET}>"
            "${TargetTempDependenciesDir}/"
    )
endfunction()