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
            struct TF_binding_helper {



            };

        }

        template<typename F__>
        using TF_container_binding = typename internal::TF_binding_helper<F__>;

        template<typename F__>
        using TF_container_allocator = typename TF_container_binding<F__>::F_allocator;

        template<typename F__, typename F_new_allocator__>
        using TF_bind_container_allocator = typename TF_container_binding<F__>::template TF_bind_new_allocator<F_new_allocator__>;

    }

}

#define NCPP_CONTAINERS_DEFINE_BINDING(ContainerType, AllocatorType, NewAllocatorContainerType, ...) \
namespace ncpp {\
    \
    namespace containers {\
        \
        namespace internal {\
            \
            template<__VA_ARGS__>\
            struct TF_binding_helper<ContainerType> {\
                \
                using F_container = ContainerType;\
                \
                using F_allocator = AllocatorType;\
                \
                template<typename F_new_allocator__>\
                using TF_bind_new_allocator = NewAllocatorContainerType;\
                \
            };\
            \
        }\
        \
    }\
    \
}