#pragma once

/** @file ncpp/mem/uniform_provider.hpp
*	@brief Implements uniform provider base class template.
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

        using F_default_uniform_block = NCPP_COMBINE_TYPES(
        );



        struct D_memory_block_payload_size {

            sz memory_payload_size = 0;

        };
        struct D_memory_block_payload_alignment {

            sz memory_payload_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;

        };
        struct D_memory_block_payload_alignment_offset {

            sz memory_payload_alignment_offset = 0;

        };
        struct D_memory_memory_block_alignment {

            sz memory_block_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;

        };

        using F_default_uniform_provider_desc = NCPP_COMBINE_TYPES(

            D_memory_block_payload_size,
            D_memory_block_payload_alignment,
            D_memory_block_payload_alignment_offset,
            D_memory_memory_block_alignment

        );



        using F_default_uniform_provider_management_params = NCPP_COMBINE_TYPES(
        );



        class F_invalid_uniform_provider final {

        public:
            void* create_block(
                void* params_p = 0,
                void* parent_params_p = 0
            ) { return 0; }
            void destroy_block(
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

            template<class F_uniform_provider__>
            struct TF_uniform_provider_safe_infos {

                using F_uniform_block = typename F_uniform_provider__::F_uniform_block;
                using F_uniform_provider_desc = typename F_uniform_provider__::F_uniform_provider_desc;
                using F_uniform_provider_management_params = typename F_uniform_provider__::F_uniform_provider_management_params;

                using F_child_uniform_block = typename F_uniform_provider__::F_child_uniform_block;

            };

            template<>
            struct TF_uniform_provider_safe_infos<F_invalid_uniform_provider> {

                using F_uniform_block = void;
                using F_uniform_provider_desc = void;
                using F_uniform_provider_management_params = void;

                using F_child_uniform_block = void;

            };

        }

        template<class F_uniform_provider__>
        using TF_uniform_provider_safe_infos = internal::TF_uniform_provider_safe_infos<F_uniform_provider__>;



        template<
            class F_parent_uniform_provider__ = F_invalid_uniform_provider,
            typename F_uniform_block__ = F_default_uniform_block,
            typename F_child_uniform_block__ = F_default_uniform_block,
            typename F_uniform_provider_desc__ = F_default_uniform_provider_desc,
            typename F_uniform_provider_management_params__ = F_default_uniform_provider_management_params
        >
        class TA_uniform_provider {

        private:
            using F_this = TA_uniform_provider<
                F_parent_uniform_provider__,
                F_uniform_block__,
                F_child_uniform_block__,
                F_uniform_provider_desc__,
                F_uniform_provider_management_params__
            >;

        public:
            using F_parent_uniform_provider = F_parent_uniform_provider__;
            using F_uniform_block = F_uniform_block__;
            using F_uniform_provider_desc = F_uniform_provider_desc__;
            using F_uniform_provider_management_params = F_uniform_provider_management_params__;

            using F_child_uniform_block = F_child_uniform_block__;

        public:
            using F_parent_uniform_block = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_block;
            using F_parent_uniform_provider_desc = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_provider_desc;
            using F_parent_uniform_provider_management_params = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_provider_management_params;

            using F_parent_child_uniform_block = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_child_uniform_block;

        public:
            static_assert(
                std::is_same_v<F_parent_uniform_provider, F_invalid_uniform_provider>
                || std::is_same_v<
                    F_parent_child_uniform_block,
                    F_uniform_block
                >,
                "invalid parent uniform provider"
            );

        public:
            NCPP_REQUIRE_COMBINED(F_uniform_block, F_default_uniform_block);
            NCPP_REQUIRE_COMBINED(F_uniform_provider_desc, F_default_uniform_provider_desc);
            NCPP_REQUIRE_COMBINED(F_uniform_provider_management_params, F_default_uniform_provider_management_params);

            NCPP_REQUIRE_COMBINED(F_child_uniform_block, F_default_uniform_block);



        private:
            F_uniform_provider_desc provider_desc_;

            sz actual_block_size_ = 0;
            sz header_size_ = 0;

        public:
            NCPP_FORCE_INLINE const F_uniform_provider_desc& provider_desc() const noexcept { return provider_desc_; }

            NCPP_FORCE_INLINE sz actual_block_size() const noexcept { return actual_block_size_; }
            NCPP_FORCE_INLINE sz header_size() const noexcept { return header_size_; }

        protected:
            NCPP_FORCE_INLINE void set_provider_desc(const F_uniform_provider_desc& value) noexcept { provider_desc_ = value; }



        public:
            F_parent_uniform_provider* parent_memory_block_p = 0;



        protected:
            NCPP_FORCE_INLINE TA_uniform_provider() noexcept = default;
            NCPP_FORCE_INLINE TA_uniform_provider(const F_uniform_provider_desc& provider_desc) :
                provider_desc_(provider_desc)
            {

                setup();
            }

            NCPP_FORCE_INLINE TA_uniform_provider(const TA_uniform_provider& x) :
                provider_desc_(x.provider_desc_)
            {

                setup();
            }

            NCPP_FORCE_INLINE TA_uniform_provider& operator=(const TA_uniform_provider& x) {

                provider_desc_ = x.provider_desc_;

                setup();

                return *this;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TA_uniform_provider& x) const noexcept {

                return (this == &x);
            }



        private:
            void setup() {

                NCPP_ASSERT(
                    (
                        provider_desc_.memory_block_alignment
                        / provider_desc_.memory_payload_alignment
                        * provider_desc_.memory_payload_alignment
                    )
                    == provider_desc_.memory_block_alignment
                ) << "block alignment must be multiples of memory_payload alignment";

                header_size_ = align_size(
                    sizeof(F_uniform_block) + provider_desc_.memory_payload_alignment_offset,
                    provider_desc_.memory_payload_alignment
                ) - provider_desc_.memory_payload_alignment_offset;

                actual_block_size_ = align_size(
                    header_size_ + provider_desc_.payload_size,
                    provider_desc_.memory_block_alignment
                );
            }



        public:
            NCPP_FORCE_INLINE u8* block_p_to_root_data_p(F_uniform_block* block_p) const noexcept {

                return ((u8*)block_p) + header_size_;
            }



        public:
            NCPP_FORCE_INLINE F_uniform_block* default_create_block() {

                NCPP_ASSERT(actual_block_size_) << "invalid block desc";

                F_uniform_block* block_p = (F_uniform_block*)(
                    F_crt_allocator().allocate(
                        actual_block_size_,
                        provider_desc_.memory_block_alignment,
                        0,
                        0
                    )
                );

                new(block_p) F_uniform_block{};

                return block_p;
            }
            void default_destroy_block(F_uniform_block* block_p) {

                NCPP_ASSERT(actual_block_size_) << "invalid block desc";

                ((F_uniform_block*)block_p)->~F_uniform_block();

                F_crt_allocator().deallocate(block_p);
            }

        public:
            F_uniform_block* create_block(
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                F_uniform_block* block_p = 0;

                if(!parent_memory_block_p)
                    block_p = (F_uniform_block*)default_create_block();
                else
                    block_p = (F_uniform_block*)(
                        parent_memory_block_p->allocate_child_block(
                            parent_params_p
                        )
                    );

                return block_p;
            }
            void destroy_block(
                F_uniform_block* block_p,
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                if(!parent_memory_block_p)
                    default_destroy_block(block_p);
                else {
                    parent_memory_block_p->deallocate_child_block(
                        block_p,
                        parent_params_p
                    );
                }
            }

        public:
            F_child_uniform_block* allocate_child_block(
                F_uniform_provider_management_params* params_p = 0
            );
            void deallocate_child_block(
                F_child_uniform_block* block_p,
                F_uniform_provider_management_params* params_p = 0
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

