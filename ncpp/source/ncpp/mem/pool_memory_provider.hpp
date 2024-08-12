#pragma once

/** @file ncpp/mem/pool_memory_provider.hpp
*	@brief Implements pool memory provider.
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

#include <ncpp/mem/memory_provider.hpp>
#include <ncpp/mem/linked_memory_provider.hpp>

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

    namespace mem {

        struct D_available_memory_block_linked_list {

            F_linked_memory_block_list available_memory_block_linked_list;

        };
        struct D_available_memory_block_linked_node {

            F_linked_memory_block_node available_memory_block_linked_node;

        };
        struct D_child_pool_memory_block_initialized_count {

            sz child_pool_memory_block_initialized_count = 0;

        };

        using F_pool_memory_block = NCPP_COMBINE_TYPES(

            F_linked_memory_block,

            D_child_memory_block_linked_list,
            D_available_memory_block_linked_list,
            D_child_pool_memory_block_initialized_count

        );
        using F_child_pool_memory_block = NCPP_COMBINE_TYPES(

            D_available_memory_block_linked_node,
            D_parent_memory_block_p

        );



        struct D_child_pool_memory_block_size {

            sz child_pool_memory_block_size = 0;

        };
        struct D_max_child_pool_memory_block_count_per_pool_memory_block {

            sz max_child_pool_memory_block_count_per_pool_memory_block = 0;

        };

        using F_pool_memory_provider_desc = NCPP_COMBINE_TYPES(

            F_linked_memory_provider_desc,

            D_child_pool_memory_block_size,
            D_max_child_pool_memory_block_count_per_pool_memory_block

        );



        struct D_pool_memory_block_p {

            void* pool_memory_block_p = 0;

        };

        using F_pool_memory_provider_management_params = NCPP_COMBINE_TYPES(

            D_pool_memory_block_p

        );



        template<
            class F_parent_memory_provider__ = F_invalid_memory_provider,
            typename F_memory_block__ = F_pool_memory_block,
            typename F_child_memory_block__ = F_child_pool_memory_block,
            typename F_memory_provider_desc__ = F_pool_memory_provider_desc,
            typename F_memory_provider_management_params__ = F_pool_memory_provider_management_params
        >
        class TF_pool_memory_provider :
            public TF_memory_provider<
                F_parent_memory_provider__,
                F_memory_block__,
                F_child_memory_block__,
                F_memory_provider_desc__,
                F_memory_provider_management_params__
            >
        {

        private:
            using F_base = TF_memory_provider<
                F_parent_memory_provider__,
                F_memory_block__,
                F_child_memory_block__,
                F_memory_provider_desc__,
                F_memory_provider_management_params__
            >;

        public:
            using typename F_base::F_parent_memory_provider;
            using typename F_base::F_memory_block;
            using typename F_base::F_memory_provider_desc;
            using typename F_base::F_memory_provider_management_params;

            using typename F_base::F_child_memory_block;

        public:
            using typename F_base::F_parent_memory_provider_management_params;



        public:
            NCPP_REQUIRE_COMBINED(F_memory_block, F_pool_memory_block);
            NCPP_REQUIRE_COMBINED(F_memory_provider_desc, F_pool_memory_provider_desc);
            NCPP_REQUIRE_COMBINED(F_memory_provider_management_params, F_pool_memory_provider_management_params);

            NCPP_REQUIRE_COMBINED(F_child_memory_block, F_child_pool_memory_block);



        public:
            static void process_child_provider_management_params(
                F_pool_memory_provider_management_params* provider_management_params_p,
                auto* child_provider_management_params_p
            )
            {
                F_memory_block* pool_memory_block_p = (F_memory_block*)(provider_management_params_p->pool_memory_block_p);

                F_linked_memory_block_list* child_memory_block_linked_list_p = &(pool_memory_block_p->child_memory_block_linked_list);

                child_provider_management_params_p->main_memory_block_linked_list_p = child_memory_block_linked_list_p;
            }



        private:
            sz header_size_ = 0;
            sz actual_block_size_ = 0;

        public:
            NCPP_FORCE_INLINE sz header_size() const noexcept { return header_size_; }
            NCPP_FORCE_INLINE sz actual_block_size() const noexcept { return actual_block_size_; }



        public:
            NCPP_FORCE_INLINE TF_pool_memory_provider() noexcept = default;
            NCPP_FORCE_INLINE TF_pool_memory_provider(const F_memory_provider_desc& provider_desc) :
                F_base(parse_provider_desc(provider_desc))
            {
                setup();
            }

            NCPP_FORCE_INLINE TF_pool_memory_provider(const TF_pool_memory_provider& x) :
                F_base(NCPP_BASE_R_CONST(x).provider_desc())
            {
                setup();
            }

            NCPP_FORCE_INLINE TF_pool_memory_provider& operator=(const TF_pool_memory_provider& x) {

                NCPP_BASE_THIS()->set_provider_desc(
                    NCPP_BASE_R_CONST(x).provider_desc()
                );

                setup();

                return *this;
            }



        private:
            void setup() {

                const auto& provider_desc = NCPP_BASE_THIS()->provider_desc();

                NCPP_ASSERT(
                    (
                        provider_desc.memory_block_alignment
                        % provider_desc.memory_payload_alignment
                    )
                    == 0
                ) << "block alignment must be multiples of memory_payload alignment";

                header_size_ = align_size(
                    sizeof(F_memory_block) + provider_desc.memory_payload_alignment_offset,
                    provider_desc.memory_payload_alignment
                ) - provider_desc.memory_payload_alignment_offset;

                actual_block_size_ = align_size(
                    header_size_ + provider_desc.payload_size,
                    provider_desc.memory_block_alignment
                );
            }



        public:
            NCPP_FORCE_INLINE u8* block_p_to_root_data_p(F_memory_block* block_p) const noexcept {

                return ((u8*)block_p) + header_size_;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TF_pool_memory_provider& x) const noexcept {

                return (this == &x);
            }



        private:
            F_memory_provider_desc parse_provider_desc(const F_memory_provider_desc& desc) {

                NCPP_ASSERT(
                    desc.child_pool_memory_block_size
                ) << "invalid child block size";
                NCPP_ASSERT(
                    desc.max_child_pool_memory_block_count_per_pool_memory_block
                ) << "invalid child block count per pool block";

                F_memory_provider_desc result = desc;

                result.payload_size = desc.child_pool_memory_block_size * desc.max_child_pool_memory_block_count_per_pool_memory_block;

                return result;
            }



        public:
            F_child_memory_block* allocate_child_block(
                F_memory_provider_management_params* params_p = 0
            ) {
                NCPP_ASSERT(params_p->pool_memory_block_p) << "invalid pool block";

                F_memory_block* pool_memory_block_p = (F_memory_block*)(params_p->pool_memory_block_p);

                F_child_memory_block* block_p = 0;
                F_linked_memory_block_node* block_node_p = 0;

                const auto& pdesc = NCPP_BASE_THIS()->provider_desc();

                if(pool_memory_block_p->available_memory_block_linked_list.count()) {

                    block_node_p = pool_memory_block_p->available_memory_block_linked_list.tail_node_p();
                    block_p = (F_child_memory_block*)(block_node_p->block_p);

                    pool_memory_block_p->available_memory_block_linked_list.erase(block_node_p);

                    new(block_p) F_child_memory_block{};
                }
                else {
                    NCPP_ASSERT(
                        pool_memory_block_p->child_pool_memory_block_initialized_count < pdesc.max_child_pool_memory_block_count_per_pool_memory_block
                    ) << "pool block is full";

                    block_p = (F_child_memory_block*)(
                        (u8*)(NCPP_BASE_THIS()->block_p_to_root_data_p(pool_memory_block_p))
                        + pdesc.child_pool_memory_block_size * pool_memory_block_p->child_pool_memory_block_initialized_count
                    );
                    new(block_p) F_child_memory_block{};

                    ++(pool_memory_block_p->child_pool_memory_block_initialized_count);
                }

                block_node_p = &(block_p->available_memory_block_linked_node);
                block_node_p->block_p = block_p;

                block_p->parent_memory_block_p = params_p->pool_memory_block_p;

                return block_p;
            }
            void deallocate_child_block(
                F_child_memory_block* block_p,
                F_memory_provider_management_params* params_p = 0
            ) {
                NCPP_ASSERT(params_p->pool_memory_block_p) << "invalid pool block";

                F_memory_block* pool_memory_block_p = (F_memory_block*)(params_p->pool_memory_block_p);

                F_linked_memory_block_node* block_node_p = &(block_p->available_memory_block_linked_node);
                block_node_p->block_p = block_p;

                pool_memory_block_p->available_memory_block_linked_list.push_back(block_node_p);
            }

        public:
            /**
             *	Clears everything and to be the same as the default instance.
             */
            NCPP_FORCE_INLINE void reset() {}
            /**
             *	Clear some essential datas.
             */
            NCPP_FORCE_INLINE void clear() {}

        };



        using F_pool_memory_provider = TF_pool_memory_provider<>;
        using F_child_pool_memory_provider = TF_memory_provider<
            F_pool_memory_provider,
            F_child_pool_memory_block
        >;

    }

}

