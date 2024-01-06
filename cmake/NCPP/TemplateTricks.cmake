
message(STATUS "<NCPP::TemplateTricks> Start generating template tricks")



#####################################################################################
#   Includes
#####################################################################################
include(NCPP/Utilities/SetGlobal)



#####################################################################################
#   Setup global variables
#####################################################################################
set(NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT 128 CACHE STRING "Max argument count of template tricks")



#####################################################################################
#   Setup the generated file
#####################################################################################
set(NCPP_TEMPLATE_TRICKS_FILE "${NCPP_GENERATED_FILES_DIR}/template_tricks.hpp")
file(WRITE ${NCPP_TEMPLATE_TRICKS_FILE} "\n
    #pragma once
    #include <ncpp/prerequisites.hpp>\n
    namespace ncpp::utilities {
")



#####################################################################################
#   N-th template argument
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_NthTemplateArg MaxArgCount)

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

NCPP_TemplateTricks_CreateTemplate_NthTemplateArg(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove head template args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateArgs MaxArgCount)

    set(fileContent "
        template<typename... F_args__> struct TF_template_arg_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz count__, typename... F_args__> struct TF_remove_head_template_args_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_args "")
    set(pass_template_args "")

    foreach(index RANGE 0 ${maxIndex})

        set(fileContent "${fileContent} template<${template_args} typename... F_rest_args__>
            struct TF_remove_head_template_args_getter_helper<${index}, ${pass_template_args} F_rest_args__...> { using F = TF_template_arg_list<F_rest_args__...>; };
        ")

        set(template_args "${template_args} typename arg_${index}__,")
        set(pass_template_args "${pass_template_args} arg_${index}__,")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, typename... F_args__>
        struct TF_remove_head_template_args_helper {
            static_assert((count__ <= sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_remove_head_template_args_getter_helper<count__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, typename... F_args__>
        using TF_remove_head_template_args = typename internal::TF_remove_head_template_args_helper<count__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove tail template args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateArgs MaxArgCount)

    set(fileContent "
        template<typename... F_args__> struct TF_template_arg_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz remain_count__, typename... F_args__> struct TF_remove_tail_template_args_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_args "")
    set(pass_template_args "")

    foreach(index RANGE 0 ${maxIndex})

        set(template_args_2 "${template_args}")
        set(pass_template_args_2 "${pass_template_args}")

        if(NOT index EQUAL 0)
            set(template_args_2 "${template_args_2},")
            set(pass_template_args_2 "${pass_template_args_2},")
        endif()

        set(fileContent "${fileContent} template<${template_args_2} typename... F_rest_args__>
            struct TF_remove_tail_template_args_getter_helper<${index}, ${pass_template_args_2} F_rest_args__...> { using F = TF_template_arg_list<${pass_template_args}>; };
        ")

        if(NOT index EQUAL 0)
            set(template_args "${template_args},")
            set(pass_template_args "${pass_template_args},")
        endif()

        set(template_args "${template_args} typename arg_${index}__")
        set(pass_template_args "${pass_template_args} arg_${index}__")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, typename... F_args__>
        struct TF_remove_tail_template_args_helper {
            static_assert((count__ <= sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_remove_tail_template_args_getter_helper<(sizeof...(F_args__)) - count__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, typename... F_args__>
        using TF_remove_tail_template_args = typename internal::TF_remove_tail_template_args_helper<count__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Finalize the generated file
#####################################################################################
file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "\n
    }
")



message(STATUS "<NCPP::TemplateTricks> Generate template tricks done")