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

#define NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL \
            template<class F_options__>\
            friend class ncpp::TA_object_memory;               \
            template<ncpp::b8 enable_counter__, ncpp::T_is_object F_object__, class F_options__>\
            friend class ncpp::TF_object_memory;               \
                                                    \
            template<ncpp::b8 is_thread_safe__, typename F_allocator__>     \
            friend class ncpp::TF_object_key_subpool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe__, typename F_allocator__>     \
            friend class ncpp::TF_object_key_pool;                                        \
                                                    \
            template<ncpp::b8 is_thread_safe__, typename F_allocator__>     \
            friend class ncpp::TF_default_object_storage;                                        \
                                                    \
            template<ncpp::T_is_object F_object__, typename F_allocator__, b8 is_has_object_key__, class F_options__>\
            friend class ncpp::TU_object_p;\
            template<ncpp::T_is_object F_object__, typename F_allocator__, class F_options__>\
            friend class ncpp::TS_object_p;\
            template<ncpp::T_is_object F_object__, b8 is_has_object_key__, class F_options__>\
            friend class ncpp::TK_object_p;\
            template<ncpp::T_is_object F_object__>\
            friend class ncpp::TW_object_p;



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
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::TF_object_flag<__VA_ARGS__>);\
            NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL

#define NCPP_OBJECT_THREAD_SAFE \
            NCPP_RTTI_IMPLEMENT_FLAG(ncpp::F_object_thread_safe_flag);



    template<typename F_object__>
    struct TF_object_flag {};

    NCPP_RTTI_CREATE_FLAG(F_object_thread_safe_flag);

    template<typename F__>
    concept T_is_object = NCPP_RTTI_IS_HAS_FLAG(F__, TF_object_flag<F__>);
    template<typename F__>
    concept T_is_object_thread_safe = T_is_object<F__> && NCPP_RTTI_IS_HAS_FLAG(F__, F_object_thread_safe_flag);

    using F_object_id = u32;
    using F_object_generation = u32;
    struct F_object_key {

        union {

            u64 value = NCPP_U64_MAX;

            struct {

                F_object_id id;
                F_object_generation generation;

            };

        };

        NCPP_FORCE_INLINE constexpr F_object_key() noexcept = default;
        NCPP_FORCE_INLINE constexpr F_object_key(u64 value_in) noexcept :
            value(value_in)
        {}
        NCPP_FORCE_INLINE constexpr F_object_key(u32 id_in, u32 generation_in) noexcept :
            id(id_in),
            generation(generation_in)
        {}



        NCPP_FORCE_INLINE constexpr operator u64 () const noexcept {

            return value;
        }



        NCPP_FORCE_INLINE constexpr b8 is_valid() const noexcept {

            return (value != NCPP_U64_MAX);
        }
        NCPP_FORCE_INLINE constexpr b8 is_null() const noexcept {

            return (value == NCPP_U64_MAX);
        }



        NCPP_FORCE_INLINE constexpr void reset() noexcept {

            value = NCPP_U64_MAX;
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



    template<class F_options__>
    class TA_object_memory;

    template<b8 enable_counter__, T_is_object F_object__, class F_options__>
    class TF_object_memory;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_object_key_subpool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_object_key_pool;

    template<b8 is_thread_safe__, typename F_allocator__>
    class TF_default_object_storage;

    template<T_is_object F_object__>
    class TW_object_p;
    template<T_is_object F_object__, b8 is_has_object_key__, class F_options__>
    class TK_object_p;
    template<T_is_object F_object__, typename F_allocator__, b8 is_has_object_key__, class F_options__>
    class TU_object_p;
    template<T_is_object F_object__, typename F_allocator__, class F_options__>
    class TS_object_p;



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
    class TF_object_key_subpool;

    template<typename F_allocator__>
    class TF_object_key_subpool<true, F_allocator__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;



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
                    allocator.deallocate(next_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                u32* new_generation_p = (u32*)allocator.allocate(
                    sizeof(u32) * new_size,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = (u32*)allocator.allocate(
                    sizeof(u32) * new_size,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, min_size * sizeof(u32));
                    std::memcpy(new_next_p, next_p, min_size * sizeof(u32));

                    allocator.deallocate(generation_p);
                    allocator.deallocate(next_p);

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
        TF_object_key_subpool()
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
                generation

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
    class TF_object_key_subpool<false, F_allocator__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;



    public:
        static constexpr b8 is_thread_safe = false;

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

            ~F_generation_buffer(){

                mem::F_default_allocator allocator;

                if(size) {

                    allocator.deallocate(generation_p);
                    allocator.deallocate(next_p);

                }

            }

            NCPP_FORCE_INLINE void resize(u32 new_size) {

                mem::F_default_allocator allocator;

                u32* new_generation_p = (u32*)allocator.allocate(
                    sizeof(u32) * new_size,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );
                u32* new_next_p = (u32*)allocator.allocate(
                    sizeof(u32) * new_size,
                    utilities::T_alignof<u32>,
                    0,
                    0
                );

                if(size) {

                    u32 min_size = eastl::min(size, new_size);

                    std::memcpy(new_generation_p, generation_p, min_size * sizeof(u32));
                    std::memcpy(new_next_p, next_p, min_size * sizeof(u32));

                    allocator.deallocate(generation_p);
                    allocator.deallocate(next_p);

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
        NCPP_FORCE_INLINE u32 index() const noexcept { return index_; }
        NCPP_FORCE_INLINE u32 subpool_count() const noexcept { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const noexcept { return max_local_generation_count_; }



    public:
        TF_object_key_subpool()
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
                generation
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
    class TF_object_key_pool {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;



    public:
        static constexpr b8 is_thread_safe = is_thread_safe__;

        using F_allocator = F_allocator__;

        using F_subpool = TF_object_key_subpool<is_thread_safe>;



    private:
        u32 subpool_count_ = 1;
        u32 max_local_generation_count_ = 1;
        containers::TF_vector<F_subpool> subpool_vector_;

    public:
        NCPP_FORCE_INLINE u32 subpool_count() const { return subpool_count_; }
        NCPP_FORCE_INLINE u32 max_local_generation_count() const { return max_local_generation_count_; }
        NCPP_FORCE_INLINE const containers::TF_vector<F_subpool>& subpool_vector() const { return subpool_vector_; }



    public:
        TF_object_key_pool(u32 subpool_count = 1) :
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

    using F_object_key_pool = TF_object_key_pool<>;



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
    class TF_default_object_storage : public utilities::TI_singleton<TF_default_object_storage<is_thread_safe__, F_allocator__>> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;



    public:
        static constexpr b8 is_thread_safe = is_thread_safe__;

        using F_allocator = F_allocator__;

        using F_key_pool = TF_object_key_pool<is_thread_safe, F_allocator>;



    private:
        F_key_pool key_pool_;

    public:
        NCPP_FORCE_INLINE F_key_pool& key_pool() noexcept { return key_pool_; }
        NCPP_FORCE_INLINE const F_key_pool& key_pool() const noexcept { return key_pool_; }



    public:
        TF_default_object_storage(u32 subpool_count) :
            key_pool_(subpool_count)
        {

        }
        ~TF_default_object_storage(){

        }

    };

    using F_default_object_storage = TF_default_object_storage<>;



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    template<b8 is_thread_safe__ = false>
    struct TF_object_counter;

    template<>
    struct TF_object_counter<true> {

        static constexpr b8 is_thread_safe = true;
        static constexpr u8 counter_size = 4;

        using F_value = TF_atomic_uint<counter_size>;
        using F_return_value = TF_uint<counter_size>;

        F_value value = 0;

        NCPP_FORCE_INLINE F_return_value increase() noexcept {

            return value.fetch_add(1, eastl::memory_order_acq_rel);
        }
        NCPP_FORCE_INLINE F_return_value decrease() noexcept {

            return value.fetch_sub(1, eastl::memory_order_acq_rel);
        }
        NCPP_FORCE_INLINE F_return_value load() const noexcept {

            return value.load(eastl::memory_order_acquire);
        }

        NCPP_FORCE_INLINE operator F_return_value () const noexcept {

            return load();
        }
    };

    template<>
    struct TF_object_counter<false> {

        static constexpr b8 is_thread_safe = false;
        static constexpr u8 counter_size = 4;

        using F_value = TF_uint<counter_size>;
        using F_return_value = TF_uint<counter_size>;

        F_value value = 0;

        NCPP_FORCE_INLINE F_return_value increase() noexcept {

            return value++;
        }
        NCPP_FORCE_INLINE F_return_value decrease() noexcept {

            return value--;
        }
        NCPP_FORCE_INLINE F_return_value load() const noexcept {

            return value;
        }

        NCPP_FORCE_INLINE operator F_return_value () const noexcept {

            return load();
        }
    };

    using F_object_counter = TF_object_counter<>;



    template<T_is_object F_object__>
    NCPP_FORCE_INLINE TF_object_counter<T_is_object_thread_safe<F_object__>> T_object_counter(const F_object__& object) noexcept {

        return *(
            (TF_object_counter<T_is_object_thread_safe<F_object__>>*)
            (
                ((u64*)&object)
                - 1
            )
        );
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



    template<
        b8 is_storage_thread_safe__ = false,
        typename F_allocator__ = mem::F_default_allocator
    >
    struct TF_default_object_options {

        using F_this = TF_default_object_options<
            is_storage_thread_safe__,
            F_allocator__
        >;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        using F_allocator = F_allocator__;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        using F_storage = TF_default_object_storage<
            is_storage_thread_safe__,
            F_allocator__
        >;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        template<b8 is_counter_thread_safe__ = false>
        using TF_counter = TF_object_counter<
            is_counter_thread_safe__
        >;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

        using A_object_memory = TA_object_memory<F_this>;

        template<b8 enable_counter__, T_is_object F_object__>
        using TF_object_memory = TF_object_memory<enable_counter__, F_object__, F_this>;

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



    template<class F_options__ = F_default_object_options>
    class TA_object_memory {

    protected:
        NCPP_FORCE_INLINE TA_object_memory() noexcept = default;

    public:
        NCPP_FORCE_INLINE ~TA_object_memory() noexcept = default;

    };



    template<b8 enable_counter__, T_is_object F_object__, class F_options__ = F_default_object_options>
    class TF_object_memory;

    template<T_is_object F_object__, class F_options__>
    class NCPP_ALIGN(8) TF_object_memory<true, F_object__, F_options__> :
        public TA_object_memory<F_options__>
    {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        using F_this = TF_object_memory<true, F_object__, F_options__>;

        using F_object = F_object__;
        using F_options = F_options__;

        static constexpr b8 is_thread_safe = T_is_object_thread_safe<F_object__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_options::template TF_counter<is_thread_safe> shared_counter_;
        utilities::TF_mem_wrap<F_object__> object_mem_wrap_;

    public:
        NCPP_FORCE_INLINE auto shared_counter() const noexcept { return shared_counter_.load(); }
        NCPP_FORCE_INLINE F_object__* object_p() const noexcept { return (F_object__*)&object_mem_wrap_; }
        NCPP_FORCE_INLINE F_object__& object() const noexcept { return *object_p(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE TF_object_memory() noexcept = default;
        NCPP_FORCE_INLINE ~TF_object_memory() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE void T_initialize_object(F_args__&&... args) const {

            new (object_p()) F_object(std::forward<F_args__>(args)...);

        }
        NCPP_FORCE_INLINE void deinitialize_object() const noexcept {

            object_p()->~F_object();

        }

    };

    template<T_is_object F_object__, class F_options__>
    class TF_object_memory<false, F_object__, F_options__> :
        public TA_object_memory<F_options__>
    {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        using F_this = TF_object_memory<false, F_object__, F_options__>;

        using F_object = F_object__;
        using F_options = F_options__;

        static constexpr b8 is_thread_safe = T_is_object_thread_safe<F_object__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        utilities::TF_mem_wrap<F_object__> object_mem_wrap_;

    public:
        NCPP_FORCE_INLINE F_object__* object_p() const noexcept { return (F_object__*)&object_mem_wrap_; }
        NCPP_FORCE_INLINE F_object__& object() const noexcept { return *object_p(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        NCPP_FORCE_INLINE TF_object_memory() noexcept = default;
        NCPP_FORCE_INLINE ~TF_object_memory() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<typename... F_args__>
        NCPP_FORCE_INLINE void T_initialize_object(F_args__&&... args) const {

            new (object_p()) F_object(std::forward<F_args__>(args)...);

        }
        NCPP_FORCE_INLINE void deinitialize_object() const noexcept {

            object_p()->~F_object();

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



    template<typename F1__, typename F2__>
    concept T_is_object_down_castable = T_is_object<F1__> && T_is_object<F2__> && requires(F1__* p1, F2__* p2) {
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



    template<T_is_object F_passed_object__>
    class TW_object_p {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        static constexpr b8 is_const = std::is_const_v<F_passed_object__>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_passed_object* raw_object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* raw_object_p() const noexcept { return (F_passed_object*)raw_object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(raw_object_p()); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TW_object_p(F_passed_object* raw_object_p) noexcept :
            raw_object_p_(raw_object_p)
        {

        }

    public:
        NCPP_FORCE_INLINE TW_object_p() noexcept = default;

        template<b8 enable_counter__, T_is_object F_other__, class F_options>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p(const TF_object_memory<enable_counter__, F_other__, F_options>& object_memory) noexcept :
            raw_object_p_(object_memory.object_p())
        {

        }
        template<b8 enable_counter__, T_is_object F_other__, class F_options>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p& operator = (const TF_object_memory<enable_counter__, F_other__, F_options>& object_memory) noexcept {

            raw_object_p_ = object_memory.object_p();

            return *this;
        }

        NCPP_FORCE_INLINE TW_object_p(const TW_object_p& x) noexcept :
            raw_object_p_(x.raw_object_p_)
        {

        }
        NCPP_FORCE_INLINE TW_object_p& operator = (const TW_object_p& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            return *this;
        }

        NCPP_FORCE_INLINE TW_object_p(TW_object_p&& x) noexcept :
            raw_object_p_(x.raw_object_p_)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TW_object_p& operator = (TW_object_p&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p(const TW_object_p<F_other__>& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_)
        {

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p& operator = (const TW_object_p<F_other__>& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p(TW_object_p<F_other__>&& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_)
        {

            x.reset_no_destroy_internal();

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TW_object_p& operator = (TW_object_p<F_other__>&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object, F_other__>
        explicit NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return (F_other__*)raw_object_p_;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        NCPP_FORCE_INLINE TW_object_p<F_other__> T_cast() const noexcept {

            return (F_other__*)raw_object_p_;
        }

        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            return (raw_object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            return (raw_object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            raw_object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            reset_no_destroy_internal();
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



    template<T_is_object F_passed_object__, b8 is_has_object_key__ = true, class F_options__ = F_default_object_options>
    class TK_object_p;



    template<T_is_object F_passed_object__, class F_options__>
    class TK_object_p<F_passed_object__, true, F_options__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_object_memory = TF_object_memory<false, F_passed_object, F_options>;

        static constexpr b8 is_has_object_key = true;

        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        template<T_is_object F_other__>
        using TF_change_object = TK_object_p<F_other__, is_has_object_key, F_options>;

        using F_with_object_key = TK_object_p<F_passed_object__, true, F_options>;
        using F_no_object_key = TK_object_p<F_passed_object__, false, F_options>;

        using W_object_p = TW_object_p<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_passed_object* raw_object_p_ = 0;
        F_object_key object_key_;

    public:
        NCPP_FORCE_INLINE F_passed_object* raw_object_p() const noexcept { return (F_passed_object*)raw_object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(raw_object_p()); }

        NCPP_FORCE_INLINE F_object_memory* object_memory_p() const noexcept { return (F_object_memory*)raw_object_p_; }
        NCPP_FORCE_INLINE F_object_memory& object_memory() const noexcept { return *object_memory_p(); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE typename F_options::F_storage& object_storage() const { return F_options::F_storage::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_object_p(F_passed_object* raw_object_p, F_object_key object_key) noexcept :
            raw_object_p_(raw_object_p),
            object_key_(object_key)
        {

        }

    public:
        NCPP_FORCE_INLINE TK_object_p() noexcept = default;
        NCPP_FORCE_INLINE ~TK_object_p() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_object_p(const TK_object_p& x) noexcept :
            raw_object_p_(x.raw_object_p_),
            object_key_(x.object_key_)
        {

        }
        NCPP_FORCE_INLINE TK_object_p& operator = (const TK_object_p& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            return *this;
        }

        NCPP_FORCE_INLINE TK_object_p(TK_object_p&& x) noexcept :
            raw_object_p_(x.raw_object_p_),
            object_key_(x.object_key_)
        {

            x.reset();

        }
        NCPP_FORCE_INLINE TK_object_p& operator = (TK_object_p&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            x.reset();

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p(const TF_change_object<F_other__>& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_),
            object_key_(x.object_key_)
        {

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p& operator = (const TF_change_object<F_other__>& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p(TF_change_object<F_other__>&& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_),
            object_key_(x.object_key_)
        {

            x.reset();

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p& operator = (TF_change_object<F_other__>&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            x.reset();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        NCPP_FORCE_INLINE const TF_change_object<F_other__>& T_cast() const noexcept {

            return *((const TF_change_object<F_other__>*)this);
        }

        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            return object_storage().key_pool().check(object_key_);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            return !object_storage().key_pool().check(object_key_);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            raw_object_p_ = 0;
            object_key_ = 0;

        }



    public:
        NCPP_FORCE_INLINE W_object_p weak_p() const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object, F_other__>
        NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object, F_other__>
        explicit NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }

    };



    template<T_is_object F_passed_object__, class F_options__>
    class TK_object_p<F_passed_object__, false, F_options__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_options = F_options__;

        using F_object_memory = TF_object_memory<false, F_passed_object, F_options>;

        static constexpr b8 is_has_object_key = false;

        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        template<T_is_object F_other__>
        using TF_change_object = TK_object_p<F_other__, is_has_object_key, F_options>;

        using F_with_object_key = TK_object_p<F_passed_object__, true, F_options>;
        using F_no_object_key = TK_object_p<F_passed_object__, false, F_options>;

        using W_object_p = TW_object_p<F_passed_object>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_passed_object* raw_object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* raw_object_p() const noexcept { return (F_passed_object*)raw_object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(raw_object_p()); }

        NCPP_FORCE_INLINE F_object_memory* object_memory_p() const noexcept { return (F_object_memory*)raw_object_p_; }
        NCPP_FORCE_INLINE F_object_memory& object_memory() const noexcept { return *object_memory_p(); }

        NCPP_FORCE_INLINE typename F_options::F_storage& object_storage() const { return F_options::F_storage::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TK_object_p(F_passed_object* raw_object_p) noexcept :
            raw_object_p_(raw_object_p)
        {

        }

    public:
        NCPP_FORCE_INLINE TK_object_p() noexcept = default;
        NCPP_FORCE_INLINE ~TK_object_p() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TK_object_p(const TK_object_p& x) noexcept :
            raw_object_p_(x.raw_object_p_)
        {

        }
        NCPP_FORCE_INLINE TK_object_p& operator = (const TK_object_p& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            return *this;
        }

        NCPP_FORCE_INLINE TK_object_p(TK_object_p&& x) noexcept :
            raw_object_p_(x.raw_object_p_)
        {

            x.reset();

        }
        NCPP_FORCE_INLINE TK_object_p& operator = (TK_object_p&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset();

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p(const TF_change_object<F_other__>& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_)
        {

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p& operator = (const TF_change_object<F_other__>& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p(TF_change_object<F_other__>&& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_)
        {

            x.reset();

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TK_object_p& operator = (TF_change_object<F_other__>&& x) noexcept
        {

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        NCPP_FORCE_INLINE const TF_change_object<F_other__>& T_cast() const noexcept {

            return *((const TF_change_object<F_other__>*)this);
        }

        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            return (raw_object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            return (raw_object_p_ == 0);
        }



    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            raw_object_p_ = 0;

        }



    public:
        NCPP_FORCE_INLINE W_object_p weak_p() const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object, F_other__>
        NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object, F_other__>
        explicit NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
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



    template<T_is_object F_passed_object__, typename F_allocator__ = mem::F_object_allocator, b8 is_has_object_key__ = true, class F_options__ = F_default_object_options>
    class TU_object_p;



    template<T_is_object F_passed_object__, typename F_allocator__, class F_options__>
    class TU_object_p<F_passed_object__, F_allocator__, true, F_options__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_object_memory = TF_object_memory<false, F_passed_object, F_options>;

        static constexpr b8 is_has_object_key = true;

        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        template<T_is_object F_other__>
        using TF_change_object = TU_object_p<F_other__, F_allocator, is_has_object_key, F_options>;

        using F_with_object_key = TU_object_p<F_passed_object__, F_allocator, true, F_options>;
        using F_no_object_key = TU_object_p<F_passed_object__, F_allocator, false, F_options>;

        using W_object_p = TW_object_p<F_passed_object__>;
        using K_object_p = TK_object_p<F_passed_object__, is_has_object_key, F_options>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_passed_object* raw_object_p_ = 0;
        F_object_key object_key_;

    public:
        NCPP_FORCE_INLINE F_passed_object* raw_object_p() const noexcept { return (F_passed_object*)raw_object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(raw_object_p()); }

        NCPP_FORCE_INLINE F_object_memory* object_memory_p() const noexcept { return (F_object_memory*)raw_object_p_; }
        NCPP_FORCE_INLINE F_object_memory& object_memory() const noexcept { return *object_memory_p(); }

        NCPP_FORCE_INLINE F_object_key object_key() const noexcept { return object_key_; }

        NCPP_FORCE_INLINE typename F_options::F_storage& object_storage() const { return F_options::F_storage::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_object_p(F_passed_object* raw_object_p, F_object_key object_key) noexcept :
            raw_object_p_(raw_object_p),
            object_key_(object_key)
        {

        }

    public:
        NCPP_FORCE_INLINE TU_object_p() noexcept = default;
        NCPP_FORCE_INLINE ~TU_object_p() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_object_p(TU_object_p&& x) noexcept :
            raw_object_p_(x.raw_object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TU_object_p& operator = (TU_object_p&& x) noexcept
        {

            reset();

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TU_object_p(TF_change_object<F_other__>&& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_),
            object_key_(x.object_key_)
        {

            x.reset_no_destroy_internal();

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TU_object_p& operator = (TF_change_object<F_other__>&& x) noexcept
        {

            reset();

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;
            object_key_ = x.object_key_;

            x.reset_no_destroy_internal();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        NCPP_FORCE_INLINE const TF_change_object<F_other__>& T_cast() const noexcept {

            return *((const TF_change_object<F_other__>*)this);
        }

        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            return (raw_object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            return (raw_object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            raw_object_p_ = 0;
            object_key_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(raw_object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    private:
        NCPP_FORCE_INLINE void pop_key_internal() noexcept {

            object_key_ = object_storage().key_pool().pop();
        }
        NCPP_FORCE_INLINE void push_key_internal() noexcept {

            object_storage().key_pool().push(object_key_);
        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            raw_object_p_ = (F_passed_object*)allocator.allocate(
                sizeof(F_object),
                utilities::T_alignof<F_object>,
                0,
                0
            );

            new ((F_object*)raw_object_p_) F_object(std::forward<F_args__>(args)...);

            pop_key_internal();

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_object_p&& operator()(F_args__&&... args) {

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TU_object_p T_make(F_args__&&... args) {

            TU_object_p object_p;

            object_p.T_create_object(std::forward<F_args__>(args)...);

            return std::move(object_p);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept {

            push_key_internal();

            F_allocator allocator;

            ((F_object*)raw_object_p_)->~F_object();

            allocator.deallocate(raw_object_p_);

        }



    public:
        NCPP_FORCE_INLINE W_object_p weak_p() const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object__, F_other__>
        NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object__, F_other__>
        explicit NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }



    public:
        NCPP_FORCE_INLINE K_object_p keyed_p() const noexcept {

            return { raw_object_p_, object_key_ };
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object__, F_other__>
        NCPP_FORCE_INLINE operator TK_object_p<F_other__> () const noexcept {

            return { raw_object_p_, object_key_ };
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object__, F_other__>
        explicit NCPP_FORCE_INLINE operator TK_object_p<F_other__> () const noexcept {

            return { raw_object_p_, object_key_ };
        }

    };



    template<T_is_object F_passed_object__, typename F_allocator__, class F_options__>
    class TU_object_p<F_passed_object__, F_allocator__, false, F_options__> {

    public:
        NCPP_OBJECT_POINTER_FRIEND_CLASSES_INTERNAL;

        using F_passed_object = F_passed_object__;
        using F_object = std::remove_const_t<F_passed_object__>;

        using F_allocator = F_allocator__;
        using F_options = F_options__;

        using F_object_memory = TF_object_memory<false, F_passed_object, F_options>;

        static constexpr b8 is_has_object_key = false;

        static constexpr b8 is_const = std::is_const_v<F_passed_object>;

        template<T_is_object F_other__>
        using TF_change_object = TU_object_p<F_other__, F_allocator, is_has_object_key, F_options>;

        using F_with_object_key = TU_object_p<F_passed_object__, F_allocator, true, F_options>;
        using F_no_object_key = TU_object_p<F_passed_object__, F_allocator, false, F_options>;

        using W_object_p = TW_object_p<F_passed_object__>;
        using K_object_p = TK_object_p<F_passed_object__, is_has_object_key, F_options>;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        F_passed_object* raw_object_p_ = 0;

    public:
        NCPP_FORCE_INLINE F_passed_object* raw_object_p() const noexcept { return (F_passed_object*)raw_object_p_; }
        NCPP_FORCE_INLINE F_passed_object& object() const noexcept { return *(raw_object_p()); }

        NCPP_FORCE_INLINE F_object_memory* object_memory_p() const noexcept { return (F_object_memory*)raw_object_p_; }
        NCPP_FORCE_INLINE F_object_memory& object_memory() const noexcept { return *object_memory_p(); }

        NCPP_FORCE_INLINE typename F_options::F_storage& object_storage() const { return F_options::F_storage::instance(); }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    private:
        NCPP_FORCE_INLINE TU_object_p(F_passed_object* raw_object_p) noexcept :
            raw_object_p_(raw_object_p)
        {

        }

    public:
        NCPP_FORCE_INLINE TU_object_p() noexcept = default;
        NCPP_FORCE_INLINE ~TU_object_p() noexcept {

            reset();
        }

        NCPP_FORCE_INLINE TU_object_p(TU_object_p&& x) noexcept :
            raw_object_p_(x.raw_object_p_)
        {

            x.reset_no_destroy_internal();

        }
        NCPP_FORCE_INLINE TU_object_p& operator = (TU_object_p&& x) noexcept
        {

            reset();

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TU_object_p(TF_change_object<F_other__>&& x) noexcept :
            raw_object_p_((F_passed_object*)x.raw_object_p_)
        {

            x.reset_no_destroy_internal();

        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_other__, F_passed_object>
        NCPP_FORCE_INLINE TU_object_p& operator = (TF_change_object<F_other__>&& x) noexcept
        {

            reset();

            raw_object_p_ = (F_passed_object*)x.raw_object_p_;

            x.reset_no_destroy_internal();

            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    public:
        template<T_is_object F_other__>
        NCPP_FORCE_INLINE const TF_change_object<F_other__>& T_cast() const noexcept {

            return *((const TF_change_object<F_other__>*)this);
        }

        NCPP_FORCE_INLINE b8 is_valid() const noexcept {

            return (raw_object_p_ != 0);
        }
        NCPP_FORCE_INLINE b8 is_null() const noexcept {

            return (raw_object_p_ == 0);
        }



    private:
        NCPP_FORCE_INLINE void reset_no_destroy_internal() noexcept {

            raw_object_p_ = 0;
        }

    public:
        NCPP_FORCE_INLINE void reset() noexcept {

            if(raw_object_p_) {

                destroy_object_internal();
                reset_no_destroy_internal();

            }

        }



    public:
        template<typename... F_args__>
        inline void T_create_object(F_args__&&... args) {

            F_allocator allocator;

            raw_object_p_ = (F_passed_object*)allocator.allocate(
                sizeof(F_object),
                utilities::T_alignof<F_object>,
                0,
                0
            );

            new ((F_object*)raw_object_p_) F_object(std::forward<F_args__>(args)...);

        }
        template<typename... F_args__>
        NCPP_FORCE_INLINE TU_object_p&& operator()(F_args__&&... args) {

            T_create_object(std::forward<F_args__>(args)...);

            return std::move(*this);
        }

        template<typename... F_args__>
        static NCPP_FORCE_INLINE TU_object_p T_make(F_args__&&... args) {

            TU_object_p object_p;

            object_p.T_create_object(std::forward<F_args__>(args)...);

            return std::move(object_p);
        }

    private:
        NCPP_FORCE_INLINE void destroy_object_internal() noexcept {

            F_allocator allocator;

            ((F_object*)raw_object_p_)->~F_object();

            allocator.deallocate(raw_object_p_);

        }



    public:
        NCPP_FORCE_INLINE W_object_p weak_p() const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object__, F_other__>
        NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object__, F_other__>
        explicit NCPP_FORCE_INLINE operator TW_object_p<F_other__> () const noexcept {

            return raw_object_p_;
        }



    public:
        NCPP_FORCE_INLINE K_object_p keyed_p() const noexcept {

            return { raw_object_p_ };
        }
        template<T_is_object F_other__>
        requires T_is_object_down_castable<F_passed_object__, F_other__>
        NCPP_FORCE_INLINE operator TK_object_p<F_other__> () const noexcept {

            return { raw_object_p_ };
        }
        template<T_is_object F_other__>
        requires T_is_object_up_castable<F_passed_object__, F_other__>
        explicit NCPP_FORCE_INLINE operator TK_object_p<F_other__> () const noexcept {

            return { raw_object_p_ };
        }

    };



    template<
        T_is_object F_passed_object__,
        typename F_allocator__ = mem::F_object_allocator,
        b8 is_has_object_key__ = true,
        class F_options__ = F_default_object_options,
        typename... F_args__
    >
    NCPP_FORCE_INLINE TU_object_p<
        F_passed_object__,
        F_allocator__,
        is_has_object_key__,
        F_options__
    > T_make_unique_object(F_args__&&... args) {

        TU_object_p<
            F_passed_object__,
            F_allocator__,
            is_has_object_key__,
            F_options__
        > object_p;

        object_p.T_create_object(std::forward<F_args__>(args)...);

        return std::move(object_p);
    }

}