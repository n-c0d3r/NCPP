
message(STATUS "<NCPP::TemplateTricks> Start generating template tricks")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/Utilities/SetGlobal)



#####################################################################################
#   Setup global variables
#####################################################################################
set(NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT 256 CACHE STRING "Max argument count of template tricks")



#####################################################################################
#   Setup the generated file
#####################################################################################
set(NCPP_TEMPLATE_TRICKS_FILE "${NCPP_GENERATED_FILES_DIR}/template_tricks.hpp")
file(WRITE ${NCPP_TEMPLATE_TRICKS_FILE} "\n
    #include <ncpp/prerequisites.hpp>\n
    namespace ncpp::utilities {
")



#####################################################################################
#   N-th argument
#####################################################################################
function(NCPP_TemplateTricks_GenerateNthArgumentTemplate MaxArgCount)

    set(fileContent " namespace internal { \n")

    set(fileContent "${fileContent} template<sz index__, typename... F_args__> struct TF_nth_template_arg_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_args "typename arg_0__")
    set(pass_template_args "arg_0__")

    foreach(index RANGE 0 ${maxIndex})

        if(NOT index EQUAL 0)
            set(template_args "${template_args}, typename arg_${index}__")
            set(pass_template_args "${pass_template_args}, arg_${index}__")
        endif()

        set(fileContent "${fileContent} template<${template_args}, typename... F_rest_args__>
            struct TF_nth_template_arg_getter_helper<${index}, ${pass_template_args}, F_rest_args__...> { using F = arg_${index}__; };
        ")

    endforeach()

    set(fileContent "${fileContent} template<sz index__, typename... F_args__>
        struct TF_nth_template_arg_helper {
            static_assert((index__ < sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_nth_template_arg_getter_helper<index__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz index__, typename... F_args__>
        using TF_nth_template_arg = typename internal::TF_nth_template_arg_helper<index__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_GenerateNthArgumentTemplate(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Finalize the generated file
#####################################################################################
file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "\n
    }
")



message(STATUS "<NCPP::TemplateTricks> Generate template tricks done")