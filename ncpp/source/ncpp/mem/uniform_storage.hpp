#pragma once

/** @file ncpp/mem/uniform_storage.hpp
*	@brief Implements uniform storage base class template.
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
#include <ncpp/mem/uniform_provider.hpp>

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

        template<class F_uniform_storage__, class F_uniform_provider__>
        class TA_uniform_storage {

        private:
            using F_this = TA_uniform_storage<F_uniform_storage__, F_uniform_provider__>;

        public:
            using F_uniform_storage = F_uniform_storage__;
            using F_uniform_provider = F_uniform_provider__;

        public:
            using F_uniform_block = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_block;
            using F_uniform_provider_desc = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_provider_desc;
            using F_uniform_provider_management_params = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_provider_management_params;

            using F_child_uniform_block = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_child_uniform_block;



        private:
            utilities::TF_mem_wrap<F_uniform_provider> provider_mem_wrap_;
            NCPP_ENABLE_IF_DEBUG(b8 is_provider_initialized_ = false);

        public:
            NCPP_FORCE_INLINE F_uniform_provider& provider() noexcept { return provider_mem_wrap_.get(); }
            NCPP_FORCE_INLINE const F_uniform_provider& provider() const noexcept { return provider_mem_wrap_.get(); }



        protected:
            NCPP_FORCE_INLINE TA_uniform_storage()
            {
            }

        public:
            virtual ~TA_uniform_storage() {

                NCPP_ENABLE_IF_DEBUG(
                    NCPP_ASSERT(is_provider_initialized_) << "provider is not initialized"
                );

                provider_mem_wrap_.destruct();
            }

            NCPP_FORCE_INLINE TA_uniform_storage(const TA_uniform_storage& x) = delete;
            NCPP_FORCE_INLINE TA_uniform_storage(TA_uniform_storage&& x) = delete;

            NCPP_FORCE_INLINE TA_uniform_storage& operator=(const TA_uniform_storage& x) = delete;
            NCPP_FORCE_INLINE TA_uniform_storage& operator=(TA_uniform_storage&& x) = delete;



        public:
            NCPP_FORCE_INLINE b8 operator==(const TA_uniform_storage& x) const noexcept {

                return (this == &x);
            }



        protected:
            void init_provider(const F_uniform_provider_desc& provider_desc) {

                provider_mem_wrap_.construct(provider_desc);

                NCPP_ENABLE_IF_DEBUG(is_provider_initialized_ = true);
            }



        public:
            F_uniform_block* pop_block();
            void push_block(F_uniform_block*);

        };

    }

}

