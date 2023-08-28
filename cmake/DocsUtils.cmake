
set(DOXYGEN_THEME_AWESOME_CSS_DIR "${CMAKE_CURRENT_LIST_DIR}/../submodules/doxygen-awesome-css")
set(DOXYGEN_THEME_FLAT_DESIGN_DIR "${CMAKE_CURRENT_LIST_DIR}/../submodules/doxygen_theme_flat_design")



function(DocsUtils_CreateTarget)
    cmake_parse_arguments(
        PARGS
        ""
        "NAME;BRIEF;TARGET_NAME;TARGET_FOLDER;TARGET_LABEL;OUTPUT_DIR;CWD;INTERNAL_DOCS;MAIN_PAGE"
        "INPUT_DIRS;STYLE_DIRS"
        ${ARGN}
    )

    if(DOXYGEN_FOUND)

        SET(DOXYGEN_OUTPUT_DIRECTORY ${PARGS_OUTPUT_DIR})

        FILE(RELATIVE_PATH CWD_DIR_TO_DOXYGEN_THEME_DIR ${PARGS_CWD} ${DOXYGEN_THEME_AWESOME_CSS_DIR})



        set(STYLE_FILES "")
        if(PARGS_STYLE_DIRS)
            foreach(style_dir ${PARGS_STYLE_DIRS})
                file(GLOB_RECURSE style_files "${style_dir}/*.css")
                set(STYLE_FILES "${STYLE_FILES};${style_files}")
            endforeach()
        endif()        



        SET(DOXYGEN_PROJECT_NAME ${PARGS_NAME})
        SET(DOXYGEN_PROJECT_BRIEF ${PARGS_BRIEF})
        SET(DOXYGEN_JAVADOC_AUTOBRIEF YES)

        if(PARGS_INTERNAL_DOCS)
            SET(DOXYGEN_EXTRACT_PRIVATE YES)
        else()
            SET(DOXYGEN_EXTRACT_PRIVATE NO)
        endif()

        SET(DOXYGEN_EXTRACT_STATIC YES)
        SET(DOXYGEN_EXTRACT_LOCAL_METHODS YES)

        if(PARGS_INTERNAL_DOCS)
            SET(DOXYGEN_INTERNAL_DOCS YES)
            SET(DOXYGEN_ENABLED_SECTIONS "INTERNAL")
        else()
            SET(DOXYGEN_INTERNAL_DOCS NO)
            SET(DOXYGEN_ENABLED_SECTIONS "EXTERNAL")
        endif()

        SET(DOXYGEN_RECURSIVE YES)

        SET(DOXYGEN_GENERATE_TREEVIEW YES)

        SET(DOXYGEN_MACRO_EXPANSION YES)

        if(PARGS_MAIN_PAGE)
            SET(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${PARGS_MAIN_PAGE})
        endif()

        SET(DOXYGEN_ENABLE_PREPROCESSING  NO)
        


        SET(DOXYGEN_HTML_EXTRA_STYLESHEET "${DOXYGEN_HTML_EXTRA_STYLESHEET};${CWD_DIR_TO_DOXYGEN_THEME_DIR}/doxygen-awesome.css;${CWD_DIR_TO_DOXYGEN_THEME_DIR}/doxygen-awesome-sidebar-only.css")
        # SET(DOXYGEN_HTML_EXTRA_STYLESHEET "${DOXYGEN_HTML_EXTRA_STYLESHEET};${CWD_DIR_TO_DOXYGEN_THEME_DIR}/src/doxygen-style.css")



        SET(DOXYGEN_HTML_EXTRA_STYLESHEET "${DOXYGEN_HTML_EXTRA_STYLESHEET};${STYLE_FILES}")



        doxygen_add_docs(${PARGS_TARGET_NAME}
            "${PARGS_INPUT_DIRS}"
            WORKING_DIRECTORY ${PARGS_CWD}
            COMMENT "Generate NCPP documentations"
        )

        if(PARGS_TARGET_FOLDER)
            set_target_properties(${PARGS_TARGET_NAME}
                PROPERTIES 
                    FOLDER ${PARGS_TARGET_FOLDER}
            )
        endif()
        if(PARGS_TARGET_LABEL)
            set_target_properties(${PARGS_TARGET_NAME}
                PROPERTIES 
                    PROJECT_LABEL ${PARGS_TARGET_LABEL}
            )
        endif()

    else()

        message(SEND_ERROR "<NCPP::Documentations> Not found doxygen")        

    endif()

endfunction()
