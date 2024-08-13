#pragma once

/** @file ncpp/mem/memory_provider.hpp
*	@brief Implements memory provider base class template.
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

#include <ncpp/mem/allocator.hpp>
#include <ncpp/mem/crt_allocator.hpp>
#include <ncpp/utilities/combine_types.hpp>

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

        struct D_parent_memory_block_p {

            void* parent_memory_block_p = 0;

        };

        struct D_child_memory_block_count_u8 {

            u8 child_memory_block_count_u8 = 0;

        };
        struct D_child_memory_block_count_u16 {

            u16 child_memory_block_count_u16 = 0;

        };
        struct D_child_memory_block_count_u32 {

            u32 child_memory_block_count_u32 = 0;

        };

        using F_default_memory_block = NCPP_COMBINE_TYPES(
        );



        struct D_memory_block_payload_size {

            sz memory_block_payload_size = 0;

        };
        struct D_memory_block_payload_alignment {

            sz memory_block_payload_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;

        };
        struct D_memory_block_payload_alignment_offset {

            sz memory_block_payload_alignment_offset = 0;

        };
        struct D_memory_block_size {

            sz memory_block_size = 0;

        };
        struct D_memory_block_alignment {

            sz memory_block_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;

        };
        struct D_memory_block_alignment_offset {

            sz memory_block_alignment_offset = 0;

        };

        using F_default_memory_provider_desc = NCPP_COMBINE_TYPES(
        );
        
        using F_default_memory_provider_management_params = NCPP_COMBINE_TYPES(
        );



        class F_invalid_memory_provider final {

        public:
            void* create_block_through_parent(
                void* params_p = 0,
                void* parent_params_p = 0
            ) { return 0; }
            void destroy_block_through_parent(
                void* block_p,
                void* params_p = 0,
                void* parent_params_p = 0
            ) {}

        public:
            void* allocate_child_block(
                void* params_p = 0
            ){ return 0; }
            void deallocate_child_block(
                void* block_p,
                void* params_p = 0
            ){}

        };

        namespace internal {

            template<class F_memory_provider__>
            struct TF_memory_provider_safe_infos {

                using F_memory_block = typename F_memory_provider__::F_memory_block;
                using F_memory_provider_desc = typename F_memory_provider__::F_memory_provider_desc;
                using F_memory_provider_management_params = typename F_memory_provider__::F_memory_provider_management_params;

                using F_child_memory_block = typename F_memory_provider__::F_child_memory_block;

            };

            template<>
            struct TF_memory_provider_safe_infos<F_invalid_memory_provider> {

                using F_memory_block = void;
                using F_memory_provider_desc = void;
                using F_memory_provider_management_params = void;

                using F_child_memory_block = void;

            };

        }

        template<class F_memory_provider__>
        using TF_memory_provider_safe_infos = internal::TF_memory_provider_safe_infos<F_memory_provider__>;



        template<
            class F_parent_memory_provider__ = F_invalid_memory_provider,
            typename F_memory_block__ = F_default_memory_block,
            typename F_child_memory_block__ = F_default_memory_block,
            typename F_memory_provider_desc__ = F_default_memory_provider_desc,
            typename F_memory_provider_management_params__ = F_default_memory_provider_management_params
        >
        class TF_memory_provider {

        private:
            using F_this = TF_memory_provider<
                F_parent_memory_provider__,
                F_memory_block__,
                F_child_memory_block__,
                F_memory_provider_desc__,
                F_memory_provider_management_params__
            >;

        public:
            using F_parent_memory_provider = F_parent_memory_provider__;
            using F_memory_block = F_memory_block__;
            using F_memory_provider_desc = F_memory_provider_desc__;
            using F_memory_provider_management_params = F_memory_provider_management_params__;

            using F_child_memory_block = F_child_memory_block__;

        public:
            using F_parent_memory_block = typename TF_memory_provider_safe_infos<F_parent_memory_provider>::F_memory_block;
            using F_parent_memory_provider_desc = typename TF_memory_provider_safe_infos<F_parent_memory_provider>::F_memory_provider_desc;
            using F_parent_memory_provider_management_params = typename TF_memory_provider_safe_infos<F_parent_memory_provider>::F_memory_provider_management_params;

            using F_parent_child_memory_block = typename TF_memory_provider_safe_infos<F_parent_memory_provider>::F_child_memory_block;

        public:
            static_assert(
                std::is_same_v<F_parent_memory_provider, F_invalid_memory_provider>
                || std::is_same_v<
                    F_parent_child_memory_block,
                    F_memory_block
                >,
                "invalid parent memory provider"
            );

        public:
            NCPP_REQUIRE_COMBINED(F_memory_block, F_default_memory_block);
            NCPP_REQUIRE_COMBINED(F_memory_provider_desc, F_default_memory_provider_desc);
            NCPP_REQUIRE_COMBINED(F_memory_provider_management_params, F_default_memory_provider_management_params);

            NCPP_REQUIRE_COMBINED(F_child_memory_block, F_default_memory_block);



        private:
            F_memory_provider_desc provider_desc_;

        public:
            NCPP_FORCE_INLINE const F_memory_provider_desc& provider_desc() const noexcept { return provider_desc_; }

        protected:
            NCPP_FORCE_INLINE void set_provider_desc(const F_memory_provider_desc& value) noexcept { provider_desc_ = value; }



        public:
            F_parent_memory_provider* parent_memory_provider_p = 0;



        public:
            NCPP_FORCE_INLINE TF_memory_provider() noexcept = default;
            NCPP_FORCE_INLINE TF_memory_provider(const F_memory_provider_desc& provider_desc) :
                provider_desc_(provider_desc)
            {
            }

            NCPP_FORCE_INLINE TF_memory_provider(const TF_memory_provider& x) :
                provider_desc_(x.provider_desc_)
            {
            }

            NCPP_FORCE_INLINE TF_memory_provider& operator=(const TF_memory_provider& x) {

                provider_desc_ = x.provider_desc_;

                return *this;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TF_memory_provider& x) const noexcept {

                return (this == &x);
            }



        public:
            NCPP_FORCE_INLINE F_memory_block* default_create_block(sz size, sz alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT, sz alignment_offset = 0) {

                F_memory_block* block_p = (F_memory_block*)(
                    F_crt_allocator().allocate(
                        size,
                        alignment,
                        alignment_offset,
                        0
                    )
                );

                new(block_p) F_memory_block{};

                return block_p;
            }
            void default_destroy_block(F_memory_block* block_p) {

                ((F_memory_block*)block_p)->~F_memory_block();

                F_crt_allocator().deallocate(block_p);
            }

        public:
            F_memory_block* create_block_through_parent(
                F_memory_provider_management_params* params_p = 0,
                F_parent_memory_provider_management_params* parent_params_p = 0
            ) {
                return (F_memory_block*)(
                    parent_memory_provider_p->allocate_child_block(
                        parent_params_p
                    )
                );
            }
            void destroy_block_through_parent(
                F_memory_block* block_p,
                F_memory_provider_management_params* params_p = 0,
                F_parent_memory_provider_management_params* parent_params_p = 0
            ) {
                return parent_memory_provider_p->deallocate_child_block(
                    block_p,
                    parent_params_p
                );
            }

        public:
            F_child_memory_block* allocate_child_block(
                F_memory_provider_management_params* params_p = 0
            );
            void deallocate_child_block(
                F_child_memory_block* block_p,
                F_memory_provider_management_params* params_p = 0
            );

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

    }

}

