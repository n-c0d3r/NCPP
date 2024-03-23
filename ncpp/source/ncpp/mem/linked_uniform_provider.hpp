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

        struct F_linked_uniform_block_node {

            void* block_p = 0;
            F_linked_uniform_block_node* prev_p = 0;
            F_linked_uniform_block_node* next_p = 0;

        };



        class F_linked_uniform_block_list {

        private:
            F_linked_uniform_block_node* head_node_p_ = 0;
            F_linked_uniform_block_node* tail_node_p_ = 0;
            sz count_ = 0;

        public:
            NCPP_FORCE_INLINE F_linked_uniform_block_node* head_node_p() noexcept { return head_node_p_; }
            NCPP_FORCE_INLINE const F_linked_uniform_block_node* head_node_p() const noexcept { return head_node_p_; }
            NCPP_FORCE_INLINE F_linked_uniform_block_node* tail_node_p() noexcept { return tail_node_p_; }
            NCPP_FORCE_INLINE const F_linked_uniform_block_node* tail_node_p() const noexcept { return tail_node_p_; }

            NCPP_FORCE_INLINE sz count() const noexcept { return count_; }



        public:
            NCPP_FORCE_INLINE F_linked_uniform_block_list() noexcept = default;

            NCPP_FORCE_INLINE F_linked_uniform_block_list(const F_linked_uniform_block_list& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list(F_linked_uniform_block_list&& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list& operator = (const F_linked_uniform_block_list& x) noexcept = delete;
            NCPP_FORCE_INLINE F_linked_uniform_block_list& operator = (F_linked_uniform_block_list&& x) noexcept = delete;



        public:
            void push_back(F_linked_uniform_block_node* node_p) {

                NCPP_ASSERT(node_p) << "invalid block to add";

                node_p->prev_p = tail_node_p_;

                if(tail_node_p_ == 0) {
                    head_node_p_ = node_p;
                }
                else {
                    tail_node_p_->next_p = node_p;
                }

                tail_node_p_ = node_p;

                ++count_;
            }
            void push_front(F_linked_uniform_block_node* node_p) {

                NCPP_ASSERT(node_p) << "invalid block to add";

                node_p->next_p = head_node_p_;

                if(head_node_p_ == 0) {
                    tail_node_p_ = node_p;
                }
                else {
                    head_node_p_->prev_p = node_p;
                }

                head_node_p_ = node_p;

                ++count_;
            }
            void erase(F_linked_uniform_block_node* node_p) {

                NCPP_ASSERT(node_p) << "invalid block to add";

                if(node_p->next_p) {
                    node_p->next_p->prev_p = node_p->prev_p;
                }
                else {
                    tail_node_p_ = node_p->prev_p;
                }

                if(node_p->prev_p) {
                    node_p->prev_p->next_p = node_p->next_p;
                }
                else {
                    head_node_p_ = node_p->next_p;
                }

                node_p->next_p = 0;
                node_p->prev_p = 0;

                --count_;
            }

            template<typename F_functor__>
            void T_iterate(F_functor__&& functor) {

                F_linked_uniform_block_node* node_p = head_node_p_;

                while(node_p) {

                    F_linked_uniform_block_node* next_node_p = node_p->next_p;

                    functor(node_p);

                    node_p = next_node_p;
                }
            }
            template<typename F_functor__>
            void T_reverse_iterate(F_functor__&& functor) {

                F_linked_uniform_block_node* node_p = tail_node_p_;

                while(node_p) {

                    F_linked_uniform_block_node* prev_node_p = node_p->prev_p;

                    functor(node_p);

                    node_p = prev_node_p;
                }
            }

        };



        struct D_main_memory_block_linked_node
        {

            F_linked_uniform_block_node main_memory_block_linked_node;

        };
        struct D_child_memory_block_linked_list
        {

            F_linked_uniform_block_list child_memory_block_linked_list;

        };

        using F_linked_uniform_block = NCPP_COMBINE_TYPES(

            F_default_uniform_block,

            D_main_memory_block_linked_node

        );



        using F_linked_uniform_provider_desc = NCPP_COMBINE_TYPES(

            F_default_uniform_provider_desc

        );



        struct D_main_memory_block_linked_list_p {

            F_linked_uniform_block_list* main_memory_block_linked_list_p = 0;

        };

        using F_linked_uniform_provider_management_params = NCPP_COMBINE_TYPES(

            F_default_uniform_provider_management_params,

            D_main_memory_block_linked_list_p

        );



        template<
            class F_parent_uniform_provider__ = F_invalid_uniform_provider,
            typename F_uniform_block__ = F_linked_uniform_block,
            typename F_child_uniform_block__ = void,
            typename F_uniform_provider_desc__ = F_linked_uniform_provider_desc,
            typename F_uniform_provider_management_params__ = F_linked_uniform_provider_management_params
        >
        class TF_linked_uniform_provider :
            public TA_uniform_provider<
                F_parent_uniform_provider__,
                F_uniform_block__,
                F_child_uniform_block__,
                F_uniform_provider_desc__,
                F_uniform_provider_management_params__
            >
        {

        private:
            using F_base = TA_uniform_provider<
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
            NCPP_REQUIRE_COMBINED(F_uniform_block, F_linked_uniform_block);
            NCPP_REQUIRE_COMBINED(F_uniform_provider_desc, F_linked_uniform_provider_desc);
            NCPP_REQUIRE_COMBINED(F_uniform_provider_management_params, F_linked_uniform_provider_management_params);

            NCPP_REQUIRE_COMBINED(F_child_uniform_block, void);



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
            F_uniform_block* create_block(
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                NCPP_ASSERT(params_p->main_memory_block_linked_list_p) << "invalid target list";

                F_uniform_block* block_p = (F_uniform_block*)F_base::create_block(params_p, parent_params_p);

                F_linked_uniform_block_node* main_memory_block_linked_node_p = &(block_p->main_memory_block_linked_node);
                main_memory_block_linked_node_p->block_p = block_p;

                params_p->main_memory_block_linked_list_p->push_back(main_memory_block_linked_node_p);

                return block_p;
            }
            void destroy_block(
                F_uniform_block* block_p,
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                NCPP_ASSERT(params_p->main_memory_block_linked_list_p) << "invalid target list";

                F_linked_uniform_block_node* main_memory_block_linked_node_p = &(block_p->main_memory_block_linked_node);

                params_p->main_memory_block_linked_list_p->erase(main_memory_block_linked_node_p);

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

