#pragma once

/** @file ncpp/mem/linked_uniform_provider.hpp
*	@brief Implements linked uniform provider.
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
#include <ncpp/mem/crt_uniform_provider.hpp>

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

        class F_linked_uniform_block_list;



        struct F_linked_uniform_block : public F_crt_uniform_block {

            F_linked_uniform_block* prev_p = 0;
            F_linked_uniform_block* next_p = 0;

        };
        struct F_linked_uniform_provider_desc : public F_crt_uniform_provider_desc {

        };
        struct F_linked_uniform_provider_management_params : public F_crt_uniform_provider_management_params {

            F_linked_uniform_block_list* target_list_p = 0;

        };



        class F_linked_uniform_block_list {

        private:
            F_linked_uniform_block* head_block_p_ = 0;
            F_linked_uniform_block* tail_block_p_ = 0;

        public:
            NCPP_FORCE_INLINE F_linked_uniform_block* head_block_p() noexcept { return head_block_p_; }
            NCPP_FORCE_INLINE const F_linked_uniform_block* head_block_p() const noexcept { return head_block_p_; }
            NCPP_FORCE_INLINE F_linked_uniform_block* tail_block_p() noexcept { return tail_block_p_; }
            NCPP_FORCE_INLINE const F_linked_uniform_block* tail_block_p() const noexcept { return tail_block_p_; }



        public:
            NCPP_FORCE_INLINE F_linked_uniform_block_list() noexcept = default;

            NCPP_FORCE_INLINE F_linked_uniform_block_list(const F_linked_uniform_block_list& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list(F_linked_uniform_block_list&& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list& operator = (const F_linked_uniform_block_list& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list& operator = (F_linked_uniform_block_list&& x) noexcept = delete;



        public:
            void push_back(F_linked_uniform_block* block_p) {

                NCPP_ASSERT(block_p) << "invalid block to add";

                block_p->prev_p = tail_block_p_;

                if(tail_block_p_ == 0) {

                    tail_block_p_ = block_p;
                    head_block_p_ = block_p;
                }
                else {
                    tail_block_p_->next_p = block_p;
                }
            }
            void push_front(F_linked_uniform_block* block_p) {

                NCPP_ASSERT(block_p) << "invalid block to add";

                block_p->next_p = head_block_p_;

                if(head_block_p_ == 0) {

                    head_block_p_ = block_p;
                    tail_block_p_ = block_p;
                }
                else {
                    head_block_p_->prev_p = block_p;
                }
            }
            void erase(F_linked_uniform_block* block_p) {

                NCPP_ASSERT(block_p) << "invalid block to add";

                if(block_p->next_p) {

                    block_p->next_p->prev_p = block_p->prev_p;
                }
                else {
                    tail_block_p_ = block_p->prev_p;
                }

                if(block_p->prev_p) {

                    block_p->prev_p->next_p = block_p->next_p;
                }
                else {
                    head_block_p_ = block_p->next_p;
                }
            }

            template<typename F_functor__>
            void T_iterate(F_functor__&& functor) {

                F_linked_uniform_block* block_p = head_block_p_;

                while(block_p) {

                    F_linked_uniform_block* next_block_p = block_p->next_p;

                    functor(block_p);

                    block_p = next_block_p;
                }
            }
            template<typename F_functor__>
            void T_reverse_iterate(F_functor__&& functor) {

                F_linked_uniform_block* block_p = tail_block_p_;

                while(block_p) {

                    F_linked_uniform_block* prev_block_p = block_p->prev_p;

                    functor(block_p);

                    block_p = prev_block_p;
                }
            }

        };



        template<class F_parent_uniform_provider__ = F_crt_uniform_provider, class F_uniform_block__ = F_linked_uniform_block, class F_uniform_provider_desc__ = F_linked_uniform_provider_desc, class F_uniform_provider_management_params__ = F_linked_uniform_provider_management_params>
        class TF_linked_uniform_provider : public TA_uniform_provider<F_parent_uniform_provider__, F_uniform_block__, F_uniform_provider_desc__, F_uniform_provider_management_params__> {

        private:
            using F_base = TA_uniform_provider<F_parent_uniform_provider__, F_uniform_block__, F_uniform_provider_desc__, F_uniform_provider_management_params__>;

        public:
            using typename F_base::F_parent_uniform_provider;
            using typename F_base::F_uniform_block;
            using typename F_base::F_uniform_provider_desc;
            using typename F_base::F_uniform_provider_management_params;



        public:
            NCPP_FORCE_INLINE TF_linked_uniform_provider() noexcept = default;
            NCPP_FORCE_INLINE TF_linked_uniform_provider(const F_uniform_provider_desc& provider_desc) :
                F_base(provider_desc)
            {
            }
            NCPP_FORCE_INLINE TF_linked_uniform_provider(const TF_linked_uniform_provider& x) :
                F_base(NCPP_BASE_R_CONST(x).provider_desc())
            {
            }

            NCPP_FORCE_INLINE TF_linked_uniform_provider& operator=(const TF_linked_uniform_provider& x) {

                NCPP_BASE_THIS()->set_provider_desc(
                    NCPP_BASE_R_CONST(x).provider_desc()
                );

                return *this;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TF_linked_uniform_provider& x) const noexcept {

                return (this == &x);
            }



        public:
            A_uniform_block* create_block(
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* parent_params_p = 0
            ) {

                NCPP_ASSERT(((F_linked_uniform_provider_management_params*)params_p)->target_list_p) << "invalid target list";

                F_uniform_block* block_p = (F_uniform_block*)F_base::create_block(params_p, parent_params_p);

                ((F_linked_uniform_provider_management_params*)params_p)->target_list_p->push_back(block_p);

                return block_p;
            }
            void destroy_block(
                A_uniform_block* block_p,
                A_uniform_provider_management_params* params_p = 0,
                A_uniform_provider_management_params* parent_params_p = 0
            ) {

                NCPP_ASSERT(((F_linked_uniform_provider_management_params*)params_p)->target_list_p) << "invalid target list";

                ((F_linked_uniform_provider_management_params*)params_p)->target_list_p->erase((F_uniform_block*)block_p);

                F_base::destroy_block(block_p, params_p, parent_params_p);
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



        using F_linked_uniform_provider = TF_linked_uniform_provider<>;

    }

}

