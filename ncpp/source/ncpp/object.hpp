#pragma once

/** @file ncpp/object.hpp
*	@brief Implement object.
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

#include <ncpp/mem/default_allocator.hpp>
#include <ncpp/mem/object_allocator.hpp>
#include <ncpp/rtti/rtti_flag.hpp>
#include <ncpp/utilities/mem_wrap.hpp>
#include <ncpp/utilities/alignof.hpp>
#include <ncpp/utilities/singleton.hpp>
#include <ncpp/utilities/unique_lock.hpp>
#include <ncpp/utilities/cpass.hpp>
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/pac/thread_index.hpp>
#include <ncpp/pac/spin_lock.hpp>

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

#define NCPP_OBJECT_FRIEND_CLASSES() \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_key_subpool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_key_pool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe_fr__, typename F_allocator_fr__>     \
            friend class ncpp::TF_default_object_manager;                                        \
                                                    \
            template<typename F_object_fr__, typename F_requirements__>\
            friend class ncpp::TW_oref;\
            template<typename F_object_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements__>\
            friend class ncpp::TK_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements__>\
            friend class ncpp::TU_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements__>\
            friend class ncpp::TS_oref;\
            template<typename F_object_fr__, typename F_allocator_fr__, class F_options_fr__, ncpp::b8 is_has_object_key_fr__, typename F_requirements__>\
            friend class ncpp::TX_oref;

#define NCPP_OBJECT_MEMORY_HEADER_SIZE (sizeof(ncpp::u64) * 2)



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_OBJECT_IMPLEMENT(...) \
            NCPP_OBJECT_FRIEND_CLASSES()

#define NCPP_OBJECT_THREAD_SAFE() \
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::F_object_thread_safe_flag);



    NCPP_RTTI_CREATE_FLAG(F_object_thread_safe_flag);
    NCPP_RTTI_CREATE_FLAG(F_oref_flag);

    template<typename F__>
    concept T_is_object_thread_safe = NCPP_RTTI_IS_HAS_FLAG(F__, F_object_thread_safe_flag);
    template<typename F__>
    concept T_is_oref = NCPP_RTTI_IS_HAS_FLAG(F__, F_oref_flag);

    struct F_object_key {

        union {

            u64 value = NCPP_U64_MAX;

            struct {

                u32 id : 32;
                u32 generation : 31;
                u32 is_thread_safe : 1;

            };

        };

        NCPP_FORCE_INLINE constexpr F_object_key() noexcept = default;
        NCPP_FORCE_INLINE constexpr F_object_key(F_null) noexcept : value(NCPP_U64_MAX) {}

        NCPP_FORCE_INLINE constexpr F_object_key(u64 value_in) noexcept :
            value(value_in)
        {}
        NCPP_FORCE_INLINE constexpr F_object_key(u32 id_in, u32 generation_in, b8 is_thread_safe_in) noexcept :
            id(id_in),
            generation(generation_in),
            is_thread_safe(is_thread_safe_in)
        {

        }



        NCPP_FORCE_INLINE constexpr operator u64 () const noexcept {

            return value;
        }

        friend NCPP_FORCE_INLINE constexpr b8 operator == (F_object_key a, F_object_key b) noexcept {

            return (a.id == b.id) && (a.generation == b.generation);
        }
        friend NCPP_FORCE_INLINE constexpr b8 operator != (F_object_key a, F_object_key b) noexcept {

            return (a.id != b.id) || (a.generation != b.generation);
        }



        NCPP_FORCE_INLINE constexpr b8 is_valid() const noexcept {

            return (id != NCPP_U32_MAX);
        }
        NCPP_FORCE_INLINE constexpr b8 is_null() const noexcept {

            return (id == NCPP_U32_MAX);
        }



        NCPP_FORCE_INLINE constexpr void reset() noexcept {

            id = NCPP_U32_MAX;
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_CHECK_OREF_REQUIREMENTS(...) \
            NCPP_ENABLE_IF_DEBUG( \
                std::remove_const_t<std::remove_pointer_t<decltype(__VA_ARGS__)>>::F_requirements::T_check(*(__VA_ARGS__))                    \
            );

    template<class F_requirements__, b8 is_always_valid__ = false>
    struct TF_requirements_base {

        static constexpr b8 is_always_valid = is_always_valid__;



        template<
            class F_passed_oref__,
            class F_requirements_binded_oref__ = std::remove_const_t<std::remove_reference_t<F_passed_oref__>>::template TF_bind_requirements<F_requirements__>,
            typename F_return__ = utilities::TF_nth_template_targ<
                std::is_rvalue_reference_v<F_passed_oref__>,
                utilities::TF_nth_template_targ<
                    std::is_const_v<std::remove_reference_t<F_passed_oref__>>,
                    F_requirements_binded_oref__,
                    const F_requirements_binded_oref__
                >&,
                utilities::TF_nth_template_targ<
                    std::is_const_v<std::remove_reference_t<F_passed_oref__>>,
                    F_requirements_binded_oref__,
                    const F_requirements_binded_oref__
                >&&
            >
        >
        static NCPP_FORCE_INLINE F_return__ T_apply(F_passed_oref__&& oref) noexcept
        {

            NCPP_ENABLE_IF_DEBUG(
                F_requirements__::T_check((const F_requirements_binded_oref__&)oref);
            );

            return ((F_return__)oref);
        }

    };

    struct F_default_requirements : public TF_requirements_base<F_default_requirements> {

        template<T_is_oref F_oref__>
        static NCPP_FORCE_INLINE void T_check(const F_oref__& oref) noexcept {
        }

    };

    struct F_valid_requirements : public TF_requirements_base<F_valid_requirements, true> {

        template<T_is_oref F_oref__>
        static NCPP_FORCE_INLINE void T_check(const F_oref__& oref) noexcept {

            NCPP_ASSERT(oref.is_valid()) << "invalid oref";
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_key_subpool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_key_pool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_manager;

    template<typename F_passed_object__, typename F_requirements__>
    class TW_oref;
    template<typename F_passed_object__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TK_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TU_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TS_oref;
    template<typename F_passed_object__, typename F_allocator__, class F_options__, b8 is_has_object_key__, typename F_requirements__>
    class TX_oref;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, typename F_requirements__ = F_default_requirements>
    using TW = TW_oref<F_passed_object__, F_requirements__>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false,
        typename F_requirements__ = F_default_requirements
    >
    using TK = TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_default_requirements
    >
    using TK2 = TK_oref<F_passed_object__, F_options__, true, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false,
        typename F_requirements__ = F_default_requirements
    >
    using TU = TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_default_requirements
    >
    using TU2 = TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false,
        typename F_requirements__ = F_default_requirements
    >
    using TS = TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_default_requirements
    >
    using TS2 = TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false,
        typename F_requirements__ = F_default_requirements
    >
    using TX = TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        typename F_requirements__ = F_default_requirements
    >
    using TX2 = TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__>
    using TW_valid = TW_oref<F_passed_object__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false
    >
    using TK_valid = TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        class F_options__ = F_default_object_options
    >
    using TK2_valid = TK_oref<F_passed_object__, F_options__, true, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false
    >
    using TU_valid = TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options
    >
    using TU2_valid = TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false
    >
    using TS_valid = TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options
    >
    using TS2_valid = TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options,
        b8 is_has_object_key__ = false
    >
    using TX_valid = TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_valid_requirements>;

    template<
        typename F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        class F_options__ = F_default_object_options
    >
    using TX2_valid = TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_valid_requirements>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_key_subpool;

    template<typename F_allocator__>
    class TF_default_object_key_subpool<true, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;



    private:
        u32 index_ = 0;
        u32 object_key_begin_index_ = 0;
        u32 max_local_generation_count_ = 0;
        u32 subpool_count_ = 0;

        struct F_generation_buffer {

            u32* generation_p = 0;
            u32* next_p = 0;
            u32 size = 0;
            mutable pac::TF_spin_lock<false, true> lock;

            ~F_generation_buffer(){

                mem::F_default_allocator allocator;

                if(size) {

                    allocator.deallocate(generation_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                sz buffer_size_in_bytes = sizeof(u32) * new_size;
                u32* new_generation_p = (u32*)allocator.allocate(
                    2 * buffer_size_in_bytes,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = new_generation_p + new_size;

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, 2 * min_size * sizeof(u32));

                    allocator.deallocate(generation_p);

                }

                generation_p = new_generation_p;
                next_p = new_next_p;
                size = new_size;

            }

            NCPP_FORCE_INLINE void ensure_concurrent(u32 min_size) noexcept {

                lock.wlock();

                if(min_size > size) {

                    resize(min_size);

                }

                lock.wunlock();

            }

        };
        F_generation_buffer generation_buffer_;

        au32 free_generation_tail_index_ = NCPP_U32_MAX;
        au32 generation_capacity_ = 0;



    public:
        NCPP_FORCE_INLINE u32 index() const noexcept { return index_; }
        NCPP_FORCE_INLINE u32 subpool_count() const noexcept { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const noexcept { return max_local_generation_count_; }



    public:
        TF_default_object_key_subpool()
        {
        }



    private:
        inline b8 try_optain_generation(u32 free_generation_tail_index, u32& out_free_generation_tail_index, u32& out_generation_index, u32& out_generation) noexcept {

            if(free_generation_tail_index == NCPP_U32_MAX){

                out_generation_index = generation_capacity_.fetch_add(1, eastl::memory_order_acq_rel);

                generation_buffer_.ensure_concurrent(out_generation_index + 1);

                generation_buffer_.lock.rlock();
                generation_buffer_.generation_p[out_generation_index] = 0;
                generation_buffer_.lock.runlock();

                out_generation = 0;

                return true;
            }
            else{

                generation_buffer_.lock.rlock();
                u32 next_free_generation_tail_index = generation_buffer_.next_p[free_generation_tail_index];
                out_generation = generation_buffer_.generation_p[free_generation_tail_index];
                generation_buffer_.lock.runlock();

                out_free_generation_tail_index = next_free_generation_tail_index;
                out_generation_index = free_generation_tail_index;

                return false;
            }

        }
        inline void optain_generation(u32& out_generation_index, u32& out_generation) noexcept {

            u32 free_generation_tail_index = free_generation_tail_index_.load(eastl::memory_order_acquire);

            u32 obtained_generation_index = NCPP_U32_MAX;
            u32 new_free_generation_tail_index = NCPP_U32_MAX;

            b8 is_special = try_optain_generation(
                free_generation_tail_index,
                new_free_generation_tail_index,
                obtained_generation_index,
                out_generation
            );

            while(
                free_generation_tail_index_.compare_exchange_weak(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    eastl::memory_order_acq_rel
                )
                && !is_special
            ) {

                is_special = try_optain_generation(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    obtained_generation_index,
                    out_generation
                );

            }

            out_generation_index = obtained_generation_index;

        }

        inline void try_free_generation(u32 generation_index, u32 free_generation_tail_index, u32& out_free_generation_tail_index) noexcept {

            generation_buffer_.lock.rlock();
            generation_buffer_.next_p[generation_index] = free_generation_tail_index;
            generation_buffer_.lock.runlock();

            out_free_generation_tail_index = generation_index;

        }
        inline void free_generation(u32 generation_index) noexcept {

            generation_buffer_.lock.rlock();
            ++(generation_buffer_.generation_p[generation_index]);
            generation_buffer_.lock.runlock();

            u32 free_generation_tail_index = free_generation_tail_index_.load(eastl::memory_order_acquire);

            u32 new_free_generation_tail_index = NCPP_U32_MAX;

            try_free_generation(generation_index, free_generation_tail_index, new_free_generation_tail_index);

            while(
                free_generation_tail_index_.compare_exchange_weak(
                    free_generation_tail_index,
                    new_free_generation_tail_index,
                    eastl::memory_order_acq_rel
                )
            )
            {

                try_free_generation(generation_index, free_generation_tail_index, new_free_generation_tail_index);

            }

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 generation_index = NCPP_U32_MAX;
            u32 generation = NCPP_U32_MAX;
            optain_generation(generation_index, generation);

            NCPP_ASSERT(generation_index != NCPP_U32_MAX) << "invalid generation index";
            NCPP_ASSERT(generation != NCPP_U32_MAX) << "invalid generation";

            return F_object_key{
                generation_index,
                generation,
                true
            };
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            free_generation(object_key.id);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            generation_buffer_.lock.rlock();
            b8 result = (generation_buffer_.generation_p[object_key.id] == object_key.generation);
            generation_buffer_.lock.runlock();

            return result;
        }

    };



    template<typename F_allocator__>
    class TF_default_object_key_subpool<false, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;



    private:
        struct F_generation_buffer {

            u32* generation_p = 0;
            u32* next_p = 0;
            u32 size = 0;

            ~F_generation_buffer(){

                mem::F_default_allocator allocator;

                if(size) {

                    allocator.deallocate(generation_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                sz buffer_size_in_bytes = sizeof(u32) * new_size;
                u32* new_generation_p = (u32*)allocator.allocate(
                    2 * buffer_size_in_bytes,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = new_generation_p + new_size;

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, 2 * min_size * sizeof(u32));

                    allocator.deallocate(generation_p);

                }

                generation_p = new_generation_p;
                next_p = new_next_p;
                size = new_size;

            }

            NCPP_FORCE_INLINE void ensure(u32 min_size) noexcept {

                if(min_size > size) {

                    resize(min_size);

                }

            }

        };
        F_generation_buffer generation_buffer_;

        u32 free_generation_tail_index_ = NCPP_U32_MAX;
        u32 generation_capacity_ = 0;



    public:
        TF_default_object_key_subpool()
        {
        }



    private:
        inline void optain_generation(u32& out_generation_index, u32& out_generation) noexcept {

            if(free_generation_tail_index_ == NCPP_U32_MAX){

                out_generation_index = generation_capacity_++;

                generation_buffer_.ensure(out_generation_index + 1);

                generation_buffer_.generation_p[out_generation_index] = 0;

                out_generation = 0;
            }
            else{

                u32 next_free_generation_tail_index = generation_buffer_.next_p[free_generation_tail_index_];
                out_generation = generation_buffer_.generation_p[free_generation_tail_index_];

                out_generation_index = free_generation_tail_index_;
                free_generation_tail_index_ = next_free_generation_tail_index;
            }

        }

        inline void free_generation(u32 generation_index) noexcept {

            ++(generation_buffer_.generation_p[generation_index]);

            generation_buffer_.next_p[generation_index] = free_generation_tail_index_;

            free_generation_tail_index_ = generation_index;

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 generation_index = NCPP_U32_MAX;
            u32 generation = NCPP_U32_MAX;
            optain_generation(generation_index, generation);

            NCPP_ASSERT(generation_index != NCPP_U32_MAX) << "invalid generation index";
            NCPP_ASSERT(generation != NCPP_U32_MAX) << "invalid generation";

            return F_object_key{
                generation_index,
                generation,
                false
            };
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            free_generation(object_key.id);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            return (generation_buffer_.generation_p[object_key.id] == object_key.generation);
        }

    };



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_key_pool;

    template<typename F_allocator__>
    class TF_default_object_key_pool<true, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;

        using F_subpool = TF_default_object_key_subpool<is_thread_safe>;



    private:
        u32 subpool_count_ = 1;
        u32 max_local_generation_count_ = 1;
        containers::TF_vector<F_subpool> subpool_vector_;

    public:
        NCPP_FORCE_INLINE u32 subpool_count() const { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const { return max_local_generation_count_; }
        NCPP_FORCE_INLINE const containers::TF_vector<F_subpool>& subpool_vector() const { return subpool_vector_; }



    public:
        TF_default_object_key_pool(u32 subpool_count = 1) :
                subpool_count_(subpool_count),
                subpool_vector_(subpool_count)
        {

            max_local_generation_count_ = (NCPP_U32_MAX / subpool_count);

            for(u32 i = 0; i < subpool_count; ++i) {

                subpool_vector_[i].index_ = i;
                subpool_vector_[i].object_key_begin_index_ = i * max_local_generation_count_;
                subpool_vector_[i].max_local_generation_count_ = max_local_generation_count_;
                subpool_vector_[i].subpool_count_ = subpool_count;
            }

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            u32 thread_index = pac::thread_index();

            auto& subpool = subpool_vector_[thread_index];

            F_object_key object_key = subpool.pop();

            object_key.id += subpool.object_key_begin_index_;

            return object_key;
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            object_key.id %= max_local_generation_count_;

            subpool_vector_[object_key.id / max_local_generation_count_].push(object_key);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            if(object_key.is_null())
                return false;

            object_key.id %= max_local_generation_count_;

            return subpool_vector_[object_key.id / max_local_generation_count_].check(object_key);
        }

    };

    template<typename F_allocator__>
    class TF_default_object_key_pool<false, F_allocator__> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;

        using F_subpool = TF_default_object_key_subpool<is_thread_safe>;



    private:
        F_subpool subpool_;

    public:
        NCPP_FORCE_INLINE const F_subpool& subpool() const { return subpool_; }



    public:
        TF_default_object_key_pool()
        {

        }



    public:
        NCPP_FORCE_INLINE F_object_key pop() noexcept {

            return subpool_.pop();
        }
        NCPP_FORCE_INLINE void push(F_object_key object_key) noexcept {

            subpool_.push(object_key);
        }



    public:
        NCPP_FORCE_INLINE b8 check(F_object_key object_key) const noexcept {

            if(object_key.is_null())
                return false;

            return subpool_.check(object_key);
        }

    };

    using F_default_object_key_pool = TF_default_object_key_pool<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__ = false, typename F_allocator__ = mem::F_default_allocator>
    class TF_default_object_manager;

    template<typename F_allocator__>
    class TF_default_object_manager<true, F_allocator__> : public utilities::TI_singleton<TF_default_object_manager<true, F_allocator__>> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = true;

        using F_allocator = F_allocator__;

        using F_key_pool = TF_default_object_key_pool<is_thread_safe, F_allocator>;



    private:
        F_key_pool key_pool_;

    public:
        NCPP_FORCE_INLINE F_key_pool& key_pool() noexcept { return key_pool_; }
        NCPP_FORCE_INLINE const F_key_pool& key_pool() const noexcept { return key_pool_; }



    public:
        TF_default_object_manager(u32 subpool_count) :
            key_pool_(subpool_count)
        {

        }
        ~TF_default_object_manager(){

        }

    };

    template<typename F_allocator__>
    class TF_default_object_manager<false, F_allocator__> : public utilities::TI_singleton<TF_default_object_manager<false, F_allocator__>> {

    public:
        NCPP_OBJECT_FRIEND_CLASSES();



    public:
        static constexpr b8 is_thread_safe = false;

        using F_allocator = F_allocator__;

        using F_key_pool = TF_default_object_key_pool<is_thread_safe, F_allocator>;



    private:
        F_key_pool key_pool_;

    public:
        NCPP_FORCE_INLINE F_key_pool& key_pool() noexcept { return key_pool_; }
        NCPP_FORCE_INLINE const F_key_pool& key_pool() const noexcept { return key_pool_; }



    public:
        TF_default_object_manager()
        {

        }
        ~TF_default_object_manager(){

        }

    };

    using F_default_object_manager = TF_default_object_manager<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_allocator__>
    requires (!std::is_same_v<F_allocator__, mem::F_default_allocator>)
    inline void T_initialize_default_object_managers(){

        new TF_default_object_manager<true, F_allocator__>(std::thread::hardware_concurrency());
        new TF_default_object_manager<false, F_allocator__>();

    }
    template<typename F_allocator__>
    requires (!std::is_same_v<F_allocator__, mem::F_default_allocator>)
    inline void T_release_default_object_managers(){

        delete (&TF_default_object_manager<true, F_allocator__>::instance());
        delete (&TF_default_object_manager<false, F_allocator__>::instance());

    }



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_allocator__ = mem::F_default_allocator>
    struct TF_default_object_options {

        using F_this = TF_default_object_options<F_allocator__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        using F_allocator = F_allocator__;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        template<b8 is_thread_safe_ = false>
        using TF_manager = TF_default_object_manager<is_thread_safe_, F_allocator__>;

        using F_manager = TF_manager<>;

    };

    using F_default_object_options = TF_default_object_options<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F1__, typename F2__>
    concept T_is_object_down_castable = requires(F1__* p1, F2__* p2) {
        p2 = p1;
    };
    template<typename F1__, typename F2__>
    concept T_is_object_up_castable = T_is_object_down_castable<F2__, F1__> && !T_is_object_down_castable<F1__, F2__>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(...) \
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_up_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_up_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_up_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_up_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_up_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_down_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_down_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_down_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires T_is_object_down_castable<F_passed_object, F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_down_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    requires (T_is_object_up_castable<F_passed_object, F_other_p__> || T_is_object_down_castable<F_passed_object, F_other_p__>)\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }\
\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__& T_force_cast() & noexcept {\
\
                        return (__VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__& T_force_cast() const & noexcept {\
\
                        return (const __VA_ARGS__&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE __VA_ARGS__&& T_force_cast() && noexcept {\
\
                        return (__VA_ARGS__&&)*this;\
                    }\
                    template<typename F_other_p__>\
                    NCPP_FORCE_INLINE const __VA_ARGS__&& T_force_cast() const && noexcept {\
\
                        return (const __VA_ARGS__&&)*this;\
                    }



    template<typename F_passed_object__, typename F_requirements__ = F_default_requirements>
    class TW_oref {

    private:
        using F_this = TW_oref<F_passed_object__, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_requirements = F_requirements__;

        static constexpr b8 is_const = std::is_const_v<F_passed_object__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TW_oref<F_passed_object__, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TW_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {
            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TW_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TW_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TW_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE TW_oref(const TW_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TW_oref& operator = (const TW_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TW_oref(TW_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TW_oref& operator = (TW_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref(const TW_oref<F_other_p__, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref& operator = (const TW_oref<F_other_p__, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref(TW_oref<F_other_p__, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TW_oref& operator = (TW_oref<F_other_p__, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return (F_other_p__*)object_p_;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TW_oref<F_other_p__, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            reset_no_destroy_internal();
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, class F_options__ = F_default_object_options, b8 is_has_object_key__ = false, typename F_requirements__ = F_default_requirements>
    class TK_oref;

    template<typename F_passed_object__, class F_options__ = F_default_object_options, typename F_requirements__ = F_default_requirements>
    using TK2_oref = TK_oref<F_passed_object__, F_options__, true, F_requirements__>;



    NCPP_FORCE_INLINE F_object_key object_key_unsafe(void* oref) noexcept {

        return *(((F_object_key*)oref) - sizeof(F_object_key));
    }



    template<typename F_passed_object__, class F_options__, typename F_requirements__>
    class TK_oref<F_passed_object__, F_options__, true, F_requirements__> {

    private:
        using F_this = TK_oref<F_passed_object__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TK_oref<F_passed_object__, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_object_manager& object_manager() const noexcept { return F_object_manager::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TK_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TK_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_oref(const TK_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TK_oref(TK_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            if(object_key_.is_thread_safe)
                return F_options::template TF_manager<true>::instance().key_pool().check(object_key_);
            else
                return F_options::template TF_manager<false>::instance().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            if(object_key_.is_thread_safe)
                return !F_options::template TF_manager<true>::instance().key_pool().check(object_key_);
            else
                return !F_options::template TF_manager<false>::instance().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            object_p_ = 0;
            object_key_ = 0;

        }



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE auto no_key() const noexcept {

            return TK_oref<F_passed_object, F_options, false, F_requirements>::unsafe(object_p_);
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    template<typename F_passed_object__, class F_options__, typename F_requirements__>
    class TK_oref<F_passed_object__, F_options__, false, F_requirements__> {

    private:
        using F_this = TK_oref<F_passed_object__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TK_oref<F_passed_object__, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TK_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TK_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TK_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_oref(const TK_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TK_oref(TK_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TK_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            object_p_ = 0;

        }



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE auto with_key_unsafe() const noexcept {

            return TK_oref<F_passed_object, F_options, true, F_requirements>::unsafe(object_p_);
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = false, typename F_requirements__ = F_default_requirements>
    class TU_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_default_requirements>
    using TU2_oref = TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TU_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TU_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_object_manager& object_manager() const noexcept { return F_object_manager::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TU_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TU_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TU_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_oref(TU_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template TF_manager<true>::instance().key_pool().push(object_key_);
            else
                F_options::template TF_manager<false>::instance().key_pool().push(object_key_);
        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );

            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;
            *object_key_p = object_key_;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

            pop_key_internal();

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TU_oref T_make(F_args__&&... args) {

            TU_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TU_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TU_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TU_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TU_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TU_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TU_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_oref(TU_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TU_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );

//            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TU_oref T_make(F_args__&&... args) {

            TU_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = false, typename F_requirements__ = F_default_requirements>
    class TS_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_default_requirements>
    using TS2_oref = TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;



    NCPP_FORCE_INLINE u32 shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - 1;

        return counter_p->load(eastl::memory_order_acquire);
    }
    NCPP_FORCE_INLINE u32 increase_shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - 1;

        return counter_p->fetch_add(1, eastl::memory_order_acq_rel);
    }
    NCPP_FORCE_INLINE u32 decrease_shared_object_counter_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - 1;

        return counter_p->fetch_sub(1, eastl::memory_order_acq_rel);
    }
    NCPP_FORCE_INLINE void set_object_counter_to_one_unsafe(void* object_p) noexcept {

        au32* counter_p = ((au32*)object_p) - 1;

        counter_p->store(1, eastl::memory_order_release);
    }



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TS_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TS_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_object_manager& object_manager() const noexcept { return F_object_manager::instance(); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TS_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TS_oref() noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TS_oref(F_null) noexcept {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

        NCPP_FORCE_INLINE ~TS_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TS_oref(const TS_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TS_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(decrease_shared_object_counter_unsafe(object_p_) != 1) {

                    reset_no_destroy_internal();

                }
                else {

                    destroy_object_internal();
                    reset_no_destroy_internal();

                }

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template TF_manager<true>::instance().key_pool().push(object_key_);
            else
                F_options::template TF_manager<false>::instance().key_pool().push(object_key_);
        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            pop_key_internal();

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );
            counter_p->store(1, eastl::memory_order_release);

            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;
            *object_key_p = object_key_;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TS_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TS_oref T_make(F_args__&&... args) {

            TS_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TS_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TS_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TS_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

        }

    public:
        static NCPP_FORCE_INLINE TS_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TS_oref() noexcept = default;
        NCPP_FORCE_INLINE TS_oref(F_null) noexcept {}

        NCPP_FORCE_INLINE ~TS_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TS_oref(const TS_oref& x) noexcept :
            object_p_(x.object_p_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TS_oref&& x) noexcept :
            object_p_(x.object_p_)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        NCPP_FORCE_INLINE TS_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TS_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(decrease_shared_object_counter_unsafe(object_p_) != 1) {

                    reset_no_destroy_internal();

                }
                else {

                    destroy_object_internal();
                    reset_no_destroy_internal();

                }

            }

        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );
            counter_p->store(1, eastl::memory_order_release);

//            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TS_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TS_oref T_make(F_args__&&... args) {

            TS_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, b8 is_has_object_key__ = false, typename F_requirements__ = F_default_requirements>
    class TX_oref;

    template<typename F_passed_object__, typename F_allocator__ = mem::F_object_allocator, class F_options__ = F_default_object_options, typename F_requirements__ = F_default_requirements>
    using TX2_oref = TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__> {

    private:
        using F_this = TX_oref<F_passed_object__, F_allocator__, F_options__, true, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = true;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        using F_object_manager = F_options::template TF_manager<T_is_object_thread_safe<F_object>>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TX_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        F_object_key object_key_;
        b8 is_shared_ = false;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE F_object_manager& object_manager() const noexcept { return F_object_manager::instance(); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        NCPP_FORCE_INLINE b8 is_shared() const noexcept { return is_shared_; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TX_oref(F_passed_object* object_p, F_object_key object_key) noexcept :
            object_p_(object_p),
            object_key_(object_key)
        {

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }

    public:
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p, F_object_key object_key) noexcept {

            return { object_p, object_key };
        }
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p) noexcept {

            return { object_p, ncpp::object_key_unsafe(object_p) };
        }

    public:
        NCPP_FORCE_INLINE TX_oref() noexcept = default;
        NCPP_FORCE_INLINE TX_oref(F_null) noexcept {}

        NCPP_FORCE_INLINE ~TX_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TX_oref(const TX_oref& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TX_oref&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.is_shared_)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = x.is_shared_;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            x.reset_no_destroy_internal();

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            object_key_(x.object_key_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            NCPP_CHECK_OREF_REQUIREMENTS(this);
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            object_key_ = x.object_key_;
            is_shared_ = false;

            NCPP_CHECK_OREF_REQUIREMENTS(this);

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            if(is_shared_)
                return (object_p_ != 0);

            if(object_key_.is_thread_safe)
                return F_options::template TF_manager<true>::instance().key_pool().check(object_key_);
            else
                return F_options::template TF_manager<false>::instance().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            if(is_shared_)
                return (object_p_ == 0);

            if(object_key_.is_thread_safe)
                return !F_options::template TF_manager<true>::instance().key_pool().check(object_key_);
            else
                return !F_options::template TF_manager<false>::instance().key_pool().check(object_key_);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
            object_key_.reset();
            is_shared_ = false;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(is_shared_) {

                    if (decrease_shared_object_counter_unsafe(object_p_) != 1) {

                        reset_no_destroy_internal();

                    } else {

                        destroy_object_internal();
                        reset_no_destroy_internal();

                    }

                }
                else {

                    reset_no_destroy_internal();

                }

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = object_manager().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            if(object_key_.is_thread_safe)
                F_options::template TF_manager<true>::instance().key_pool().push(object_key_);
            else
                F_options::template TF_manager<false>::instance().key_pool().push(object_key_);
        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            pop_key_internal();

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );
            counter_p->store(1, eastl::memory_order_release);

            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;
            *object_key_p = object_key_;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

            is_shared_ = true;

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TX_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TX_oref T_make(F_args__&&... args) {

            TX_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_, object_key_ };
        }



    public:
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() const & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() const && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };



    template<typename F_passed_object__, typename F_allocator__, class F_options__, typename F_requirements__>
    class TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__> {

    private:
        using F_this = TX_oref<F_passed_object__, F_allocator__, F_options__, false, F_requirements__>;

    public:
        NCPP_OBJECT_FRIEND_CLASSES();

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_requirements = F_requirements__;

        static constexpr b8 is_has_object_key = false;
        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename F_new_requirements__>
        using TF_bind_requirements = TX_oref<F_passed_object__, F_allocator, F_options__, is_has_object_key, F_new_requirements__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_RTTI_IMPLEMENT_FLAG(F_oref_flag);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    protected:
        F_passed_object* object_p_ = 0;
        b8 is_shared_ = false;

    public:
        NCPP_FORCE_INLINE F_passed_object* object_p() const noexcept { return (F_passed_object*)object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(object_p()); }

        NCPP_FORCE_INLINE u32 object_counter() const noexcept {

            NCPP_ASSERT(object_p_) << "can't get object counter from null pointer";

            return shared_object_counter_unsafe(object_p_);
        }

        NCPP_FORCE_INLINE b8 is_shared() const noexcept { return is_shared_; }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TX_oref(F_passed_object* object_p) noexcept :
            object_p_(object_p)
        {

        }

    public:
        static NCPP_FORCE_INLINE TX_oref unsafe(F_passed_object* object_p) noexcept {

            return object_p;
        }

    public:
        NCPP_FORCE_INLINE TX_oref() noexcept = default;
        NCPP_FORCE_INLINE TX_oref(F_null) noexcept {}

        NCPP_FORCE_INLINE ~TX_oref() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TX_oref(const TX_oref& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TX_oref&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.is_shared_)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            x.reset_no_destroy_internal();

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            x.reset_no_destroy_internal();

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        NCPP_FORCE_INLINE TX_oref(TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(false)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            x.reset_no_destroy_internal();

            return *this;
        }
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_(x.object_p_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.is_shared_)
        {

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            if(is_shared_ && object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.is_shared_)
        {

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = x.is_shared_;

            x.reset_no_destroy_internal();

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TU_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                set_object_counter_to_one_unsafe(object_p_);

            x.reset_no_destroy_internal();

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            x.reset_no_destroy_internal();

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(x.object_p_ != 0)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TS_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = (x.object_p_ != 0);

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

            return *this;
        }

        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(false)
        {

            x.reset_no_destroy_internal();

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>&& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            x.reset_no_destroy_internal();

            return *this;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref(const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept :
            object_p_((F_passed_object*)x.object_p_),
            is_shared_(false)
        {

            if(object_p_)
                increase_shared_object_counter_unsafe(object_p_);

        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_other_p__, F_passed_object>
        NCPP_FORCE_INLINE TX_oref& operator = (const TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements>& x) noexcept
        {

            reset();

            object_p_ = (F_passed_object*)x.object_p_;
            is_shared_ = false;

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_OBJECT_REFERENCE_DEFINE_CAST_INTERNAL(TX_oref<F_other_p__, F_allocator, F_options, is_has_object_key, F_requirements>);

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }

        NCPP_FORCE_INLINE b8 Q_is_valid() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return true;

            return (object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 Q_is_null() const noexcept {

            if constexpr (F_requirements::is_always_valid)
                return false;

            return (object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(object_p_) {

                if(is_shared_) {

                    if (decrease_shared_object_counter_unsafe(object_p_) != 1) {

                        reset_no_destroy_internal();

                    } else {

                        destroy_object_internal();
                        reset_no_destroy_internal();

                    }

                }
                else {

                    reset_no_destroy_internal();

                }

            }

        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            au32* counter_p = (au32*)allocator.allocate(
                NCPP_OBJECT_MEMORY_HEADER_SIZE + sizeof(F_object),
                utilities::T_alignof<F_object>,
                NCPP_OBJECT_MEMORY_HEADER_SIZE,
                0
            );
            counter_p->store(1, eastl::memory_order_release);

//            F_object_key* object_key_p = ((F_object_key*)counter_p) + 1;

            object_p_ = (F_passed_object*)(counter_p + (NCPP_OBJECT_MEMORY_HEADER_SIZE / sizeof(u32)));

            new ((F_object*)object_p_) F_object(std::forward<F_args__>(args)...);

            is_shared_ = true;

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TX_oref&& operator()(F_args__&&... args) && {

            NCPP_ASSERT(!is_valid()) << "can't create object by quick \"()\" operator from a valid pointer";

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TX_oref T_make(F_args__&&... args) {

            TX_oref oref;

            oref.T_create_object(std::forward<F_args__>(args)...);

            return std::move(oref);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept;



    public:
        NCPP_FORCE_INLINE TW_oref<F_passed_object, F_requirements> weak() const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TW_oref<F_other_p__, F_requirements> () const noexcept {

            return object_p_;
        }



    public:
        NCPP_FORCE_INLINE TK_oref<F_passed_object, F_options, is_has_object_key, F_requirements> keyed() const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_down_castable<F_passed_object__, F_other_p__>
        NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }
        template<typename F_other_p__>
        requires T_is_object_up_castable<F_passed_object__, F_other_p__>
        explicit NCPP_FORCE_INLINE operator TK_oref<F_other_p__, F_options, is_has_object_key, F_requirements> () const noexcept {

            return { object_p_ };
        }



    public:
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>& shared() const & noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&)*this;
        }
        NCPP_FORCE_INLINE TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }
        NCPP_FORCE_INLINE const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&& shared() const && noexcept {

            NCPP_ASSERT(is_shared_) << "currently non-shared mode";

            return (const TS_oref<F_passed_object, F_allocator, F_options, is_has_object_key, F_requirements>&&)*this;
        }



    public:
        NCPP_FORCE_INLINE F_passed_object* operator ->() const noexcept {

            return (F_passed_object*)object_p_;
        }
        NCPP_FORCE_INLINE F_passed_object& operator *() const noexcept {

            return *((F_passed_object*)object_p_);
        }

    };

}



NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TU_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);

NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TS_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);

NCPP_BIND_CUSTOM_CPASS(
    NCPP_MA(ncpp::TX_oref<F_passed_object__, F_allocator__, F_options__, is_has_object_key__, F_requirements__>),
    NCPP_MA(ncpp::TK_oref<F_passed_object__, F_options__, is_has_object_key__, F_requirements__>),
    typename F_passed_object__,
    typename F_allocator__,
    class F_options__,
    ncpp::b8 is_has_object_key__,
    typename F_requirements__
);



#define NCPP_WTHIS() (ncpp::TW_oref<std::remove_pointer_t<decltype(this)>>::unsafe(this))

#define NCPP_KTHIS(...) (ncpp::TK_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS(...) (ncpp::TS_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS(...) (ncpp::TX_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))

#define NCPP_KTHIS2(...) (ncpp::TK2_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_STHIS2(...) (ncpp::TS2_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))
#define NCPP_XTHIS2(...) (ncpp::TX2_oref<std::remove_pointer_t<decltype(this)> __VA_OPT__(,) __VA_ARGS__>::unsafe(this))