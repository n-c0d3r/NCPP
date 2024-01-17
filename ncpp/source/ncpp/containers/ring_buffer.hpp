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
		class TF_ring_buffer {

		public:
			using F_item = F_item__;
			using F_allocator = F_allocator__;

			using F_item_vector = TF_vector<F_item, F_allocator>;



		protected:
			F_item_vector item_vector_;
			
		private:
			sz capacity_ = 0;
			ptrd begin_index_ = 0;
			ptrd end_index_ = 0;

		public:
			NCPP_FORCE_INLINE sz size() const { return end_index_ - begin_index_; }
			NCPP_FORCE_INLINE sz capacity() const { return capacity_; }
			NCPP_FORCE_INLINE bool is_empty() const { return !size(); }
			NCPP_FORCE_INLINE bool is_null() const { return !capacity_; }
            NCPP_FORCE_INLINE ptrd begin_index() const { return begin_index_; }
            NCPP_FORCE_INLINE ptrd end_index() const { return end_index_; }
            NCPP_FORCE_INLINE TF_view<F_item_vector> item_vector() const { return item_vector_; }



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
				begin_index_(x.begin_index_),
				end_index_(x.end_index_)
			{



			}
			inline TF_ring_buffer& operator = (const TF_ring_buffer& x) {

				item_vector_ = x.item_vector_;
				capacity_ = x.capacity_;
				begin_index_ = x.begin_index_;
				end_index_ = x.end_index_;

                return *this;
			}

			inline TF_ring_buffer(TF_ring_buffer&& x) :
				item_vector_(std::move(x.item_vector_)),
				capacity_(x.capacity_),
				begin_index_(x.begin_index_),
				end_index_(x.end_index_)
			{



			}
			inline TF_ring_buffer& operator = (TF_ring_buffer&& x) {

				item_vector_ = std::move(x.item_vector_);
				capacity_ = x.capacity_;
				begin_index_ = x.begin_index_;
				end_index_ = x.end_index_;

                return *this;
			}



		private:
			template<typename F_passed_item__>
			void T_push(F_passed_item__&& item) {

				item_vector_[(end_index_++) % capacity_] = std::forward<F_passed_item__>(item);

			}



		public:
			NCPP_FORCE_INLINE void push(F_item const& item) {

				T_push(std::forward<F_item const&>(item));
			}
			NCPP_FORCE_INLINE void push(F_item&& item) {

				T_push(std::forward<F_item>(item));
			}

			NCPP_FORCE_INLINE F_item pop() {

				NCPP_ASSERT(size() > 0) << "ring buffer is empty";

				return std::move(item_vector_[(begin_index_++) % capacity_]);
			}

			inline b8 try_pop(F_item& item) {

				if (size() > 0) {

					item = std::move(item_vector_[(begin_index_++) % capacity_]);

					return true;
				}
				
				return false;
			}

			NCPP_FORCE_INLINE void reset() {

				begin_index_ = 0;
				end_index_ = 0;
			}



       public:
			friend std::ostream& operator << (
				std::ostream& os,
				const ncpp::TF_ostream_input<
                    TF_ring_buffer
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
						ncpp::T_cout_value(input.first.item_vector_),
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

           	friend std::ostream& operator << (std::ostream& os, const TF_ring_buffer& v)
			{

				os << ncpp::TF_ostream_input<TF_ring_buffer> { v, 0 };

				return os;
			}



           	friend std::wostream& operator << (
				std::wostream& os,
				const ncpp::TF_ostream_input<
                    TF_ring_buffer
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
						ncpp::T_cout_value(input.first.item_vector_),
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

           	friend std::wostream& operator << (std::wostream& os, const TF_ring_buffer& v)
			{

				os << ncpp::TF_ostream_input<TF_ring_buffer> { v, 0 };

				return os;
			}

		};

        template<typename F_item__>
        using TG_ring_buffer = TF_ring_buffer<F_item__, mem::F_general_allocator>;
        template<typename F_item__>
        using TM_ring_buffer = TF_ring_buffer<F_item__, mem::F_ephemeral_allocator>;

        template<typename F_item__>
        using TV_ring_buffer = TF_view<TG_ring_buffer<F_item__>>;

	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_ring_buffer<F_item__, F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_ring_buffer<F_item__, F_new_allocator__>),
    typename F_item__,
    typename F_allocator__
);

