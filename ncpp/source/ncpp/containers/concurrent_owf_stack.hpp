#pragma once

/** @file ncpp/containers/concurrent_owf_stack.hpp
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
#include <ncpp/containers/eastl_bindings.hpp>
#include <ncpp/containers/binding_helper.hpp>
#include <ncpp/containers/view.hpp>
#include <ncpp/colorized_log.hpp>

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
		class TF_concurrent_owf_stack {

		public:
			using F_item = F_item__;
			using F_allocator = F_allocator__;

			using F_item_vector = TF_vector<F_item, F_allocator>;



		protected:
			F_item_vector item_vector_;

		private:
			sz capacity_ = 0;
			asz end_index_ = 0;

		public:
			NCPP_FORCE_INLINE sz size() const { return end_index_.load(eastl::memory_order_acquire); }
			NCPP_FORCE_INLINE sz capacity() const { return capacity_; }
			NCPP_FORCE_INLINE bool is_empty() const { return !size(); }
			NCPP_FORCE_INLINE bool is_null() const { return !capacity_; }
            NCPP_FORCE_INLINE sz end_index() const { return end_index_.load(eastl::memory_order_acquire); }
            NCPP_FORCE_INLINE const F_item_vector& item_vector() const noexcept { return item_vector_; }
			NCPP_FORCE_INLINE F_item_vector& item_vector() noexcept { return item_vector_; }
			NCPP_FORCE_INLINE TG_span<const F_item> item_span() const noexcept
			{
				return { item_vector_.data(), end_index() };
			}
			NCPP_FORCE_INLINE TG_span<F_item> item_span() noexcept
			{
				return { item_vector_.data(), end_index() };
			}



		public:
			NCPP_FORCE_INLINE TF_concurrent_owf_stack() noexcept = default;
			TF_concurrent_owf_stack(sz capacity) :
				capacity_(capacity)
			{
				item_vector_.reserve(capacity);
			}

			TF_concurrent_owf_stack(const TF_concurrent_owf_stack& x) :
				item_vector_(x.item_vector_),
				capacity_(x.capacity_),
				end_index_(x.end_index())
			{
			}
			TF_concurrent_owf_stack& operator = (const TF_concurrent_owf_stack& x) {

				item_vector_ = x.item_vector_;
				capacity_ = x.capacity_;
				end_index_ = x.end_index();

                return *this;
			}

			TF_concurrent_owf_stack(TF_concurrent_owf_stack&& x) :
				item_vector_(std::move(x.item_vector_)),
				capacity_(x.capacity_),
				end_index_(x.end_index())
			{
			}
			TF_concurrent_owf_stack& operator = (TF_concurrent_owf_stack&& x) {

				item_vector_ = std::move(x.item_vector_);
				capacity_ = x.capacity_;
				end_index_ = x.end_index();

                return *this;
			}



		private:
			template<typename F_passed_item__>
			void T_push(F_passed_item__&& item) {

				sz location = end_index_.fetch_add(1, eastl::memory_order_relaxed);

				new(item_vector_.data() + location) F_item(
					std::forward<F_passed_item__>(item)
				);

				NCPP_ASSERT(location < capacity_) << "capacity exceeded";
			}
			template<typename F_passed_item__>
			sz T_push_and_return_index(F_passed_item__&& item) {

				sz location = end_index_.fetch_add(1, eastl::memory_order_relaxed);

				new(item_vector_.data() + location) F_item(
					std::forward<F_passed_item__>(item)
				);

				NCPP_ASSERT(location < capacity_);

				NCPP_ASSERT(location < capacity_) << "capacity exceeded";

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

			NCPP_FORCE_INLINE void reset() {

				sz end_index = end_index_.load(eastl::memory_order_relaxed);
				for(u32 i = 0; i < end_index; ++i)
				{
					(item_vector_.data() + i)->~F_item();
				}

				end_index_.store(0, eastl::memory_order_relaxed);
			}



       public:
			friend std::ostream& operator << (
				std::ostream& os,
				const ncpp::TF_ostream_input<
                    TF_concurrent_owf_stack
				>& input
			)
			{
				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW << "concurrent_concurrent_owf_stack"
					<< ncpp::T_cout_lowlight("(")
					<< ncpp::T_cout_lowlight("size: ")
					<< ncpp::T_cout_value(input.first.size())
					<< ncpp::T_cout_lowlight(")")
					<< " ";

				os << ncpp::T_cout_lowlight("{") << std::endl;

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

           	friend std::ostream& operator << (std::ostream& os, const TF_concurrent_owf_stack& v)
			{

				os << ncpp::TF_ostream_input<TF_concurrent_owf_stack> { v, 0 };

				return os;
			}



           	friend std::wostream& operator << (
				std::wostream& os,
				const ncpp::TF_ostream_input<
                    TF_concurrent_owf_stack
				>& input
			)
			{
				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW_TEXT << L"concurrent_concurrent_owf_stack"
					<< ncpp::T_cout_lowlight("(")
					<< ncpp::T_cout_lowlight("size: ")
					<< ncpp::T_cout_value(input.first.size())
					<< ncpp::T_cout_lowlight(")")
					<< L" ";

				os << ncpp::T_cout_lowlight(L"{") << std::endl;

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

           	friend std::wostream& operator << (std::wostream& os, const TF_concurrent_owf_stack& v)
			{

				os << ncpp::TF_ostream_input<TF_concurrent_owf_stack> { v, 0 };

				return os;
			}

		};

        template<typename F_item__>
        using TG_concurrent_owf_stack = TF_concurrent_owf_stack<F_item__, mem::F_general_allocator>;
        template<typename F_item__>
        using TM_concurrent_owf_stack = TF_concurrent_owf_stack<F_item__, mem::F_ephemeral_allocator>;

        template<typename F_item__>
        using TV_concurrent_owf_stack = TF_view<TG_concurrent_owf_stack<F_item__>>;

	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_concurrent_owf_stack<F_item__, F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_concurrent_owf_stack<F_item__, F_new_allocator__>),
    typename F_item__,
    typename F_allocator__
);

