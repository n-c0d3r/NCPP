#pragma once

/**
 *  @file ncpp/utilities/key_type.hpp
 *  @brief Implements key_type.
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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

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

    namespace utilities {

        namespace internal {

            template<class F__, typename = void>
            struct TF_is_has_eastl_key_type : eastl::false_type {};
            template<class F__>
            struct TF_is_has_eastl_key_type<F__, std::void_t<typename F__::key_type>> : eastl::true_type {};

            template<class F__, typename = void>
            struct TF_is_has_ncpp_key_type : eastl::false_type {};
            template<class F__>
            struct TF_is_has_ncpp_key_type<F__, std::void_t<typename F__::F_key>> : eastl::true_type {};

            template<class F__, i32 = 0>
            struct TF_key_helper {

                using F = void;

            };

            template<class F__>
            struct TF_key_helper<F__, 1> {

                using F = typename F__::key_type;

            };

            template<class F__>
            struct TF_key_helper<F__, 2> {

                using F = typename F__::F_key;

            };

        }
        


        template<class F__>
        using TF_key = typename internal::TF_key_helper<
            F__,
            internal::TF_is_has_eastl_key_type<F__>::key * 1
            + internal::TF_is_has_ncpp_key_type<F__>::key * 2
        >::F;

    }

}