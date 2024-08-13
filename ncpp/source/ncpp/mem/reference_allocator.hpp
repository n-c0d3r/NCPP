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
        class TF_reference_allocator_config {

        public:
            static constexpr F_target_allocator__* default_p() {

                return 0;
            }
            static constexpr b8 can_be_invalid = std::is_same_v<F_target_allocator__, F_default_allocator>;
        	static constexpr b8 is_always_equal = std::is_same_v<F_target_allocator__, F_default_allocator>;
        	static constexpr NCPP_FORCE_INLINE b8 can_be_used(F_target_allocator__* x) {

        		if constexpr (can_be_invalid)
        			return true;

        		return x != 0;
        	}

        };



		/**
		 *	An allocator using another allocator to allocate and deallocate memory by referenceing into the target allocator reference.
		 *	@param <F_target_allocator__> the target allocator to use.
		 */
		template<typename F_target_allocator__ = F_default_allocator, class F_config__ = TF_reference_allocator_config<F_target_allocator__>>
		class TF_reference_allocator : public TA_allocator<TF_reference_allocator<F_target_allocator__>> {

		private:
			using F_base = TA_allocator<TF_reference_allocator<F_target_allocator__>>;
			using F_target_allocator = F_target_allocator__;

		public:
			using F_config = F_config__;



        public:
            static constexpr NCPP_FORCE_INLINE F_target_allocator__* default_p() { return F_config::default_p(); }



		private:
			F_target_allocator* target_allocator_p_ = 0;



		public:
            NCPP_FORCE_INLINE F_target_allocator* target_allocator_p() { return target_allocator_p_; }
            NCPP_FORCE_INLINE const F_target_allocator* target_allocator_p() const { return target_allocator_p_; }
			NCPP_FORCE_INLINE F_target_allocator& target_allocator() { return *target_allocator_p_; }
			NCPP_FORCE_INLINE const F_target_allocator& target_allocator() const { return *target_allocator_p_; }



		public:
            NCPP_FORCE_INLINE TF_reference_allocator(const char* name = 0) :
                TA_allocator<TF_reference_allocator<F_target_allocator__>>(name),
                target_allocator_p_(default_p())
			{
			}
            NCPP_FORCE_INLINE TF_reference_allocator(F_target_allocator& target_allocator, const char* name = 0) :
                TA_allocator<TF_reference_allocator<F_target_allocator__>>(name),
                target_allocator_p_(&target_allocator)
			{
			}
            NCPP_FORCE_INLINE TF_reference_allocator& operator = (F_target_allocator& target_allocator) noexcept
            {
                target_allocator_p_ = &target_allocator;
                return *this;
            }

            NCPP_FORCE_INLINE TF_reference_allocator(const TF_reference_allocator& x) :
				TF_reference_allocator((F_target_allocator&)x.target_allocator(), x.name())
			{
			}
            NCPP_FORCE_INLINE TF_reference_allocator& operator = (const TF_reference_allocator& x) noexcept
            {
                target_allocator_p_ = (F_target_allocator*)x.target_allocator_p_;

#ifdef NCPP_ENABLE_ALLOCATOR_INFO
                reinterpret_cast<F_base*>(this)->set_name(x.name());
#endif

                return *this;
            }

			~TF_reference_allocator() {

                unreference();
            }



		public:
			NCPP_FORCE_INLINE b8 operator == (const TF_reference_allocator& x) const noexcept {

				if constexpr (F_config::is_always_equal)
					return true;

				return (target_allocator_p_ == x.target_allocator_p());
			}



		public:
			NCPP_FORCE_INLINE void* allocate(sz n, int flags = 0) {

				NCPP_ASSERT(F_config::can_be_used(target_allocator_p_))
					<< "target allocator can't be used";

				return target_allocator_p_->allocate(n, flags);
			}
			NCPP_FORCE_INLINE void* allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				NCPP_ASSERT(F_config::can_be_used(target_allocator_p_))
					<< "target allocator can't be used";

				return target_allocator_p_->allocate(n, alignment, alignment_offset, flags);
			}
			NCPP_FORCE_INLINE void  deallocate(void* p, sz n = 1) {

				NCPP_ASSERT(F_config::can_be_used(target_allocator_p_))
					<< "target allocator can't be used";

				target_allocator_p_->deallocate(p, n);
			}

			NCPP_FORCE_INLINE void reset() {

				if(!F_config::can_be_used(target_allocator_p_))
					return;

				target_allocator_p_->reset();

			}
			NCPP_FORCE_INLINE void clear() {

                if(!F_config::can_be_used(target_allocator_p_))
                    return;

				target_allocator_p_->clear();

			}

            NCPP_FORCE_INLINE void unreference() {

                target_allocator_p_ = default_p();

            }

		};

        using F_default_reference_allocator = TF_reference_allocator<>;

	}

}

