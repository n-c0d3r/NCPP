#pragma once

#include <ncpp/prerequisites.hpp>
#include <ncpp/mem/pool_memory_provider.hpp>



namespace ncpp::mem {

    template<class F_heap__, sz block_size__, sz blocks_per_chunk__>
    class TA_frame_heap;
    template<class F_heap__>
    class TF_frame_memory_adapter;
    template<class F_heap__>
    class TF_frame_allocator;



    using F_frame_param = u32;
    using F_frame_param_generation = u32;



    struct D_frame_memory_block_usage
    {
        u32 frame_memory_block_usage = 0;
    };
#ifdef NCPP_ENABLE_MEMORY_COUNTING
    struct D_frame_memory_block_usable_usage
    {
        u32 frame_memory_block_usable_usage = 0;
    };
#endif



    using F_frame_chunk_memory_block = NCPP_COMBINE_TYPES(

        F_pool_memory_block,
        D_child_memory_block_count_u8

    );
#ifdef NCPP_ENABLE_MEMORY_COUNTING
    using F_frame_memory_block = NCPP_COMBINE_TYPES(

        F_child_pool_memory_block,
        D_frame_memory_block_usage,
        D_frame_memory_block_usable_usage

    );
#else
    using F_frame_memory_block = NCPP_COMBINE_TYPES(

        F_child_pool_memory_block,
        D_frame_memory_block_usage

    );
#endif



    using F_frame_chunk_memory_provider_desc = NCPP_COMBINE_TYPES(

        F_pool_memory_provider_desc

    );
    using F_frame_memory_provider_desc = NCPP_COMBINE_TYPES(
    );



    using F_frame_chunk_memory_provider_management_params = NCPP_COMBINE_TYPES(

        F_pool_memory_provider_management_params

    );
    using F_frame_memory_provider_management_params = NCPP_COMBINE_TYPES(
    );



    template<class F_heap__, sz block_size__ = NCPP_DEFAULT_FRAME_BLOCK_SIZE, sz blocks_per_chunk__ = NCPP_DEFAULT_FRAME_BLOCKS_PER_CHUNK>
    class TA_frame_heap {

    private:
        using F_this = TA_frame_heap<F_heap__, block_size__, blocks_per_chunk__>;

    private:
        using F_heap = F_heap__;

    public:
        using F_adapter = TF_frame_memory_adapter<F_heap>;
        template<class F_heap_fr__>
        friend class ncpp::mem::TF_frame_memory_adapter;

        using F_allocator = TF_frame_allocator<F_heap__>;

        static constexpr sz block_size = block_size__;
        static constexpr sz block_payload_size = block_size - sizeof(F_frame_memory_block);
        static constexpr sz blocks_per_chunk = blocks_per_chunk__;
        static constexpr sz chunk_payload_size = block_size * blocks_per_chunk;
        static constexpr sz chunk_size = sizeof(F_frame_chunk_memory_block) + chunk_payload_size;

        NCPP_STATIC_ASSERT(blocks_per_chunk__ <= 0xFF);



    public:
        using F_chunk_memory_provider = TF_pool_memory_provider<
            F_invalid_memory_provider,
            F_frame_chunk_memory_block,
            F_frame_memory_block,
            F_frame_chunk_memory_provider_desc,
            F_frame_chunk_memory_provider_management_params
        >;
        using F_block_memory_provider = TF_memory_provider<
            F_chunk_memory_provider,
            F_frame_memory_block,
            F_default_memory_block,
            F_frame_memory_provider_desc,
            F_frame_memory_provider_management_params
        >;



    private:
        F_chunk_memory_provider chunk_memory_provider_;
        F_block_memory_provider block_memory_provider_;
        eastl::vector<F_frame_chunk_memory_block*> chunk_p_vector_;

    private:
        F_frame_param param_count_ = 0;
        eastl::vector<F_frame_param_generation> param_generations_;
        eastl::vector<F_adapter*> adapter_p_vector_;

    public:
        NCPP_FORCE_INLINE F_frame_param param_count() const noexcept { return param_count_; }
        NCPP_FORCE_INLINE const auto& param_generations() const noexcept { return param_generations_; }
        NCPP_FORCE_INLINE const auto& adapter_p_vector() const noexcept { return adapter_p_vector_; }



