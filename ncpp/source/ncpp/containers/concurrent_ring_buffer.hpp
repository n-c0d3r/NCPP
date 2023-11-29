#pragma once

/** @file ncpp/containers/concurrent_ring_buffer.hpp
*	@brief Implements concurrent ring buffer.
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
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/binding_helper.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/pac/spinlock.hpp>

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

		template<typename F_item__, class F_allocator__ = mem::F_default_allocator, class F_lock__ = pac::F_spinlock>
		class TF_concurrent_ring_buffer {

		public:
			using F_item = F_item__;
			using F_allocator = F_allocator__;
			using F_lock = F_lock__;

			using F_item_vector = eastl::vector<F_item, F_allocator>;



		protected:
			F_item_vector item_vector_;
			aptrd begin_ = 0;
			aptrd end_ = 0;
			
		private:
			sz capacity_ = 0;
			F_lock reader_lock_;
			F_lock writer_lock_;


		public:
			NCPP_FORCE_INLINE sz size() const { return end_ - begin_; }
			NCPP_FORCE_INLINE sz capacity() const { return capacity_; }
			NCPP_FORCE_INLINE bool is_empty() const { return !size(); }
			NCPP_FORCE_INLINE bool is_null() const { return !capacity_; }



		public:
			inline TF_concurrent_ring_buffer() {



			}
			inline TF_concurrent_ring_buffer(sz capacity) :
				capacity_(capacity),
				item_vector_(capacity)
			{

				

			}

			inline TF_concurrent_ring_buffer(const TF_concurrent_ring_buffer& x) :
				item_vector_(x.item_vector_),
				capacity_(x.capacity_),
				begin_(x.begin_),
				end_(x.end_)
			{



			}
			inline TF_concurrent_ring_buffer& operator = (const TF_concurrent_ring_buffer& x) {

				item_vector_ = x.item_vector_;
				capacity_ = x.capacity_;
				begin_ = x.begin_;
				end_ = x.end_;

			}

			inline TF_concurrent_ring_buffer(TF_concurrent_ring_buffer&& x) :
				item_vector_(std::move(x.item_vector_)),
				capacity_(x.capacity_),
				begin_(x.begin_),
				end_(x.end_)
			{



			}
			inline TF_concurrent_ring_buffer& operator = (TF_concurrent_ring_buffer&& x) {

				item_vector_ = std::move(x.item_vector_);
				capacity_ = x.capacity_;
				begin_ = x.begin_;
				end_ = x.end_;

			}



		private:
			template<typename F_passed_item__>
			void T_push(F_passed_item__&& item) {

				writer_lock_.lock();

				assert(size() < capacity() && "out of capacity");

				item_vector_[(end_.fetch_add(1, eastl::memory_order_release)) % capacity_] = std::forward<F_passed_item__>(item);

				writer_lock_.unlock();

			}



		public:
			NCPP_FORCE_INLINE void push(F_item const& item) {

				T_push(std::forward<F_item const&>(item));
			}
			NCPP_FORCE_INLINE void push(F_item&& item) {

				T_push(std::forward<F_item>(item));
			}

			inline b8 try_pop(F_item& item) {

				reader_lock_.lock();

				ptrd end = end_.load(eastl::memory_order_acquire);
				ptrd begin = begin_.load(eastl::memory_order_acquire);

				if ((end - begin)> 0) {
				
					begin_.fetch_add(1, eastl::memory_order_acq_rel);

					item = std::move(item_vector_[begin % capacity_]);

					reader_lock_.unlock();

					return true;
				}

				reader_lock_.unlock();
				
				return false;
			}

			NCPP_FORCE_INLINE void reset() {

				begin_.store(0, eastl::memory_order_release);
				end_.store(0, eastl::memory_order_release);
			}

		};

	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_concurrent_ring_buffer<F_item__, F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_concurrent_ring_buffer<F_item__, F_new_allocator__>),
    typename F_item__,
    typename F_allocator__
);

