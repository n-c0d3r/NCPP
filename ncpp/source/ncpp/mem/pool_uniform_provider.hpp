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



        struct F_pool_uniform_block : public F_linked_uniform_block {

            F_linked_uniform_block_list block_list;

        };
        struct F_pool_uniform_provider_desc : public F_linked_uniform_provider_desc {

            sz child_block_size = 0;
            sz max_child_block_count_per_pool_block = 0;

        };
        struct F_pool_uniform_provider_management_params : public F_linked_uniform_provider_management_params {

            F_pool_uniform_block* pool_block_p = 0;

        };



        template<class F_parent_uniform_provider__ = F_crt_uniform_provider, class F_uniform_block__ = F_pool_uniform_block, class F_uniform_provider_desc__ = F_pool_uniform_provider_desc, class F_uniform_provider_management_params__ = F_pool_uniform_provider_management_params>
        class TF_pool_uniform_provider : public TF_linked_uniform_provider<F_parent_uniform_provider__, F_uniform_block__, F_uniform_provider_desc__, F_uniform_provider_management_params__> {

        private:
            using F_base = TF_linked_uniform_provider<F_parent_uniform_provider__, F_uniform_block__, F_uniform_provider_desc__, F_uniform_provider_management_params__>;

        public:
            using typename F_base::F_parent_uniform_provider;
            using typename F_base::F_uniform_block;
            using typename F_base::F_uniform_provider_desc;
            using typename F_base::F_uniform_provider_management_params;



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
            A_uniform_block* create_block(
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* parent_params_p = 0
            ) {

                A_uniform_block* block_p = F_base::create_block(params_p, parent_params_p);

                return block_p;
            }
            void destroy_block(
                A_uniform_block* block_p,
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* parent_params_p = 0
            ) {

                F_base::destroy_block(block_p, params_p, parent_params_p);
            }

        public:
            A_uniform_block* allocate_child_block(
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* child_params_p = 0
            ) {

                NCPP_ASSERT(((F_pool_uniform_provider_management_params*)params_p)->pool_block_p) << "invalid pool block";

                return F_base::default_create_block();
            }
            void deallocate_child_block(
                A_uniform_provider_management_params* block_p,
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* child_params_p = 0
            ) {

                NCPP_ASSERT(((F_pool_uniform_provider_management_params*)params_p)->pool_block_p) << "invalid pool block";

                F_base::default_destroy_block(block_p);
            }

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

