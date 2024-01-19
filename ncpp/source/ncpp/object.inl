#pragma once

#include <ncpp/object.hpp>



namespace ncpp {

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TU_object_p<F_passed_object__, F_allocator__, true, F_options__>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)raw_object_p_)->~F_object();

        au32* counter_p = ((au32*)raw_object_p_) - (sizeof(sz) / sizeof(u32));

        allocator.deallocate(counter_p);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TU_object_p<F_passed_object__, F_allocator__, false, F_options__>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)raw_object_p_)->~F_object();

        au32* counter_p = ((au32*)raw_object_p_) - (sizeof(sz) / sizeof(u32));

        allocator.deallocate(counter_p);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TS_object_p<F_passed_object__, F_allocator__, true, F_options__>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)raw_object_p_)->~F_object();

        au32* counter_p = ((au32*)raw_object_p_) - (sizeof(sz) / sizeof(u32));

        allocator.deallocate(counter_p);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__>
    NCPP_FORCE_INLINE void TS_object_p<F_passed_object__, F_allocator__, false, F_options__>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)raw_object_p_)->~F_object();

        au32* counter_p = ((au32*)raw_object_p_) - (sizeof(sz) / sizeof(u32));

        allocator.deallocate(counter_p);

    }

}