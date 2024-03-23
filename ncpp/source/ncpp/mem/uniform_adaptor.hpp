#pragma once

/** @file ncpp/mem/uniform_adaptor.hpp
*	@brief Implements uniform adaptor base class template.
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

        template<
            class F_uniform_adaptor__,
            class F_uniform_provider__,
            class F_source_in__
        >
        class TA_uniform_adaptor {

        private:
            using F_this = TA_uniform_adaptor<
                F_uniform_adaptor__,
                F_uniform_provider__,
                F_source_in__
            >;

        public:
            using F_uniform_adaptor = F_uniform_adaptor__;
            using F_uniform_provider = F_uniform_provider__;
            using F_source_in = F_source_in__;

        public:
            using F_uniform_block = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_block;
            using F_uniform_provider_desc = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_provider_desc;
            using F_uniform_provider_management_params = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_uniform_provider_management_params;

            using F_child_uniform_block = typename TF_uniform_provider_safe_infos<F_uniform_provider>::F_child_uniform_block;



        private:
            F_source_in* source_in_p_;

        public:
            NCPP_FORCE_INLINE F_source_in* source_in_p() noexcept { return source_in_p_; }
            NCPP_FORCE_INLINE const F_source_in* source_in_p() const noexcept { return source_in_p_; }



        protected:
            NCPP_FORCE_INLINE TA_uniform_adaptor(F_source_in* source_in_p) :
                source_in_p_(source_in_p)
            {
            }

            NCPP_FORCE_INLINE TA_uniform_adaptor(const TA_uniform_adaptor& x) = delete;
            NCPP_FORCE_INLINE TA_uniform_adaptor(TA_uniform_adaptor&& x) = delete;

            NCPP_FORCE_INLINE TA_uniform_adaptor& operator=(const TA_uniform_adaptor& x) = delete;
            NCPP_FORCE_INLINE TA_uniform_adaptor& operator=(TA_uniform_adaptor&& x) = delete;



        public:
            NCPP_FORCE_INLINE b8 operator==(const TA_uniform_adaptor& x) const noexcept {

                return (this == &x);
            }



        public:
            F_uniform_block* pop_block();
            void push_block(F_uniform_block*);

        };

    }

}

