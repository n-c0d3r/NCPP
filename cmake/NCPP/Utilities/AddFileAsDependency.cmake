
include(NCPP/Utilities/TempDependenciesDir)



function(NCPP_AddFileAsDependency TARGET FILE)
    NCPP_TempDependenciesDir(${TARGET} TargetTempDependenciesDir)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${TargetTempDependenciesDir}"
        COMMAND ${CMAKE_COMMAND} -E copy
            "${FILE}"
            "${TargetTempDependenciesDir}/"
    )
endfunction()