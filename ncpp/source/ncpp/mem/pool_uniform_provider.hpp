#pragma once

/** @file ncpp/mem/pool_uniform_provider.hpp
*	@brief Implements pool uniform provider.
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

#include <ncpp/mem/uniform_provider.hpp>
#include <ncpp/mem/linked_uniform_provider.hpp>

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

        class F_pool_uniform_block_list;



        struct I_pool_uniform_block : public I_linked_uniform_block {

            F_linked_uniform_block_list child_list;

            F_linked_uniform_block_list available_list;
            sz initialized_count = 0;

        };
        struct I_child_pool_uniform_block : public I_linked_uniform_block {

            F_linked_uniform_block_node available_node;

        };
        struct I_pool_uniform_provider_desc : public I_linked_uniform_provider_desc {

            sz child_block_size = 0;
            sz max_child_block_count_per_pool_block = 0;

        };
        struct I_pool_uniform_provider_management_params : public I_linked_uniform_provider_management_params {

            I_pool_uniform_block* pool_block_p = 0;



            NCPP_FORCE_INLINE void process_child_management_params(I_linked_uniform_provider_management_params* child_management_params_p) noexcept {

                NCPP_ASSERT(pool_block_p) << "invalid pool block";

                child_management_params_p->main_list_p = &(pool_block_p->child_list);
            }

        };



        template<
            class F_parent_uniform_provider__ = F_invalid_uniform_provider,
            class F_uniform_block__ = I_pool_uniform_block,
            class F_child_uniform_block__ = I_child_pool_uniform_block,
            class F_uniform_provider_desc__ = I_pool_uniform_provider_desc,
            class F_uniform_provider_management_params__ = I_pool_uniform_provider_management_params
        >
        class TF_pool_uniform_provider :
            public TF_linked_uniform_provider<
                F_parent_uniform_provider__,
                F_uniform_block__,
                F_child_uniform_block__,
                F_uniform_provider_desc__,
                F_uniform_provider_management_params__
            >
        {

        private:
            using F_base = TF_linked_uniform_provider<
                F_parent_uniform_provider__,
                F_uniform_block__,
                F_child_uniform_block__,
                F_uniform_provider_desc__,
                F_uniform_provider_management_params__
            >;

        public:
            using typename F_base::F_parent_uniform_provider;
            using typename F_base::F_uniform_block;
            using typename F_base::F_uniform_provider_desc;
            using typename F_base::F_uniform_provider_management_params;

            using typename F_base::F_child_uniform_block;

        public:
            using typename F_base::F_parent_uniform_provider_management_params;



        public:
            NCPP_REQUIRE_BASE(F_uniform_block, I_pool_uniform_block);
            NCPP_REQUIRE_BASE(F_uniform_provider_desc, I_pool_uniform_provider_desc);
            NCPP_REQUIRE_BASE(F_uniform_provider_management_params, I_pool_uniform_provider_management_params);

            NCPP_REQUIRE_BASE(F_child_uniform_block, I_child_pool_uniform_block);



        public:
            NCPP_FORCE_INLINE TF_pool_uniform_provider() noexcept = default;
            NCPP_FORCE_INLINE TF_pool_uniform_provider(const F_uniform_provider_desc& provider_desc) :
                F_base(parse_provider_desc(provider_desc))
            {
                setup();
            }

            NCPP_FORCE_INLINE TF_pool_uniform_provider(const TF_pool_uniform_provider& x) :
                F_base(NCPP_BASE_R_CONST(x).provider_desc())
            {
                setup();
            }

            NCPP_FORCE_INLINE TF_pool_uniform_provider& operator=(const TF_pool_uniform_provider& x) {

                NCPP_BASE_THIS()->set_provider_desc(
                    NCPP_BASE_R_CONST(x).provider_desc()
                );

                setup();

                return *this;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TF_pool_uniform_provider& x) const noexcept {

                return (this == &x);
            }



        private:
            F_uniform_provider_desc parse_provider_desc(const F_uniform_provider_desc& desc) {

                NCPP_ASSERT(
                    desc.child_block_size
                ) << "invalid child block size";
                NCPP_ASSERT(
                    desc.max_child_block_count_per_pool_block
                ) << "invalid child block count per pool block";

                F_uniform_provider_desc result = desc;

                result.payload_size = desc.child_block_size * desc.max_child_block_count_per_pool_block;

                return result;
            }
            void setup() {

            }



        public:
            F_child_uniform_block* allocate_child_block(
                F_uniform_provider_management_params* params_p = 0
            ) {

                NCPP_ASSERT(params_p->pool_block_p) << "invalid pool block";

                F_uniform_block* pool_block_p = params_p->pool_block_p;

                F_child_uniform_block* block_p = 0;
                F_linked_uniform_block_node* block_node_p = 0;

                const auto& pdesc = NCPP_BASE_THIS()->provider_desc();

                if(pool_block_p->initialized_count < pdesc.max_child_block_count_per_pool_block) {
                    block_p = (F_child_uniform_block*)(
                        (u8*)(NCPP_BASE_THIS()->block_p_to_root_data_p(pool_block_p))
                        + pdesc.child_block_size * pool_block_p->initialized_count
                    );
                    new(block_p) F_child_uniform_block{};

                    ++(pool_block_p->initialized_count);
                }
                else{
                    NCPP_ASSERT(pool_block_p->available_list.count()) << "pool block out of bound";

                    block_node_p = pool_block_p->available_list.tail_node_p();
                    block_p = (F_child_uniform_block*)(block_node_p->block_p);

                    pool_block_p->available_list.erase(block_node_p);

                    new(block_p) F_child_uniform_block{};
                }

                block_node_p = &(block_p->available_node);
                block_node_p->block_p = block_p;

                block_p->parent_p = params_p->pool_block_p;

                return block_p;
            }
            void deallocate_child_block(
                F_child_uniform_block* block_p,
                F_uniform_provider_management_params* params_p = 0
            ) {

                NCPP_ASSERT(params_p->pool_block_p) << "invalid pool block";

                F_uniform_block* pool_block_p = params_p->pool_block_p;

                F_linked_uniform_block_node* block_node_p = &(block_p->available_node);
                block_node_p->block_p = block_p;

                pool_block_p->available_list.push_back(block_node_p);
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



        using F_pool_uniform_provider = TF_pool_uniform_provider<>;

    }

}

