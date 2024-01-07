
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
#   N-th template type argument
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_NthTemplateTArg MaxArgCount)

    set(fileContent " namespace internal { \n")

    set(fileContent "${fileContent} template<sz index__, typename... F_args__> struct TF_nth_template_targ_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_targs "typename arg_0__")
    set(pass_template_targs "arg_0__")

    foreach(index RANGE 0 ${maxIndex})

        if(NOT index EQUAL 0)
            set(template_targs "${template_targs}, typename arg_${index}__")
            set(pass_template_targs "${pass_template_targs}, arg_${index}__")
        endif()

        set(fileContent "${fileContent} template<${template_targs}, typename... F_rest_args__>
            struct TF_nth_template_targ_getter_helper<${index}, ${pass_template_targs}, F_rest_args__...> { using F = arg_${index}__; };
        ")

    endforeach()

    set(fileContent "${fileContent} template<sz index__, typename... F_args__>
        struct TF_nth_template_targ_helper {
            static_assert((index__ < sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_nth_template_targ_getter_helper<index__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz index__, typename... F_args__>
        using TF_nth_template_targ = typename internal::TF_nth_template_targ_helper<index__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_NthTemplateTArg(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove head template type args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateTArgs MaxArgCount)

    set(fileContent "
        template<typename... F_args__> struct TF_template_targ_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz count__, typename... F_args__> struct TF_remove_head_template_targs_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_targs "")
    set(pass_template_targs "")

    foreach(index RANGE 0 ${maxIndex})

        set(fileContent "${fileContent} template<${template_targs} typename... F_rest_args__>
            struct TF_remove_head_template_targs_getter_helper<${index}, ${pass_template_targs} F_rest_args__...> { using F = TF_template_targ_list<F_rest_args__...>; };
        ")

        set(template_targs "${template_targs} typename arg_${index}__,")
        set(pass_template_targs "${pass_template_targs} arg_${index}__,")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, typename... F_args__>
        struct TF_remove_head_template_targs_helper {
            static_assert((count__ <= sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_remove_head_template_targs_getter_helper<count__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, typename... F_args__>
        using TF_remove_head_template_targs = typename internal::TF_remove_head_template_targs_helper<count__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateTArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove tail template type args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateTArgs MaxArgCount)

    set(fileContent "
        template<typename... F_args__> struct TF_template_targ_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz remain_count__, typename... F_args__> struct TF_remove_tail_template_targs_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_targs "")
    set(pass_template_targs "")

    foreach(index RANGE 0 ${maxIndex})

        set(template_targs_2 "${template_targs}")
        set(pass_template_targs_2 "${pass_template_targs}")

        if(NOT index EQUAL 0)
            set(template_targs_2 "${template_targs_2},")
            set(pass_template_targs_2 "${pass_template_targs_2},")
        endif()

        set(fileContent "${fileContent} template<${template_targs_2} typename... F_rest_args__>
            struct TF_remove_tail_template_targs_getter_helper<${index}, ${pass_template_targs_2} F_rest_args__...> { using F = TF_template_targ_list<${pass_template_targs}>; };
        ")

        if(NOT index EQUAL 0)
            set(template_targs "${template_targs},")
            set(pass_template_targs "${pass_template_targs},")
        endif()

        set(template_targs "${template_targs} typename arg_${index}__")
        set(pass_template_targs "${pass_template_targs} arg_${index}__")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, typename... F_args__>
        struct TF_remove_tail_template_targs_helper {
            static_assert((count__ <= sizeof...(F_args__)), \"out of bound\");
            using F = typename TF_remove_tail_template_targs_getter_helper<(sizeof...(F_args__)) - count__, F_args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, typename... F_args__>
        using TF_remove_tail_template_targs = typename internal::TF_remove_tail_template_targs_helper<count__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateTArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   N-th template value argument
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_NthTemplateVArg MaxArgCount)

    set(fileContent " namespace internal { \n")

    set(fileContent "${fileContent} template<sz index__, auto... args__> struct TF_nth_template_varg_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_vargs "auto arg_0__")
    set(pass_template_vargs "arg_0__")

    foreach(index RANGE 0 ${maxIndex})

        if(NOT index EQUAL 0)
            set(template_vargs "${template_vargs}, auto arg_${index}__")
            set(pass_template_vargs "${pass_template_vargs}, arg_${index}__")
        endif()

        set(fileContent "${fileContent} template<${template_vargs}, auto... rest_args__>
            struct TF_nth_template_varg_getter_helper<${index}, ${pass_template_vargs}, rest_args__...> { static constexpr auto value = arg_${index}__; };
        ")

    endforeach()

    set(fileContent "${fileContent} template<sz index__, auto... args__>
        struct TF_nth_template_varg_helper {
            static_assert((index__ < sizeof...(args__)), \"out of bound\");
            static constexpr auto value = TF_nth_template_varg_getter_helper<index__, args__...>::value;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz index__, auto... args__>
        static constexpr auto T_nth_template_varg = internal::TF_nth_template_varg_helper<index__, args__...>::value;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_NthTemplateVArg(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove head template value args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateVArgs MaxArgCount)

    set(fileContent "
        template<auto... args__> struct TF_template_varg_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz count__, auto... args__> struct TF_remove_head_template_vargs_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_vargs "")
    set(pass_template_vargs "")

    foreach(index RANGE 0 ${maxIndex})

        set(fileContent "${fileContent} template<${template_vargs} auto... rest_args__>
            struct TF_remove_head_template_vargs_getter_helper<${index}, ${pass_template_vargs} rest_args__...> { using F = TF_template_varg_list<rest_args__...>; };
        ")

        set(template_vargs "${template_vargs} auto arg_${index}__,")
        set(pass_template_vargs "${pass_template_vargs} arg_${index}__,")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, auto... args__>
        struct TF_remove_head_template_vargs_helper {
            static_assert((count__ <= sizeof...(args__)), \"out of bound\");
            using F = typename TF_remove_head_template_vargs_getter_helper<count__, args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, auto... F_args__>
        using TF_remove_head_template_vargs = typename internal::TF_remove_head_template_vargs_helper<count__, F_args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveHeadTemplateVArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Remove tail template value args
#####################################################################################
function(NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateVArgs MaxArgCount)

    set(fileContent "
        template<auto... args__> struct TF_template_varg_list;

        namespace internal {
        \n
    ")

    set(fileContent "${fileContent} template<sz remain_count__, auto... args__> struct TF_remove_tail_template_vargs_getter_helper; \n")

    MATH(EXPR maxIndex "${MaxArgCount} - 1")

    set(template_vargs "")
    set(pass_template_vargs "")

    foreach(index RANGE 0 ${maxIndex})

        set(template_vargs_2 "${template_vargs}")
        set(pass_template_vargs_2 "${pass_template_vargs}")

        if(NOT index EQUAL 0)
            set(template_vargs_2 "${template_vargs_2},")
            set(pass_template_vargs_2 "${pass_template_vargs_2},")
        endif()

        set(fileContent "${fileContent} template<${template_vargs_2} auto... rest_args__>
            struct TF_remove_tail_template_vargs_getter_helper<${index}, ${pass_template_vargs_2} rest_args__...> { using F = TF_template_varg_list<${pass_template_vargs}>; };
        ")

        if(NOT index EQUAL 0)
            set(template_vargs "${template_vargs},")
            set(pass_template_vargs "${pass_template_vargs},")
        endif()

        set(template_vargs "${template_vargs} auto arg_${index}__")
        set(pass_template_vargs "${pass_template_vargs} arg_${index}__")

    endforeach()

    set(fileContent "${fileContent} template<sz count__, auto... args__>
        struct TF_remove_tail_template_vargs_helper {
            static_assert((count__ <= sizeof...(args__)), \"out of bound\");
            using F = typename TF_remove_tail_template_vargs_getter_helper<(sizeof...(args__)) - count__, args__...>::F;
         };
    ")

    set(fileContent "${fileContent} } \n")

    set(fileContent "${fileContent}
        template<sz count__, auto... args__>
        using TF_remove_tail_template_vargs = typename internal::TF_remove_tail_template_vargs_helper<count__, args__...>::F;
         \n
    ")

    file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "${fileContent}")

endfunction()

NCPP_TemplateTricks_CreateTemplate_RemoveTailTemplateVArgs(${NCPP_TEMPLATE_TRICKS_MAX_ARG_COUNT})



#####################################################################################
#   Finalize the generated file
#####################################################################################
file(APPEND ${NCPP_TEMPLATE_TRICKS_FILE} "\n
    }
")



message(STATUS "<NCPP::TemplateTricks> Generate template tricks done")