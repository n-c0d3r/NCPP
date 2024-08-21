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
#include <ncpp/mem/general_allocator.hpp>
#include <ncpp/mem/ephemeral_allocator.hpp>
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/eastl_bindings.hpp>
#include <ncpp/containers/binding_helper.hpp>
#include <ncpp/containers/view.hpp>
#include <ncpp/colorized_log.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/pac/srsw_spin_lock.hpp>

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

		template<typename F_item__, class F_allocator__ = mem::F_default_allocator, class F_pop_lock__ = pac::F_srsw_spin_lock>
		class TF_concurrent_ring_buffer {

		public:
			using F_item = F_item__;
			using F_allocator = F_allocator__;
			using F_pop_lock = F_pop_lock__;

			using F_item_vector = TF_vector<F_item, F_allocator>;
			using F_is_poppable_vector = TF_vector<b8, F_allocator>;



		protected:
			F_item_vector item_vector_;
			F_is_poppable_vector is_poppable_vector_;
			ai64 begin_index_ = 0;
			ai64 end_index_ = 0;
			F_pop_lock pop_lock_;

		private:
			i64 capacity_ = 0;


		public:
			NCPP_FORCE_INLINE i64 size() const { return end_index_.load(eastl::memory_order_acquire) - begin_index_.load(eastl::memory_order_acquire); }
			NCPP_FORCE_INLINE i64 capacity() const { return capacity_; }
			NCPP_FORCE_INLINE bool is_empty() const { return !size(); }
			NCPP_FORCE_INLINE bool is_null() const { return !capacity_; }
            NCPP_FORCE_INLINE i64 begin_index() const { return begin_index_.load(eastl::memory_order_acquire); }
            NCPP_FORCE_INLINE i64 end_index() const { return end_index_.load(eastl::memory_order_acquire); }
            NCPP_FORCE_INLINE const F_item_vector& item_vector() const { return item_vector_; }
            NCPP_FORCE_INLINE const F_is_poppable_vector& is_poppable_vector() const { return is_poppable_vector_; }



		public:
			NCPP_FORCE_INLINE TF_concurrent_ring_buffer() = default;
			TF_concurrent_ring_buffer(sz capacity) :
				capacity_(capacity),
				is_poppable_vector_(capacity, false)
			{
				item_vector_.reserve(capacity);
			}

			TF_concurrent_ring_buffer(const TF_concurrent_ring_buffer& x) :
				item_vector_(x.item_vector_),
				is_poppable_vector_(x.is_poppable_vector_),
				capacity_(x.capacity_),
				begin_index_(x.begin_index_.load(eastl::memory_order_acquire)),
				end_index_(x.end_index_.load(eastl::memory_order_acquire))
			{
			}
			TF_concurrent_ring_buffer& operator = (const TF_concurrent_ring_buffer& x) {

				item_vector_ = x.item_vector_;
				is_poppable_vector_ = x.is_poppable_vector_;
				capacity_ = x.capacity_;
				begin_index_.store(x.begin_index_.load(eastl::memory_order_acquire), eastl::memory_order_release);
				end_index_.store(x.end_index_.load(eastl::memory_order_acquire), eastl::memory_order_release);

                return *this;
			}

			TF_concurrent_ring_buffer(TF_concurrent_ring_buffer&& x) :
				item_vector_(std::move(x.item_vector_)),
				is_poppable_vector_(std::move(x.is_poppable_vector_)),
				capacity_(x.capacity_),
				begin_index_(x.begin_index_.load(eastl::memory_order_acquire)),
				end_index_(x.end_index_.load(eastl::memory_order_acquire))
			{
			}
			TF_concurrent_ring_buffer& operator = (TF_concurrent_ring_buffer&& x) {

				item_vector_ = std::move(x.item_vector_);
				is_poppable_vector_ = std::move(x.is_poppable_vector_);
				capacity_ = x.capacity_;
                begin_index_.store(x.begin_index_.load(eastl::memory_order_acquire), eastl::memory_order_release);
                end_index_.store(x.end_index_.load(eastl::memory_order_acquire), eastl::memory_order_release);

                return *this;
			}



		private:
			template<typename F_passed_item__>
			void T_push(F_passed_item__&& item)
			{
				NCPP_ASSERT(size() < capacity()) << "out of capacity";

				eastl::atomic_thread_fence(eastl::memory_order_release);

				// obtain a location
				i64 location = end_index_.fetch_add(1, eastl::memory_order_relaxed);
				location %= capacity_;

				// store item and mark this location as poppable
				new(item_vector_.data() + location) F_item(
					std::forward<F_passed_item__>(item)
				);
				is_poppable_vector_[location] = true;

				eastl::atomic_thread_fence(eastl::memory_order_acquire);
			}
			template<typename F_passed_item__>
			sz T_push_and_return_index(F_passed_item__&& item)
			{
				NCPP_ASSERT(size() < capacity()) << "out of capacity";

				eastl::atomic_thread_fence(eastl::memory_order_release);

				// obtain a location
				i64 location = end_index_.fetch_add(1, eastl::memory_order_relaxed);
				location %= capacity_;

				// store item and mark this location as poppable
				new(item_vector_.data() + location) F_item(
					std::forward<F_passed_item__>(item)
				);
				is_poppable_vector_[location] = true;

				eastl::atomic_thread_fence(eastl::memory_order_acquire);

				return location;
			}



		public:
			NCPP_FORCE_INLINE void push(F_item const& item) {

				T_push(std::forward<F_item const&>(item));
			}
			NCPP_FORCE_INLINE void push(F_item&& item) {

				T_push(std::forward<F_item>(item));
			}
			NCPP_FORCE_INLINE sz push_and_return_index(F_item const& item) {

				return T_push_and_return_index(std::forward<F_item const&>(item));
			}
			NCPP_FORCE_INLINE sz push_and_return_index(F_item&& item) {

				return T_push_and_return_index(std::forward<F_item>(item));
			}

			inline b8 try_pop(F_item& item) {

				pop_lock_.lock();

				eastl::atomic_thread_fence(eastl::memory_order_release);

				i64 end = end_index_.load(eastl::memory_order_relaxed);
				i64 begin = begin_index_.load(eastl::memory_order_relaxed);

				if (end > begin) {

					i64 location = begin % capacity_;

					// wait for the location to be poppable and then pop it
					while (!is_poppable_vector_[location]);
					item = std::move(*(item_vector_.data() + location));

					// mark this location as non-poppable
					// to be poppable again, it need to be re-pushed
					is_poppable_vector_[location] = false;

					//
					begin_index_.fetch_add(1, eastl::memory_order_relaxed);

					eastl::atomic_thread_fence(eastl::memory_order_acquire);

					pop_lock_.unlock();
					return true;
				}

				eastl::atomic_thread_fence(eastl::memory_order_acquire);

				pop_lock_.unlock();
				return false;
			}

			NCPP_FORCE_INLINE void reset() {

				sz begin = begin_index();
				sz end = end_index();

				for(sz i = begin; i < end; ++i)
				{
					sz location = i % capacity_;
					(item_vector_.data() + location)->~F_item();
				}

				begin_index_.store(0, eastl::memory_order_release);
				end_index_.store(0, eastl::memory_order_release);
			}



       public:
			friend std::ostream& operator << (
				std::ostream& os,
				const ncpp::TF_ostream_input<
                    TF_concurrent_ring_buffer
				>& input
			)
			{

				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW << "concurrent_ring_buffer"
					<< ncpp::T_cout_lowlight("(")
					<< ncpp::T_cout_lowlight("size: ")
					<< ncpp::T_cout_value(input.first.size())
					<< ncpp::T_cout_lowlight(")")
					<< " ";

				os << ncpp::T_cout_lowlight("{") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("begin_index") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.begin_index()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("end_index") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.end_index()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
				os << ncpp::T_cout_field_name("item_vector") << ncpp::T_cout_lowlight(" -> ");
				auto item_vector_for_logging = F_item_vector(
					input.first.item_vector_.data(),
					input.first.item_vector_.data() + input.first.capacity_
				);
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_ostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<F_item_vector>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<F_item_vector>
					> {
						ncpp::T_cout_value(item_vector_for_logging),
						input.second + 1
					}
				);

				os << std::endl;

				for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
				os << ncpp::T_cout_lowlight("}");

				return os;
			}

           	friend std::ostream& operator << (std::ostream& os, const TF_concurrent_ring_buffer& v)
			{

				os << ncpp::TF_ostream_input<TF_concurrent_ring_buffer> { v, 0 };

				return os;
			}



           	friend std::wostream& operator << (
				std::wostream& os,
				const ncpp::TF_ostream_input<
                    TF_concurrent_ring_buffer
				>& input
			)
			{

				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW_TEXT << L"concurrent_ring_buffer"
					<< ncpp::T_cout_lowlight("(")
					<< ncpp::T_cout_lowlight("size: ")
					<< ncpp::T_cout_value(input.first.size())
					<< ncpp::T_cout_lowlight(")")
					<< L" ";

				os << ncpp::T_cout_lowlight(L"{") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("begin_index") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.begin_index()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("end_index") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.end_index()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
				os << ncpp::T_cout_field_name("item_vector") << ncpp::T_cout_lowlight(" -> ");
				auto item_vector_for_logging = F_item_vector(
					input.first.item_vector_.data(),
					input.first.item_vector_.data() + input.first.capacity_
				);
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_wostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<F_item_vector>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<F_item_vector>
					> {
						ncpp::T_cout_value(item_vector_for_logging),
						input.second + 1
					}
				);

				os << std::endl;

				for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
				os << ncpp::T_cout_lowlight(L"}");

				return os;
			}

           	friend std::wostream& operator << (std::wostream& os, const TF_concurrent_ring_buffer& v)
			{

				os << ncpp::TF_ostream_input<TF_concurrent_ring_buffer> { v, 0 };

				return os;
			}

		};

		template<typename F_item__>
		using TG_concurrent_ring_buffer = TF_concurrent_ring_buffer<F_item__, mem::F_general_allocator>;
		template<typename F_item__>
		using TM_concurrent_ring_buffer = TF_concurrent_ring_buffer<F_item__, mem::F_ephemeral_allocator>;

		template<typename F_item__>
		using TV_concurrent_ring_buffer = TF_view<TG_concurrent_ring_buffer<F_item__>>;

	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_concurrent_ring_buffer<F_item__, F_allocator__, F_pop_lock__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_concurrent_ring_buffer<F_item__, F_new_allocator__, F_pop_lock__>),
    typename F_item__,
    typename F_allocator__,
    typename F_pop_lock__
);

