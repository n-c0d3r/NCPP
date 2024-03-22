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

        struct A_uniform_block {

            A_uniform_block* parent_p = 0;

        };
        struct A_uniform_provider_desc {

            sz payload_size = 0;
            sz payload_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;
            sz payload_alignment_offset = 0;

            sz block_alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT;

        };
        struct A_uniform_provider_management_params {

            NCPP_FORCE_INLINE void process_child_management_params(A_uniform_provider_management_params*) noexcept {}

        };



        class A_invalid_uniform_provider;

        namespace internal {

            template<class F_uniform_provider__>
            struct TF_uniform_provider_safe_infos {

                using F_uniform_block = typename F_uniform_provider__::F_uniform_block;
                using F_uniform_provider_desc = typename F_uniform_provider__::F_uniform_provider_desc;
                using F_uniform_provider_management_params = typename F_uniform_provider__::F_uniform_provider_management_params;

            };

            template<>
            struct TF_uniform_provider_safe_infos<A_invalid_uniform_provider> {

                using F_uniform_block = void;
                using F_uniform_provider_desc = void;
                using F_uniform_provider_management_params = void;

            };

        }

        template<class F_uniform_provider__>
        using TF_uniform_provider_safe_infos = internal::TF_uniform_provider_safe_infos<F_uniform_provider__>;



        template<class F_parent_uniform_provider__ = A_invalid_uniform_provider, class F_uniform_block__ = A_uniform_block, class F_uniform_provider_desc__ = A_uniform_provider_desc, class F_uniform_provider_management_params__ = A_uniform_provider_management_params>
        class TA_uniform_provider {

        private:
            using F_this = TA_uniform_provider<F_parent_uniform_provider__, F_uniform_block__, F_uniform_provider_desc__, F_uniform_provider_management_params__>;

        public:
            using F_parent_uniform_provider = F_parent_uniform_provider__;
            using F_uniform_block = F_uniform_block__;
            using F_uniform_provider_desc = F_uniform_provider_desc__;
            using F_uniform_provider_management_params = F_uniform_provider_management_params__;

        public:
            using F_parent_uniform_block = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_block;
            using F_parent_uniform_provider_desc = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_provider_desc;
            using F_parent_uniform_provider_management_params = typename TF_uniform_provider_safe_infos<F_parent_uniform_provider>::F_uniform_provider_management_params;

        public:
            static_assert(
                std::is_same_v<F_parent_uniform_provider, A_invalid_uniform_provider>
                || std::is_same_v<F_parent_uniform_block, A_uniform_block>
                || std::is_convertible_v<
                    F_parent_uniform_block*,
                    F_uniform_block*
                >,
                "the parent uniform provider is not convertible to this uniform provider"
            );



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
            F_parent_uniform_provider* parent_p = 0;



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
                        provider_desc_.block_alignment
                        / provider_desc_.payload_alignment
                        * provider_desc_.payload_alignment
                    )
                    == provider_desc_.block_alignment
                ) << "block alignment must be multiples of payload alignment";

                header_size_ = align_size(
                    sizeof(F_uniform_block) + provider_desc_.payload_alignment_offset,
                    provider_desc_.payload_alignment
                ) - provider_desc_.payload_alignment_offset;

                actual_block_size_ = align_size(
                    header_size_ + provider_desc_.payload_size,
                    provider_desc_.block_alignment
                );
            }



        public:
            NCPP_FORCE_INLINE u8* block_p_to_root_data_p(F_uniform_block* block_p) const noexcept {

                return ((u8*)block_p) + header_size_;
            }



        public:
            NCPP_FORCE_INLINE F_uniform_block* default_create_block() {

                NCPP_ASSERT(actual_block_size_) << "invalid block desc";

                return (F_uniform_block*)(
                    F_crt_allocator().allocate(
                        actual_block_size_,
                        provider_desc_.block_alignment,
                        0,
                        0
                    )
                );
            }
            void default_destroy_block(F_uniform_block* block_p) {

                NCPP_ASSERT(actual_block_size_) << "invalid block desc";

                F_crt_allocator().deallocate(block_p);
            }

        public:
            F_uniform_block* create_block(
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                F_uniform_block* block_p = 0;

                if(!parent_p)
                    block_p = default_create_block();
                else {
                    block_p = (F_uniform_block*)(
                        parent_p->allocate_child_block(
                            parent_params_p
                        )
                    );
                }

                new(block_p) F_uniform_block{};

                return block_p;
            }
            void destroy_block(
                F_uniform_block* block_p,
                F_uniform_provider_management_params* params_p = 0,
                F_parent_uniform_provider_management_params* parent_params_p = 0
            ) {

                ((F_uniform_block*)block_p)->~F_uniform_block();

                if(!parent_p)
                    default_destroy_block(block_p);
                else {
                    parent_p->deallocate_child_block(
                        block_p,
                        parent_params_p
                    );
                }
            }

        public:
            F_uniform_block* allocate_child_block(
                F_uniform_provider_management_params* params_p = 0
            );
            void deallocate_child_block(
                F_uniform_block* block_p,
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

