#pragma once

/** @file ncpp/rtti/robject_flag.hpp
*	@brief Implements reflectable object flag.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/iostream.hpp>
#include <ncpp/utilities/is_function.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/rtti/traits_defs.hpp>

#pragma endregion



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

	namespace rtti {

		NCPP_RTTI_CREATE_FLAG(F_robject_flag);
		NCPP_RTTI_CREATE_FLAG(F_robject_abstract_flag);
		NCPP_RTTI_CREATE_FLAG(F_robject_virtual_flag);
		NCPP_RTTI_CREATE_FLAG(F_robject_has_base_flag);

        NCPP_RTTI_CREATE_FLAG(F_disable_reflect_robject_type_info);
        NCPP_RTTI_CREATE_FLAG(F_disable_reflect_robject_member_info);
        NCPP_RTTI_CREATE_FLAG(F_disable_reflect_robject_metadata);

		NCPP_RTTI_CREATE_FLAG(F_user_reflect_custom_params_flag);

		template<class F_robject__, typename F_member__, class F_member_static_info__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_pre_reflect_member_flag);
		template<class F_robject__, typename F_member__, class F_member_static_info__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_post_reflect_member_flag);
    
        template<class F_robject__, class F_base__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_pre_reflect_base_flag);
        template<class F_robject__, class F_base__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_post_reflect_base_flag);
    
        template<class F_robject__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_pre_reflect_object_flag);
        template<class F_robject__, NCPP_RTTI_SPECIFIC_TARGS()>
		NCPP_RTTI_CREATE_FLAG(TF_user_post_reflect_object_flag);
    
#define NCPP_ROBJECT_DISABLE_DEFAULT_REFLECT() \
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_disable_reflect_robject_member_info);\
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_disable_reflect_robject_type_info);\
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::rtti::F_disable_reflect_robject_metadata);



        NCPP_RTTI_CREATE_FLAG(F_sinfo_flag);

        NCPP_RTTI_CREATE_FLAG(F_sinfo_base_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_member_flag);

        NCPP_RTTI_CREATE_FLAG(F_sinfo_static_flag);

        NCPP_RTTI_CREATE_FLAG(F_sinfo_virtual_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_abstract_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_const_flag);

        NCPP_RTTI_CREATE_FLAG(F_sinfo_function_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_variable_flag);

        NCPP_RTTI_CREATE_FLAG(F_sinfo_private_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_protected_flag);
        NCPP_RTTI_CREATE_FLAG(F_sinfo_public_flag);



        template<typename F__>
        struct TA_sinfo_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag);

        };



        template<typename F__>
        struct TA_sinfo_base_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_base_flag);

        };

        template<typename F__>
        struct TA_sinfo_member_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_member_flag);

        };



        template<typename F__>
        struct TA_sinfo_static_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_static_flag);

        };



        template<typename F__>
        struct TA_sinfo_virtual_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_virtual_flag);

        };

        template<typename F__>
        struct TA_sinfo_abstract_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_abstract_flag);

        };

        template<typename F__>
        struct TA_sinfo_const_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_const_flag);

        };



        template<typename F__>
        struct TA_sinfo_variable_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_variable_flag);

        };

        template<typename F__>
        struct TA_sinfo_function_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_function_flag);

        };



        template<typename F__>
        struct TA_sinfo_private_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_private_flag);

        };

        template<typename F__>
        struct TA_sinfo_protected_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_protected_flag);

        };

        template<typename F__>
        struct TA_sinfo_public_filter {

            static constexpr b8 value = NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_flag) && NCPP_RTTI_IS_HAS_FLAG(F__, rtti::F_sinfo_public_flag);

        };
                
	}

}
