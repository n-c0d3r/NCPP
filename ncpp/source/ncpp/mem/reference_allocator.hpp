#pragma once

/** @file ncpp/mem/reference_allocator.hpp
*	@brief Implements reference allocator.
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
#include <ncpp/mem/default_allocator.hpp>

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

        template<typename F_target_allocator__>
        class TF_default_reference_allocator_config {

        public:
            static constexpr F_target_allocator__* get_default() {

                return 0;
            }
            static constexpr b8 can_be_invalid = !std::is_same_v<F_target_allocator__, F_default_allocator>;

        };



		/**
		 *	An allocator using another allocator to allocate and deallocate memory by referenceing into the target allocator reference.
		 *	@param <F_target_allocator__> the target allocator to use.
		 */
		template<typename F_target_allocator__ = F_default_allocator, class F_config__ = TF_default_reference_allocator_config<F_target_allocator__>>
		class TF_reference_allocator : public TI_allocator<TF_reference_allocator<F_target_allocator__>> {

		public:
			using F_target_allocator = F_target_allocator__;
			using F_config = F_config__;



		private:
			F_target_allocator* target_allocator_p_;



		public:
			NCPP_FORCE_INLINE F_target_allocator& target_allocator() { return *target_allocator_p_; }
			NCPP_FORCE_INLINE const F_target_allocator& target_allocator() const { return *target_allocator_p_; }



		public:
			inline TF_reference_allocator(const char* name = 0) :
				TI_allocator<TF_reference_allocator<F_target_allocator__>>(name),
                target_allocator_p_(F_config::get_default())
			{



			}
			inline TF_reference_allocator(F_target_allocator& target_allocator, const char* name = 0) :
				TI_allocator<TF_reference_allocator<F_target_allocator__>>(name),
				target_allocator_p_(&target_allocator)
			{



			}
			inline TF_reference_allocator(const TF_reference_allocator& x) :
				TF_reference_allocator((F_target_allocator&)x.target_allocator_p_, x.name_)
			{



			}

			~TF_reference_allocator() {

				reset();
			}



		public:
			NCPP_FORCE_INLINE void* allocate(sz n, int flags = 0) {

				assert(target_allocator_p_ && "allocator reference is null, cant allocate memory");

				return target_allocator_p_->allocate(n, flags);
			}
			NCPP_FORCE_INLINE void* allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				assert(target_allocator_p_ && "allocator reference is null, cant allocate memory");

				return target_allocator_p_->allocate(n, alignment, alignment_offset, flags);
			}
			NCPP_FORCE_INLINE void  deallocate(void* p, sz n = 1) {

				assert(target_allocator_p_ && "allocator reference is null, cant deallocate memory");

				target_allocator_p_->deallocate(p, n);
			}

			NCPP_FORCE_INLINE void reset() {

                if constexpr (F_config::can_be_invalid)
                    if (!target_allocator_p_)
                        return;

				target_allocator_p_->reset();

				target_allocator_p_ = 0;

			}
			NCPP_FORCE_INLINE void clear() {

                if constexpr (F_config::can_be_invalid)
                    if (!target_allocator_p_)
                        return;

				target_allocator_p_->clear();

			}

		};

        using F_default_reference_allocator = TF_reference_allocator<>;

	}

}

