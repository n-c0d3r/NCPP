#pragma once

/** @file ncpp/containers/ring_buffer.hpp
*	@brief Implements ring buffer.
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

#include <ncpp/utilities/.hpp>
#include <ncpp/mem/default_allocator.hpp>
#include <ncpp/mem/general_allocator.hpp>
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/binding_helper.hpp>

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

	namespace containers {

		template<typename F_item__, class F_allocator__ = mem::F_default_allocator>
		class TF_ring_buffer {

		public:
			using F_item = F_item__;
			using F_allocator = F_allocator__;

			using F_item_vector = eastl::vector<F_item, F_allocator>;



		protected:
			F_item_vector item_vector_;
			
		private:
			sz capacity_ = 0;
			ptrd begin_ = 0;
			ptrd end_ = 0;

		public:
			NCPP_FORCE_INLINE sz size() const { return end_ - begin_; }
			NCPP_FORCE_INLINE sz capacity() const { return capacity_; }
			NCPP_FORCE_INLINE bool is_empty() const { return !size(); }
			NCPP_FORCE_INLINE bool is_null() const { return !capacity_; }



		public:
			inline TF_ring_buffer() {



			}
			inline TF_ring_buffer(sz capacity) :
				capacity_(capacity),
				item_vector_(capacity)
			{

				

			}

			inline TF_ring_buffer(const TF_ring_buffer& x) :
				item_vector_(x.item_vector_),
				capacity_(x.capacity_),
				begin_(x.begin_),
				end_(x.end_)
			{



			}
			inline TF_ring_buffer& operator = (const TF_ring_buffer& x) {

				item_vector_ = x.item_vector_;
				capacity_ = x.capacity_;
				begin_ = x.begin_;
				end_ = x.end_;

			}

			inline TF_ring_buffer(TF_ring_buffer&& x) :
				item_vector_(std::move(x.item_vector_)),
				capacity_(x.capacity_),
				begin_(x.begin_),
				end_(x.end_)
			{



			}
			inline TF_ring_buffer& operator = (TF_ring_buffer&& x) {

				item_vector_ = std::move(x.item_vector_);
				capacity_ = x.capacity_;
				begin_ = x.begin_;
				end_ = x.end_;

			}



		private:
			template<typename F_passed_item__>
			void T_push(F_passed_item__&& item) {

				item_vector_[(end_++) % capacity_] = std::forward<F_passed_item__>(item);

			}



		public:
			NCPP_FORCE_INLINE void push(F_item const& item) {

				T_push(std::forward<F_item const&>(item));
			}
			NCPP_FORCE_INLINE void push(F_item&& item) {

				T_push(std::forward<F_item>(item));
			}

			NCPP_FORCE_INLINE F_item pop() {

				assert(size() > 0 && "ring buffer is empty");

				return std::move(item_vector_[(begin_++) % capacity_]);
			}

			inline b8 try_pop(F_item& item) {

				if (size() > 0) {

					item = std::move(item_vector_[(begin_++) % capacity_]);

					return true;
				}
				
				return false;
			}

			NCPP_FORCE_INLINE void reset() {

				begin_ = 0;
				end_ = 0;
			}

		};

        template<typename F_item__>
        using TG_ring_buffer = TF_ring_buffer<F_item__, mem::F_general_allocator>;

	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_ring_buffer<F_item__, F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_ring_buffer<F_item__, F_new_allocator__>),
    typename F_item__,
    typename F_allocator__
);

