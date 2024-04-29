#pragma once

#include <ncpp/object.hpp>



namespace ncpp {

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        push_key_internal();

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

        allocator.deallocate(counter_p);

    }
    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    template<typename... F_args__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::T_create_object(F_args__&&... args) {

        pop_key_internal();

        F_allocator allocator;

        au32* counter_p = (au32*)allocator.allocate(
            NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
            utilities::T_alignof<F_object>,
            NCPP_OBJECT_MEMORY_HEADER_SIZE,
            0
        );

        *NCPP_RAW_P_TO_KEY_P(counter_p) = object_key_;
		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  	((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

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

		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  ((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        push_key_internal();

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

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
        counter_p->store(F_options__::initial_shared_reference_count, eastl::memory_order_release);

		*NCPP_RAW_P_TO_KEY_P(counter_p) = object_key_;
		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  	((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

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
        counter_p->store(F_options__::initial_shared_reference_count, eastl::memory_order_release);

		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  	((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        push_key_internal();

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

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
        counter_p->store(F_options__::initial_shared_reference_count, eastl::memory_order_release);

		*NCPP_RAW_P_TO_KEY_P(counter_p) = object_key_;
		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  	((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        is_shared_ = true;

    }

    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_child_oref__>
    NCPP_FORCE_INLINE void TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_child_oref__>::destroy_object_internal() noexcept {

        F_allocator allocator;

		(*NCPP_OBJECT_P_TO_DESTRUCTOR_CALLER_P(object_p_))(object_p_);

        au32* counter_p = NCPP_OBJECT_P_TO_COUNTER_P(object_p_);

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
        counter_p->store(F_options__::initial_shared_reference_count, eastl::memory_order_release);

		*NCPP_RAW_P_TO_DESTRUCTOR_CALLER_P(counter_p) = [](void* p){
		  	((F_object*)p)->~F_object();
		};

        object_p_ = NCPP_RAW_P_TO_OBJECT_P(counter_p);

        new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        is_shared_ = true;

    }

}