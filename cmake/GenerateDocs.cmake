
message("Generate docs")



set(NCPP_OUTPUT_DOCUMENTATIONS_DIR "${CMAKE_CURRENT_BINARY_DIR}/documentations")
set(NCPP_OUTPUT_EXTERNAL_DOCUMENTATIONS_DIR "${NCPP_OUTPUT_DOCUMENTATIONS_DIR}/external")
set(NCPP_OUTPUT_INTERNAL_DOCUMENTATIONS_DIR "${NCPP_OUTPUT_DOCUMENTATIONS_DIR}/internal")

if(NOT EXISTS ${NCPP_OUTPUT_EXTERNAL_DOCUMENTATIONS_DIR})
    file(MAKE_DIRECTORY ${NCPP_OUTPUT_EXTERNAL_DOCUMENTATIONS_DIR})
endif()

if(NOT EXISTS ${NCPP_OUTPUT_INTERNAL_DOCUMENTATIONS_DIR})
    file(MAKE_DIRECTORY ${NCPP_OUTPUT_INTERNAL_DOCUMENTATIONS_DIR})
endif()



set(NCPP_DOCUMENTATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/documentations")
set(NCPP_EXTERNAL_DOCUMENTATIONS_DIR "${NCPP_DOCUMENTATIONS_DIR}/external")
set(NCPP_INTERNAL_DOCUMENTATIONS_DIR "${NCPP_DOCUMENTATIONS_DIR}/internal")

set(NCPP_MARKDOWN_DOCUMENTATIONS_DIR "${NCPP_DOCUMENTATIONS_DIR}/doxygen_markdown")



file(
    COPY 
    "${NCPP_DOCUMENTATIONS_DIR}/doxygen_themes"
    DESTINATION "${NCPP_OUTPUT_DOCUMENTATIONS_DIR}"
)



function(NCPPGenerateDocs docs_dir output_dir)
    set(DOXYFILE_TEMPLATE "${docs_dir}/Doxyfile.template")
    set(OUTPUT_DOXYFILE "${output_dir}/Doxyfile")
    file(READ ${DOXYFILE_TEMPLATE} DOXYFILE_TEMPLATE_CONTENT)
    string(
        REPLACE
        "OUTPUT_DIRECTORY       ="
        "OUTPUT_DIRECTORY       = ${output_dir}/ncpp"
        DOXYFILE_TEMPLATE_CONTENT
        ${DOXYFILE_TEMPLATE_CONTENT}
    )
    string(
        REPLACE
        "INPUT                  ="
        "INPUT                  = ${NCPP_MARKDOWN_DOCUMENTATIONS_DIR}
        INPUT += ${NCPP_SOURCE_DIR}
        FILE_PATTERNS += *.md *.markdown
        MARKDOWN_SUPPORT = YES
        TAB_SIZE = 2
        USE_MDFILE_AS_MAINPAGE = ${NCPP_MARKDOWN_DOCUMENTATIONS_DIR}/Overview.md
        "
        DOXYFILE_TEMPLATE_CONTENT
        ${DOXYFILE_TEMPLATE_CONTENT}
    )
    file(WRITE ${OUTPUT_DOXYFILE} ${DOXYFILE_TEMPLATE_CONTENT})    
    
    execute_process(
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${output_dir}
    )

endfunction()



message("Generate external docs")
NCPPGenerateDocs(
    ${NCPP_EXTERNAL_DOCUMENTATIONS_DIR}
    ${NCPP_OUTPUT_EXTERNAL_DOCUMENTATIONS_DIR}
)
message("Generate external docs done")

message("Generate internal docs")
NCPPGenerateDocs(
    ${NCPP_INTERNAL_DOCUMENTATIONS_DIR}
    ${NCPP_OUTPUT_INTERNAL_DOCUMENTATIONS_DIR}
)
message("Generate internal docs done")



message("Generate docs done")