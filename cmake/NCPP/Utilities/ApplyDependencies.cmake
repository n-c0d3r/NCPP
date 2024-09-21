
include(NCPP/Utilities/TempDependenciesDir)
include(NCPP/Utilities/AddTargetFileAsDependency)



function(NCPP_ApplyDependencies)
    cmake_parse_arguments(
        PARGS
        "QUIET"
        "TARGET"
        "DEPENDENT_TARGETS"
        ${ARGN}
    )

    if(NOT PARGS_TARGET)
        message(FATAL_ERROR "TARGET argument is required")
    endif()
    if(NOT TARGET ${PARGS_TARGET})
        message(FATAL_ERROR "${PARGS_TARGET} target not found")
    endif()

    NCPP_TempDependenciesDir(${PARGS_TARGET} TargetTempDependenciesDir)
    add_custom_command(TARGET ${PARGS_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "${TargetTempDependenciesDir}"
    )

    if(PARGS_DEPENDENT_TARGETS)
        foreach(DEPENDENT_TARGET ${PARGS_DEPENDENT_TARGETS})
            NCPP_TempDependenciesDir(${DEPENDENT_TARGET} DependentTargetTempDependenciesDir)
            add_custom_command(TARGET ${PARGS_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                    "${DependentTargetTempDependenciesDir}"
            )
            get_target_property(DependentTargetType ${DEPENDENT_TARGET} TYPE)
            if(DependentTargetType STREQUAL "SHARED_LIBRARY")
                NCPP_AddTargetFileAsDependency(${PARGS_TARGET} ${DEPENDENT_TARGET})
            endif()
            add_custom_command(TARGET ${PARGS_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${DependentTargetTempDependenciesDir}"
                    "${TargetTempDependenciesDir}"
            )
        endforeach()

        add_dependencies(${PARGS_TARGET}
            ${PARGS_DEPENDENT_TARGETS}
        )
    endif()

    get_target_property(TargetType ${PARGS_TARGET} TYPE)
    if(TargetType STREQUAL "EXECUTABLE")
        add_custom_command(TARGET ${PARGS_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${TargetTempDependenciesDir}"
                "$<TARGET_FILE_DIR:${PARGS_TARGET}>"
        )
    endif()
endfunction()