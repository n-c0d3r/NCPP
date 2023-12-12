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

        template<class F_allocator__ = mem::F_default_allocator>
        class TF_hash_table {
            
        public:
            using F_allocator = F_allocator__;
            
            
            
        private:
            u32 hash_size_ = 2;
            u32 index_size_ = 0;
            
            u32 hash_mask_ = 0;
            
            eastl::vector<u32, F_allocator> hash_vector_;
            eastl::vector<u32, F_allocator> index_vector_;
            
        public:
            NCPP_FORCE_INLINE u32 hash_size() const { return hash_size_; }
            NCPP_FORCE_INLINE u32 index_size() const { return index_size_; }
            
            NCPP_FORCE_INLINE u32 hash_mask() const { return hash_mask_; }
            
            NCPP_FORCE_INLINE const eastl::vector<u32, F_allocator>& hash_vector() const { return hash_vector_; }
            NCPP_FORCE_INLINE const eastl::vector<u32, F_allocator>& index_vector() const { return index_vector_; }
            
            
            
        public:
            inline TF_hash_table(u32 hash_size = 2, u32 index_size = 0, const F_allocator& allocator = F_allocator()) :
                hash_size_(hash_size),
                index_size_(index_size),

				hash_mask_(hash_size_ - 1),

                hash_vector_(allocator),
                index_vector_(allocator)
            {
                
				assert(hash_size_ > 0 && "hash size must be greater than zero");
				assert(utilities::is_power_of_two(static_cast<f32>(hash_size_)) && "hash size must be power of two");
                
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
            inline void clear(u32 hash_size, u32 index_size){
                
                reset();
                
                hash_size_ = hash_size;
                index_size_ = index_size;
                
                assert(hash_size_ > 0 && "hash size must be greater than zero");
                assert(utilities::is_power_of_two(hash_size_) && "hash size must be power of two");
                
                if( index_size_ )
                {
                    hash_mask_ = hash_size_ - 1;
                    
                    hash_vector_.resize(hash_size_, 0);
                    index_vector_.resize(index_size_, 0xFFFFFFFF);
                    
                }
                
            }
            inline void resize(u32 index_size) {
                
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
            NCPP_FORCE_INLINE u32 first(u32 key) const {
                
                return hash_vector_[key & hash_mask_];
            }
            NCPP_FORCE_INLINE u32 next(u32 index) const {
                
                assert(index < index_size_);
                assert(index_vector_[index] != index);
                return index_vector_[index];
            }
            NCPP_FORCE_INLINE b8 is_valid(u32 index) const {
                
                return index != ~0u;
            }
            inline void add(u32 key, u32 index){
                
                if( index >= index_size_ )
                {
                    resize(utilities::round_up_to_power_of_two(static_cast<f32>(index + 1)));
                }

                key &= hash_mask_;
                index_vector_[index] = hash_vector_[key];
                hash_vector_[key] = index;

            }
            inline void add_concurrent(u32 key, u32 index){
                assert(index < index_size_);

                key &= hash_mask_;
                index_vector_[index] = EA::Thread::AtomicFetchSwap((i32*)(hash_vector_.data() + key), index);
            }
            inline void remove(u32 key, u32 index){
                
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
                    for(u32 i = hash_vector_[key]; is_valid(i); i = index_vector_[i])
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

				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW << "hash_table"
					<< " ";

				os << ncpp::T_cout_lowlight("{") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("hash_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.hash_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("index_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.index_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("hash_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_ostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.hash_vector_),
						input.second + 1
					}
				);
				os << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << " ";

				}
        		os << ncpp::T_cout_field_name("index_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_ostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.index_vector_),
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

				if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

					os << ncpp::T_cout_lowlight(L"...");

					return os;
				}

				os << NCPP_FOREGROUND_YELLOW_TEXT << L"hash_table"
					<< L" ";

				os << ncpp::T_cout_lowlight(L"{") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("hash_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.hash_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("index_size") << ncpp::T_cout_lowlight(" -> ") << ncpp::T_cout_value(input.first.index_size()) << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("hash_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_wostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.hash_vector_),
						input.second + 1
					}
				);
				os << ncpp::T_cout_lowlight(",") << std::endl;

				for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

					os << L" ";

				}
        		os << ncpp::T_cout_field_name("index_vector") << ncpp::T_cout_lowlight(" -> ");
				ncpp::T_safe_ostream_with_tab<
					ncpp::F_wostream,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					>
				>(
					os,
					ncpp::TF_ostream_input<
						ncpp::TF_cout_value<eastl::vector<u32, F_allocator>>
					> {
						ncpp::T_cout_value(input.first.index_vector_),
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

           	friend std::wostream& operator << (std::wostream& os, const TF_hash_table& v)
			{

				os << ncpp::TF_ostream_input<TF_hash_table> { v, 0 };

				return os;
			}
            
        };
    
    
    
        using F_hash_table = TF_hash_table<>;

        using G_hash_table = TF_hash_table<mem::F_general_allocator>;
        using EP_hash_table = TF_hash_table<mem::F_ephemeral_allocator>;

        using V_hash_table = TF_view<G_hash_table>;
    
	}

}

NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_hash_table<F_allocator__>),
    NCPP_MA(F_allocator__),
    NCPP_MA(ncpp::containers::TF_hash_table<F_new_allocator__>),
    typename F_allocator__
);

