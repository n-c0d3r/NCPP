#pragma once

#include <ncpp/object.hpp>



namespace ncpp {

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, true>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, false>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, true>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, false>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }

}