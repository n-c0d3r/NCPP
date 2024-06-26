#pragma once

/** @file ncpp/object.hpp
*	@brief Implements object functionalities.
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

#include <ncpp/mem/object_allocator.hpp>
#include <ncpp/utilities/magic.hpp>

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

    namespace internal {

        template<typename F_object__, typename F_allocator__ = mem::F_object_allocator, b8 is_default__ = true>
        NCPP_FORCE_INLINE F_object__* T_allocate_object(utilities::TF_no_deduct<F_allocator__>* allocator_p) {

            if constexpr (is_default__)
                return reinterpret_cast<F_object__*>(F_allocator__::default_p()->allocate(sizeof(F_object__), eastl::max((sz)NCPP_ALIGNOF(F_object__), (sz)EASTL_ALLOCATOR_MIN_ALIGNMENT), 0, 0));
            else
                return reinterpret_cast<F_object__*>(allocator_p->allocate(sizeof(F_object__), eastl::max((sz)NCPP_ALIGNOF(F_object__), (sz)EASTL_ALLOCATOR_MIN_ALIGNMENT), 0, 0));
        }

        template<typename F_object__, typename F_allocator__ = mem::F_object_allocator, b8 is_default__ = true>
        NCPP_FORCE_INLINE void T_deallocate_object(utilities::TF_no_deduct<F_allocator__>* allocator_p, F_object__* object_p) {

            if constexpr (is_default__)
                F_allocator__::default_p()->deallocate(object_p, 1);
            else
                allocator_p->deallocate(object_p, 1);
        }

        template<typename F_object__>
        NCPP_FORCE_INLINE void T_deconstruct_object(F_object__* object_p) {

            object_p->~F_object__();
        }

    }

}



#define NCPP_CREATE(AllocatorPointer, ObjectMagicType, ...) ( \
        new(                                                 \
            ncpp::internal::T_allocate_object<                         \
                NCPP_MAGIC_EXPAND(ObjectMagicType),                                  \
                ncpp::utilities::TF_nth_template_targ<      \
                    !std::is_same_v<decltype(AllocatorPointer), int>, \
                    ncpp::mem::F_object_allocator,           \
                    std::remove_pointer_t<decltype(AllocatorPointer)>  \
                >,                                       \
                std::is_same_v<decltype(AllocatorPointer), int>\
            >(AllocatorPointer)                               \
        ) NCPP_MAGIC_EXPAND(ObjectMagicType) { __VA_ARGS__ }      \
    )

#define NCPP_DESTROY(AllocatorPointer, ObjectPointer) {\
        ncpp::internal::T_deconstruct_object<std::remove_pointer_t<decltype(ObjectPointer)>>(ObjectPointer);        \
        ncpp::internal::T_deallocate_object<                         \
            std::remove_pointer_t<decltype(ObjectPointer)>,                                  \
            ncpp::utilities::TF_nth_template_targ_t<      \
                !std::is_same_v<decltype(AllocatorPointer), int>, \
                ncpp::mem::F_object_allocator,           \
                std::remove_pointer_t<decltype(AllocatorPointer)>  \
            >,                                         \
            std::is_same_v<decltype(AllocatorPointer), int>\
        >(AllocatorPointer, ObjectPointer);\
    };
