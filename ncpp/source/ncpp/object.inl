#pragma once

#include <ncpp/object.hpp>



namespace ncpp {

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::T_create_object(F_args__&&... args) {

        NCPP_ASSERT(!is_valid()) << "object reference is already valid";

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );

        F_object_key* object_key_p = (F_object_key*)(((u64*)counter_p) + 1);
        *object_key_p = object_key_;

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        pop_key_internal();

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::T_create_object(F_args__&&... args) {

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::T_create_object(F_args__&&... args) {

        pop_key_internal();

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );
        counter_p->store(1, eastl::memory_order_release);

        F_object_key* object_key_p = (F_object_key*)(((u64*)counter_p) + 1);
        *object_key_p = object_key_;

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::T_create_object(F_args__&&... args) {

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );
        counter_p->store(1, eastl::memory_order_release);

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        push_key_internal();

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::T_create_object(F_args__&&... args) {

        pop_key_internal();

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );
        counter_p->store(1, eastl::memory_order_release);

        F_object_key* object_key_p = (F_object_key*)(((u64*)counter_p) + 1);
        *object_key_p = object_key_;

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        is_shared_ = true;

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

        ((F_object*)object_p_)->~F_object();

        au32* counter_p = ((au32*)object_p_) - (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32));

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::T_create_object(F_args__&&... args) {

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );
        counter_p->store(1, eastl::memory_order_release);

        object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        is_shared_ = true;

    }

}