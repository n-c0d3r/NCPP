#pragma once

/** @file ncpp/containers/binding_helper.hpp
*	@brief Implements binding helper.
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

	namespace containers {

        namespace internal {

            template<typename F__>
            struct TF_allocator_binding_helper {

                using F_container = F__;

                using F_allocator = void;

                template<typename F_new_allocator__>
                using TF_bind_new_allocator = F__;

            };

        }

        template<typename F__>
        using TF_container_allocator = typename internal::TF_allocator_binding_helper<F__>::F_allocator;

        template<typename F__>
        static constexpr b8 T_is_has_container_allocator = !std::is_same_v<void, TF_container_allocator<F__>>;

        template<typename F__, typename F_new_allocator__>
        using TF_bind_container_allocator = typename internal::TF_allocator_binding_helper<F__>::template TF_bind_new_allocator<F_new_allocator__>;

        template<typename F1__, typename F2__>
        static constexpr b8 T_is_same_container = (
            std::is_same_v<
                F1__,
                TF_bind_container_allocator<F2__, TF_container_allocator<F1__>>
            >
        );

    }

}

#define NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(ContainerType, AllocatorType, NewAllocatorContainerType, ...) \
    template<__VA_ARGS__>\
    struct ::ncpp::containers::internal::TF_allocator_binding_helper<ContainerType> {\
        \
        using F_container = ContainerType;\
        \
        using F_allocator = AllocatorType;\
        \
        template<typename F_new_allocator__>\
        using TF_bind_new_allocator = NewAllocatorContainerType;\
        \
    };