#pragma once

/** @file ncpp/containers/hash_table.hpp
*	@brief Implements hash table.
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

        template<typename F_int__ = u32, class F_allocator__ = mem::F_default_allocator>
        class TF_hash_table {
            
        public:
            using F_int = F_int__;
            using F_allocator = F_allocator__;

            using F_vector = TF_vector<F_int, F_allocator>;
            using V_vector = TF_view<F_vector>;

            
            
        private:
            F_int hash_size_ = 2;
            F_int index_size_ = 0;
            
            F_int hash_mask_ = 0;

            F_vector hash_vector_;
            F_vector index_vector_;
            
        public:
            NCPP_FORCE_INLINE F_int hash_size() const { return hash_size_; }
            NCPP_FORCE_INLINE F_int index_size() const { return index_size_; }
            
            NCPP_FORCE_INLINE F_int hash_mask() const { return hash_mask_; }
            
            NCPP_FORCE_INLINE V_vector hash_vector() const { return hash_vector_; }
            NCPP_FORCE_INLINE V_vector index_vector() const { return index_vector_; }
            
            
            
        public:
            inline TF_hash_table(F_int hash_size = 2, F_int index_size = 0, const F_allocator& allocator = F_allocator()) :
                hash_size_(hash_size),
                index_size_(index_size),

				hash_mask_(hash_size_ - 1),

                hash_vector_(allocator),
                index_vector_(allocator)
            {
                
				NCPP_ASSERT(hash_size_ > 0) << "hash size must be greater than zero";
				NCPP_ASSERT(utilities::is_power_of_two(static_cast<f32>(hash_size_))) << "hash size must be power of two";
                
                if(index_size > 0) {
                    
                    hash_vector_.resize(hash_size_, 0);
                    index_vector_.resize(index_size_, 0xFFFFFFFF);
                    
                }
                
            }
            inline TF_hash_table(const TF_hash_table& x) :
                hash_size_(x.hash_size_),
                index_size_(x.index_size_),
            
                hash_vector_(x.hash_size_),
                index_vector_(x.index_size_)
            {
                
                
                
            }
            inline TF_hash_table& operator = (const TF_hash_table& x)
            {
                
                hash_size_ = x.hash_size_;
                index_size_ = x.index_size_;
                
                hash_vector_ = x.hash_vector_;
                index_vector_ = x.index_vector_;
                
                return *this;
            }
            inline TF_hash_table(TF_hash_table&& x) :
                hash_size_(x.hash_size_),
                index_size_(x.index_size_),
            
                hash_vector_(std::move(x.hash_size_)),
                index_vector_(std::move(x.index_size_))
            {
                
                
                
            }
            inline TF_hash_table& operator = (TF_hash_table&& x)
            {
                
                hash_size_ = x.hash_size_;
                index_size_ = x.index_size_;
                
                hash_vector_ = std::move(x.hash_vector_);
                index_vector_ = std::move(x.index_vector_);
                
                return *this;
            }
            ~TF_hash_table(){
                
                reset();
                
            }
            
            
            
        public:
            inline void reset(){
                
                if(index_size_) {
                    
                    hash_vector_.clear();
                    index_vector_.clear();
                    
                    hash_size_ = 2;
                    index_size_ = 2;
                    
                }
                
            }
            inline void clear(){
                
                if(index_size_) {
                    
                    hash_vector_.resize(hash_size_, 0xFFFFFFFF);
                    
                }
                
            }
            inline void clear(F_int hash_size, F_int index_size){
                
                reset();
                
                hash_size_ = hash_size;
                index_size_ = index_size;
                
                NCPP_ASSERT(hash_size_ > 0) << "hash size must be greater than zero";
                NCPP_ASSERT(utilities::is_power_of_two(hash_size_)) << "hash size must be power of two";
                
                if( index_size_ )
                {
                    hash_mask_ = hash_size_ - 1;
                    
                    hash_vector_.resize(hash_size_, 0);
                    index_vector_.resize(index_size_, 0xFFFFFFFF);
                    
                }
                
            }
            inline void resize(F_int index_size) {
                
                if( index_size_ == index_size )
                {
                    return;
                }

                if( index_size == 0 )
                {
                    reset();
                    return;
                }

                if( index_size_ == 0 )
                {
                    hash_mask_ = (hash_size_ - 1);
                    hash_vector_.resize(hash_size_, 0xFFFFFFFF);
                }
                
                index_vector_.resize(index_size);

                index_size_ = index_size;
                
            }
            NCPP_FORCE_INLINE F_int first(F_int key) const {
                
                return hash_vector_[key & hash_mask_];
            }
            NCPP_FORCE_INLINE F_int next(F_int index) const {
                
                NCPP_ASSERT(index < index_size_);
                NCPP_ASSERT(index_vector_[index] != index);
                return index_vector_[index];
            }
            NCPP_FORCE_INLINE b8 is_valid(F_int index) const {
                
                return index != ~0u;
            }
            inline void add(F_int key, F_int index){

                NCPP_DISABLE_ALL_WARNINGS_PUSH
                if( index >= index_size_ )
                {
                    resize(utilities::round_up_to_power_of_two(static_cast<f32>(index + 1)));
                }
                NCPP_DISABLE_ALL_WARNINGS_POP

                key &= hash_mask_;
                index_vector_[index] = hash_vector_[key];
                hash_vector_[key] = index;

            }
            inline void add_concurrent(F_int key, F_int index){
                NCPP_ASSERT(index < index_size_);

                key &= hash_mask_;
                index_vector_[index] = EA::Thread::AtomicFetchSwap((i32*)(hash_vector_.data() + key), index);
            }
            inline void remove(F_int key, F_int index){
                
                if(index >= index_size_)
                {
                    return;
                }

                key &= hash_mask_;

                if(hash_vector_[key] == index)
                {
                    // Head of chain
                    hash_vector_[key] = index_vector_[index];
                }
                else
                {
                    for(F_int i = hash_vector_[key]; is_valid(i); i = index_vector_[i])
                    {
                        if(index_vector_[i] == index)
                        {
                            // Next = Next->Next
                            index_vector_[i] = index_vector_[index];
                            break;
                        }
                    }
                }
                
            }



       public:
			friend std::ostream& operator << (
				std::ostream& os,
				const ncpp::TF_ostream_input<
                    TF_hash_table
				>& input
			)
			{

				if (input.second > (F_int)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW << "hash_table"
					<< " ";

				os << ncpp::T_cout_lowlight("{") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("hash_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.hash_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("index_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.index_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("hash_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_ostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.hash_vector_),
						input.second + 1
					}
				);
				os << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("index_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_ostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.index_vector_),
						input.second + 1
					}
				);
				os << std::endl;

				for (F_int j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
				os << ncpp::T_cout_lowlight("}");

				return os;
			}

           	friend std::ostream& operator << (std::ostream& os, const TF_hash_table& v)
			{

				os << ncpp::TF_ostream_input<TF_hash_table> { v, 0 };

				return os;
			}



           	friend std::wostream& operator << (
				std::wostream& os,
				const ncpp::TF_ostream_input<
                    TF_hash_table
				>& input
			)
			{

				if (input.second > (F_int)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW_TEXT << L"hash_table"
					<< L" ";

				os << ncpp::T_cout_lowlight(L"{") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("hash_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.hash_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("index_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.index_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("hash_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_wostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.hash_vector_),
						input.second + 1
					}
				);
				os << ncpp::T_cout_lowlight(",") << std::endl;

				for (F_int j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("index_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_wostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<TF_vector<F_int, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.index_vector_),
						input.second + 1
					}
				);
				os << std::endl;

				for (F_int j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
				os << ncpp::T_cout_lowlight(L"}");

				return os;
			}

           	friend std::wostream& operator << (std::wostream& os, const TF_hash_table& v)
			{

				os << ncpp::TF_ostream_input<TF_hash_table> { v, 0 };

				return os;
			}
            
        };
    
    
    
        using F_hash_table = TF_hash_table<>;

        using G_hash_table = TF_hash_table<u32, mem::F_general_allocator>;
        using M_hash_table = TF_hash_table<u32, mem::F_ephemeral_allocator>;

        using V_hash_table = TF_view<G_hash_table>;
    
	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_hash_table<F_int__, F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_hash_table<F_int__, F_new_allocator__>),
    typename F_int__,
    typename F_allocator__
);