    public:
        TA_frame_heap(u32 param_count = 1, u32 adapter_count = 1) :
            param_count_(param_count),
            param_generations_(param_count),
            adapter_p_vector_(adapter_count)
        {
            F_frame_chunk_memory_provider_desc chunk_memory_provider_desc;
            chunk_memory_provider_desc.child_pool_memory_block_size = block_size;
            chunk_memory_provider_desc.max_child_pool_memory_block_count_per_pool_memory_block = blocks_per_chunk;
            new(&chunk_memory_provider_) F_chunk_memory_provider(chunk_memory_provider_desc);

            F_frame_memory_provider_desc block_memory_provider_desc;
            new(&block_memory_provider_) F_block_memory_provider(block_memory_provider_desc);

            block_memory_provider_.parent_memory_provider_p = &chunk_memory_provider_;

            // create adapters
            for(auto& generation : param_generations_)
                generation = 0;

            // create adapters
            for(F_adapter*& adapter_p : adapter_p_vector_)
                adapter_p = new F_adapter((F_heap*)this);
        }
        ~TA_frame_heap()
        {
            release_chunks();

            // destroy adapters
            for(auto adapter_p : adapter_p_vector_)
                delete adapter_p;
            adapter_p_vector_.clear();
        }



    private:
        F_frame_chunk_memory_block* optain_chunk()
        {
            // try optain pre-created chunks
            for(auto it = chunk_p_vector_.rbegin(); it != chunk_p_vector_.rend(); ++it)
            {
                if((*it)->child_memory_block_count_u8 < blocks_per_chunk)
                    return *it;
            }

            // create new chunk
            F_frame_chunk_memory_block* chunk_p = chunk_memory_provider_.default_create_block(chunk_size);
            chunk_p_vector_.push_back(chunk_p);
            return chunk_p;
        }
        F_frame_memory_block* create_block_on_chunk(F_frame_chunk_memory_block* chunk_p)
        {
            F_frame_chunk_memory_provider_management_params management_params;
            management_params.pool_memory_block_p = chunk_p;

            chunk_p->child_memory_block_count_u8++;

            return block_memory_provider_.create_block_through_parent(0, &management_params);
        }

    private:
        F_frame_memory_block* create_block()
        {
            F_frame_chunk_memory_block* chunk_p = optain_chunk();

            return create_block_on_chunk(chunk_p);
        }
        void destroy_block(F_frame_memory_block* block_p)
        {
            F_frame_chunk_memory_block* chunk_p = (F_frame_chunk_memory_block*)(block_p->parent_memory_block_p);

            F_frame_chunk_memory_provider_management_params management_params;
            management_params.pool_memory_block_p = chunk_p;

            chunk_p->child_memory_block_count_u8--;

            chunk_memory_provider_.deallocate_child_block(block_p, &management_params);
        }



    public:
        void release_chunks()
        {
            for(auto adapter_p : adapter_p_vector_)
                adapter_p->reset_params();

            for(auto chunk_p : chunk_p_vector_)
            {
                chunk_memory_provider_.default_destroy_block(chunk_p);
            }
            chunk_p_vector_.clear();
        }

    public:
        void reset_param(F_frame_param param)
        {
            for(auto adapter_p : adapter_p_vector_)
                adapter_p->reset_param(param);

            ++(param_generations_[param]);
        }
        void reset_params()
        {
            for(u32 i = 0; i < param_count_; ++i)
                reset_param(i);
        }

    };



    template<class F_heap__>
    class TF_frame_memory_adapter {

    private:
        using F_this = TF_frame_memory_adapter<F_heap__>;

    public:
        using F_heap = F_heap__;
        template<class F_heap_fr__, sz block_size_fr__, sz blocks_per_chunk_fr__>
        friend class ncpp::mem::TA_frame_heap;

    public:
        using TF_allocator = TF_frame_allocator<F_heap__>;



    public:
        using F_block_list = eastl::fixed_vector<F_frame_memory_block*, 64>;



    private:
        F_heap* heap_p_ = 0;
        eastl::vector<F_block_list> block_lists_;

    public:
        NCPP_FORCE_INLINE F_heap* heap_p() const noexcept { return heap_p_; }



    protected:
        TF_frame_memory_adapter(F_heap* heap_p) :
            heap_p_(heap_p),
            block_lists_(heap_p->param_count())
        {
        }

    public:
        ~TF_frame_memory_adapter()
        {
            reset_params();
        }



