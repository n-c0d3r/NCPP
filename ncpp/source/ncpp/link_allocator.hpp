#pragma once

/** @file ncpp/link_allocator.hpp
*	@brief Implements link allocator.
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

#include <ncpp/allocator_base.hpp>

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

	/**
	 *	An allocator using another allocator to allocate and deallocate memory by linking into the target allocator reference.
	 *	@param <target_allocator_type__> the target allocator to use.
	 */
	template<typename target_allocator_type__>
	class TF_link_allocator : public TI_allocator<TF_link_allocator<target_allocator_type__>> {

	public:
		using target_allocator_type = target_allocator_type__;



	private:
		target_allocator_type* target_allocator_p_;



	public:
		inline target_allocator_type& target_allocator() { return *target_allocator_p_; }
		inline const target_allocator_type& target_allocator() const { return *target_allocator_p_; }



	public:
		inline TF_link_allocator(const char* name = 0) :
			TI_allocator<TF_link_allocator<target_allocator_type__>>(name)
		{



		}
		inline TF_link_allocator(target_allocator_type& target_allocator, const char* name = 0) :
			TI_allocator<TF_link_allocator<target_allocator_type__>>(name),
			target_allocator_p_(&target_allocator)
		{



		}
		inline TF_link_allocator(const TF_link_allocator& x) :
			TF_link_allocator(x.target_allocator(), x.name_)
		{



		}

		~TF_link_allocator() {

			reset();
		}

		

	public:
		inline void* new_mem(sz size) {

			assert(target_allocator_p_);

			return target_allocator_p_->new_mem(size);
		}
		inline void delete_mem(void* p) {

			assert(target_allocator_p_);

			target_allocator_p_->delete_mem(p);
		}

		inline void reset() {

			if (!target_allocator_p_)
				return;

			target_allocator_p_->reset();

			target_allocator_p_ = 0;

		}
		inline void clear() {

			if (!target_allocator_p_)
				return;

			target_allocator_p_->clear();

		}

	};

}

