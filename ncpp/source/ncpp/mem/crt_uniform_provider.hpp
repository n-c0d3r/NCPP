#pragma once

/** @file ncpp/mem/crt_uniform_provider.hpp
*	@brief Implements current runtime uniform provider.
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

        using F_crt_uniform_block = NCPP_COMBINE_TYPES(

            F_default_uniform_block

        );

        using F_crt_uniform_provider_desc = NCPP_COMBINE_TYPES(

            F_default_uniform_provider_desc

        );

        using F_crt_uniform_provider_management_params = NCPP_COMBINE_TYPES(

            F_default_uniform_provider_management_params

        );



        template<
            typename F_uniform_block__ = F_crt_uniform_block,
            typename F_child_uniform_block__ = F_default_uniform_block,
            typename F_uniform_provider_desc__ = F_crt_uniform_provider_desc,
            typename F_uniform_provider_management_params__ = F_crt_uniform_provider_management_params
        >
        class TF_crt_uniform_provider :
            public TA_uniform_provider<
                F_invalid_uniform_provider,
                F_uniform_block__,
                F_child_uniform_block__,
                F_uniform_provider_desc__,
                F_uniform_provider_management_params__
            >
        {

        private:
            using F_base = TA_uniform_provider<
                F_invalid_uniform_provider,
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
            NCPP_REQUIRE_BASE(F_uniform_block, F_default_uniform_block);
            NCPP_REQUIRE_BASE(F_uniform_provider_desc, F_default_uniform_provider_desc);
            NCPP_REQUIRE_BASE(F_uniform_provider_management_params, F_default_uniform_provider_management_params);

            NCPP_REQUIRE_BASE(F_child_uniform_block, F_default_uniform_block);



        public:
            NCPP_FORCE_INLINE TF_crt_uniform_provider() noexcept = default;
            NCPP_FORCE_INLINE TF_crt_uniform_provider(const F_uniform_provider_desc& provider_desc) :
                F_base(provider_desc)
            {
            }

            NCPP_FORCE_INLINE TF_crt_uniform_provider(const TF_crt_uniform_provider& x) :
                F_base(NCPP_BASE_R_CONST(x).provider_desc())
            {
            }

            NCPP_FORCE_INLINE TF_crt_uniform_provider& operator=(const TF_crt_uniform_provider& x) {

                NCPP_BASE_THIS()->set_provider_desc(
                    NCPP_BASE_R_CONST(x).provider_desc()
                );

                return *this;
            }



        public:
            NCPP_FORCE_INLINE b8 operator==(const TF_crt_uniform_provider& x) const noexcept {

                return (this == &x);
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



        using F_crt_uniform_provider = TF_crt_uniform_provider<>;

    }

}