    private:
        void* optain_memory(u32 block_list_index, u32 required_free_size = 0)
        {
            NCPP_ASSERT(block_lists_.size() > block_list_index) << "block list is not created";

            auto& block_list = block_lists_[block_list_index];

            // if block list is not empty, try optain a block from it
            if(block_list.size())
            {
                F_frame_memory_block* block_p = block_list.back();

                u32 memory_offset = block_p->frame_memory_block_usage;
                u32 free_size = F_heap::block_payload_size - memory_offset;

                if(free_size >= required_free_size)
                {
                    block_p->frame_memory_block_usage += required_free_size;

#ifdef NCPP_ENABLE_MEMORY_COUNTING
                    block_p->frame_memory_block_usable_usage += increase_usable_allocated_memory_by_actual_size(required_free_size);
#endif

                    return ((u8*)(block_p + 1)) + memory_offset;
                }
            }

            // create new block from heap
            F_frame_memory_block* block_p = heap_p_->create_block();
            block_list.push_back(block_p);

            block_p->frame_memory_block_usage = required_free_size;

#ifdef NCPP_ENABLE_MEMORY_COUNTING
            block_p->frame_memory_block_usable_usage += increase_usable_allocated_memory_by_actual_size(required_free_size);
#endif

            return block_p + 1;
        }

    private:
        void reset_param(F_frame_param param)
        {
            auto& block_list = block_lists_[param];

            for(auto block_p : block_list)
            {
                block_p->frame_memory_block_usage = 0;

#ifdef NCPP_ENABLE_MEMORY_COUNTING
                decrease_usable_allocated_memory(block_p->frame_memory_block_usable_usage);
                block_p->frame_memory_block_usable_usage = 0;
#endif

                heap_p_->destroy_block(block_p);
            }

            block_list.clear();
        }
        void reset_params()
        {
            for(u32 i = 0; i < block_lists_.size(); ++i)
                reset_param(i);
        }



    public:
        NCPP_FORCE_INLINE void* new_mem(u32 block_list_index, sz size, sz alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT, sz alignment_offset = 0) {

            sz actual_size = size + alignment;

            void* raw_memory_p = optain_memory(block_list_index, actual_size);

            return (void*)(
                align_address(
                    reinterpret_cast<uintptr_t>(raw_memory_p) + alignment_offset,
                    alignment
                ) - alignment_offset
            );
        }

    };



    template<class F_heap__>
    class TF_frame_allocator :
        public TA_allocator<
            TF_frame_allocator<F_heap__>,
            true
        >
    {

    private:
        using F_this = TF_frame_allocator<F_heap__>;
        using F_base = TA_allocator<F_this, true>;

    public:
        using F_heap = F_heap__;
        using F_adapter = typename F_heap::F_adapter;



    private:
        F_adapter* adapter_p_ = 0;
        F_frame_param param_ = 0;

    public:
        NCPP_FORCE_INLINE F_adapter* adapter_p() const noexcept { return adapter_p_; }
        NCPP_FORCE_INLINE F_frame_param param() const noexcept { return param_; }



    public:
        NCPP_FORCE_INLINE TF_frame_allocator(const char* name = 0) noexcept :
            TA_allocator<F_this, true>(name)
        {
        }
        NCPP_FORCE_INLINE TF_frame_allocator(F_adapter* adapter_p, F_frame_param param = 0, const char* name = 0) noexcept :
            TA_allocator<F_this, true>(name),
            adapter_p_(adapter_p),
            param_(param)
        {
        }
        NCPP_FORCE_INLINE TF_frame_allocator(const TF_frame_allocator& x) noexcept :
            TF_frame_allocator(x.adapter_p_, x.param_, x.name())
        {
        }
        NCPP_FORCE_INLINE TF_frame_allocator& operator = (const TF_frame_allocator& x) noexcept
        {
            adapter_p_ = x.adapter_p_;
            param_ = x.param_;

#ifdef NCPP_ENABLE_ALLOCATOR_INFO
            reinterpret_cast<F_base*>(this)->set_name(x.name());
#endif

            return *this;
        }
        NCPP_FORCE_INLINE ~TF_frame_allocator() noexcept = default;



    public:
        NCPP_FORCE_INLINE b8 operator==(const TF_frame_allocator& x) const noexcept {

            return (param_ == x.param_);
        }



    public:
        NCPP_FORCE_INLINE void* new_mem(sz size, sz alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT, sz alignment_offset = 0) {

            NCPP_ASSERT(adapter_p_) << "invalid adapter";

            return adapter_p_->new_mem(
                param_,
                size,
                alignment,
                alignment_offset
            );
        }
        NCPP_FORCE_INLINE void delete_mem(void* p) {
        }

    };

}