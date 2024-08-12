#pragma once

#include <ncpp/prerequisites.hpp>
#include <ncpp/mem/pool_memory_provider.hpp>



namespace ncpp::mem {

    template<class F_adapter__, class F_heap__, sz block_size__, sz blocks_per_chunk__>
    class TA_frame_heap;
    template<class F_adapter__, class F_heap__>
    class TA_frame_memory_adapter;
    template<class F_adapter__, class F_heap__, u32 free_at_param__>
    class TF_frame_allocator;



    struct D_frame_memory_block_usage
    {
        u32 frame_memory_block_usage = 0;
    };



    using F_frame_chunk_memory_block = NCPP_COMBINE_TYPES(

        F_pool_memory_block,
        D_child_memory_block_count_u8

    );
    using F_frame_memory_block = NCPP_COMBINE_TYPES(

        F_child_pool_memory_block,
        D_frame_memory_block_usage

    );



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



    template<class F_adapter__, class F_heap__, sz block_size__ = NCPP_DEFAULT_FRAME_BLOCK_SIZE, sz blocks_per_chunk__ = NCPP_DEFAULT_FRAME_BLOCKS_PER_CHUNK>
    class TA_frame_heap {

    private:
        using F_this = TA_frame_heap<F_adapter__, F_heap__, block_size__, blocks_per_chunk__>;

    private:
        using F_heap = F_heap__;

    public:
        using F_adapter = F_adapter__;

    public:
        template<u32 free_at_param__ = 0>
        using TF_allocator = TF_frame_allocator<F_adapter, F_heap__, free_at_param__>;

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



    public:
        // implement these functions in your own frame heap class to let it works
        static NCPP_FORCE_INLINE F_this* instance_p() noexcept;
        static NCPP_FORCE_INLINE F_adapter* query_adapter() noexcept;



    private:
        F_chunk_memory_provider chunk_memory_provider_;
        F_block_memory_provider block_memory_provider_;
        eastl::vector<F_frame_chunk_memory_block*> chunk_p_vector_;

    protected:
        eastl::vector<F_adapter*> adapter_p_vector_;

    public:
        NCPP_FORCE_INLINE const auto& adapter_p_vector() const noexcept { return adapter_p_vector_; }



    public:
        TA_frame_heap()
        {
            F_frame_chunk_memory_provider_desc chunk_memory_provider_desc;
            chunk_memory_provider_desc.child_pool_memory_block_size = block_size;
            chunk_memory_provider_desc.max_child_pool_memory_block_count_per_pool_memory_block = blocks_per_chunk;
            new(&chunk_memory_provider_) F_chunk_memory_provider(chunk_memory_provider_desc);

            F_frame_memory_provider_desc block_memory_provider_desc;
            new(&block_memory_provider_) F_block_memory_provider(block_memory_provider_desc);

            block_memory_provider_.parent_memory_provider_p = &chunk_memory_provider_;
        }
        ~TA_frame_heap()
        {
            release_chunks();
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
            return chunk_memory_provider_.default_create_block(chunk_size);
        }
        F_frame_memory_block* create_block_on_chunk(F_frame_chunk_memory_block* chunk_p)
        {
            F_frame_chunk_memory_provider_management_params management_params;
            management_params.pool_memory_block_p = chunk_p;

            chunk_p->child_memory_block_count_u8++;

            return block_memory_provider_.create_block_through_parent(0, &management_params);
        }

    public:
        void release_chunks()
        {
            for(auto adapter_p : adapter_p_vector_)
                adapter_p->destroy_params();

            for(auto chunk_p : chunk_p_vector_)
            {
                chunk_memory_provider_.default_destroy_block(chunk_p);
            }
            chunk_p_vector_.clear();
        }

    protected:
        void set_uniform_param_count(u32 uniform_param_count)
        {
            for(auto adapter_p : adapter_p_vector_)
                adapter_p->set_param_count(uniform_param_count);
        }

    public:
        void reset_uniform_param(u32 uniform_param_index)
        {
            for(auto adapter_p : adapter_p_vector_)
                adapter_p->reset_param(uniform_param_index);
        }

    public:
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

    };



    template<class F_adapter__, class F_heap__>
    class TA_frame_memory_adapter {

    private:
        using F_this = TA_frame_memory_adapter<F_adapter__, F_heap__>;

    private:
        using F_adapter = F_adapter__;

    public:
        using F_heap = F_heap__;
        friend F_heap;

    public:
        template<u32 free_at_param__ = 0>
        using TF_allocator = TF_frame_allocator<F_adapter__, F_heap__, free_at_param__>;



    public:
        using F_block_list = eastl::fixed_vector<F_frame_memory_block*, 64>;



    private:
        eastl::vector<F_block_list> block_lists_;

    public:
        NCPP_FORCE_INLINE u32 param_count() const noexcept { return block_lists_.size(); }



    public:
        TA_frame_memory_adapter() = default;
        ~TA_frame_memory_adapter() = default;



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
                    return ((u8*)(block_p + 1)) + memory_offset;
                }
            }

            // create new block from heap
            F_frame_memory_block* block_p = F_heap::instance_p()->create_block();
            block_list.push_back(block_p);
            return block_p + 1;
        }

    private:
        // can be used by user defined heap class when defining param count
        void set_param_count(u32 param_count)
        {
            for(u32 i = 0; i < block_lists_.size(); ++i)
                reset_param(i);

            block_lists_.resize(param_count);
        }
        // can be used by user defined heap class when destroying param count
        void destroy_params()
        {
            set_param_count(0);
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



    public:
        void reset_param(u32 index)
        {
            auto& block_list = block_lists_[index];

            for(auto block_p : block_list)
            {
                block_p->frame_memory_block_usage = 0;
            }

            block_list.clear();
        }

    };



    template<class F_adapter__, class F_heap__, u32 free_at_param__ = 0>
    class TF_frame_allocator :
        public TA_allocator<
            TF_frame_allocator<F_adapter__, F_heap__, free_at_param__>,
            true
        >
    {

    private:
        using F_this = TF_frame_allocator<F_adapter__, F_heap__, free_at_param__>;
        using F_base = TA_allocator<F_this>;

    public:
        using F_adapter = F_adapter__;
        using F_heap = F_heap__;

    public:
        static constexpr u32 free_at_param = free_at_param__;



    public:
        NCPP_FORCE_INLINE TF_frame_allocator(const char* name = 0) noexcept :
            TA_allocator<F_this>(name)
        {
        }
        NCPP_FORCE_INLINE TF_frame_allocator(const TF_frame_allocator& x) noexcept :
            TF_frame_allocator(x.name())
        {
        }
        NCPP_FORCE_INLINE TF_frame_allocator& operator = (const TF_frame_allocator& x) noexcept
        {
#ifdef NCPP_ENABLE_ALLOCATOR_NAME
            reinterpret_cast<F_base*>(this)->set_name(x.name());
#endif

            return *this;
        }
        NCPP_FORCE_INLINE ~TF_frame_allocator() noexcept = default;



    public:
        NCPP_FORCE_INLINE void* new_mem(sz size, sz alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT, sz alignment_offset = 0) {

            return F_heap::query_adapter()->new_mem(
                free_at_param,
                size,
                alignment,
                alignment_offset
            );
        }
        NCPP_FORCE_INLINE void delete_mem(void* p) {
        }

    };

}