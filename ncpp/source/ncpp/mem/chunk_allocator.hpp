#pragma once

/** @file ncpp/mem/chunk_allocator.hpp
*	@brief Implements chunk allocator.
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

#include <ncpp/containers/ring_buffer.hpp>

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

		struct NCPP_ALIGN(EASTL_ALLOCATOR_MIN_ALIGNMENT) F_chunk_header {

			sz usage = 0;
			sz allocation_count = 0;
			F_chunk_header* prev_p = 0;
			F_chunk_header* next_p = 0;

			NCPP_FORCE_INLINE u8* data_root() {

				return reinterpret_cast<u8*>(this + 1);
			}

			NCPP_FORCE_INLINE u8* current_data() {

				return data_root() + usage;
			}

		};



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<class F_options__>
        class TF_chunk_storage;
        template<class F_options__>
        class TF_chunk_adaptor;
        template<class F_options__>
        class TF_chunk_allocator;



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		struct F_default_chunk_options {

			using F_global_chunk_p_ring_buffer = containers::TF_ring_buffer<F_chunk_header*, F_default_allocator>;
			using F_local_chunk_p_ring_buffer = containers::TF_ring_buffer<F_chunk_header*, F_default_allocator>;

            using F_allocator_for_chunks = F_default_allocator;

            struct F_storage_addtional_data {};



            static constexpr b8 enable_allocation_counting_inside_chunks = true;
            static constexpr b8 chunks_in_a_single_block = true;



            static NCPP_FORCE_INLINE void pre_push_chunk(void* storage_p) noexcept {}
            static NCPP_FORCE_INLINE void post_push_chunk(void* storage_p) noexcept {}
            static NCPP_FORCE_INLINE void pre_pop_chunk(void* storage_p) noexcept {}
            static NCPP_FORCE_INLINE void post_pop_chunk(void* storage_p) noexcept {}

            static NCPP_FORCE_INLINE void pre_push_chunk_with_chunk_p(void* storage_p, F_chunk_header* chunk_p) noexcept {}
            static NCPP_FORCE_INLINE void post_push_chunk_with_chunk_p(void* storage_p, F_chunk_header* chunk_p) noexcept {}
            static NCPP_FORCE_INLINE void post_pop_chunk_with_chunk_p(void* storage_p, F_chunk_header* chunk_p) noexcept {}

		};



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<class F_options__ = F_default_chunk_options>
        class TF_chunk_storage;
        template<class F_options__ = F_default_chunk_options>
        class TF_chunk_adaptor;
        template<class F_options__ = F_default_chunk_options>
        class TF_chunk_allocator;



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define NCPP_CHUNK_STORAGE_DEFAULT_MAX_CHUNK_COUNT 512
#define NCPP_CHUNK_ADAPTOR_DEFAULT_MAX_CHUNK_COUNT 16

		// Default smart chunk capacity, 256KiB
#define NCPP_DEFAULT_CHUNK_CAPACITY 256144



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		template<class F_options__>
		class TF_chunk_storage {

		public:
			using F_options = F_options__;
			using F_storage = TF_chunk_storage<F_options>;
			using F_adaptor = TF_chunk_adaptor<F_options>;
			using F_allocator = TF_chunk_allocator<F_options>;
			using F_global_chunk_p_ring_buffer = typename F_options::F_global_chunk_p_ring_buffer;
			using F_local_chunk_p_ring_buffer = typename F_options::F_local_chunk_p_ring_buffer;
            using F_allocator_for_chunks = typename F_options::F_allocator_for_chunks;
            using F_storage_addtional_data = typename F_options::F_storage_addtional_data;



        private:
            static_assert(
                !(!F_options::chunks_in_a_single_block && F_options::enable_allocation_counting_inside_chunks),
                "invalid options, allocation counting can only be enabled when chunks in a single block is enabled"
            );



		private:
			sz max_chunk_count_ = 0;
			sz chunk_capacity_ = 0;
			sz chunk_size_ = 0;
			sz max_total_size_ = 0;

			F_global_chunk_p_ring_buffer chunk_p_ring_buffer_;

			F_chunk_header* first_chunk_p_ = 0;

            F_allocator_for_chunks allocator_for_chunks_;

        public:
            F_storage_addtional_data addtional_data;

		public:
			NCPP_FORCE_INLINE sz max_chunk_count() const noexcept { return max_chunk_count_; }
			NCPP_FORCE_INLINE sz chunk_capacity() const noexcept { return chunk_capacity_; }
			NCPP_FORCE_INLINE sz chunk_size() const noexcept { return chunk_size_; }
			NCPP_FORCE_INLINE sz max_total_size() const noexcept { return max_total_size_; }

			NCPP_FORCE_INLINE const F_global_chunk_p_ring_buffer& chunk_p_ring_buffer() const noexcept { return chunk_p_ring_buffer_; }

            NCPP_FORCE_INLINE F_allocator_for_chunks& allocator_for_chunks() noexcept { return allocator_for_chunks_; }
            NCPP_FORCE_INLINE const F_allocator_for_chunks& allocator_for_chunks() const noexcept { return allocator_for_chunks_; }



		public:
			NCPP_FORCE_INLINE TF_chunk_storage(sz max_chunk_count = NCPP_CHUNK_STORAGE_DEFAULT_MAX_CHUNK_COUNT, sz chunk_capacity = NCPP_DEFAULT_CHUNK_CAPACITY) :
                chunk_p_ring_buffer_(max_chunk_count),

                max_chunk_count_(max_chunk_count),
                chunk_capacity_(aligned_size(chunk_capacity)),
                chunk_size_(chunk_capacity_ + sizeof(F_chunk_header)),
                max_total_size_((chunk_capacity_ + sizeof(F_chunk_header)) * max_chunk_count)
			{

				NCPP_ASSERT(max_chunk_count) << "chunk count is equal to zero, cant create storage";

				init_chunks_internal();

			}
            NCPP_FORCE_INLINE TF_chunk_storage(F_allocator_for_chunks& allocator_for_chunks, sz max_chunk_count = NCPP_CHUNK_STORAGE_DEFAULT_MAX_CHUNK_COUNT, sz chunk_capacity = NCPP_DEFAULT_CHUNK_CAPACITY) :
                chunk_p_ring_buffer_(max_chunk_count),

                max_chunk_count_(max_chunk_count),
                chunk_capacity_(aligned_size(chunk_capacity)),
                chunk_size_(chunk_capacity_ + sizeof(F_chunk_header)),
                max_total_size_((chunk_capacity_ + sizeof(F_chunk_header)) * max_chunk_count),

                allocator_for_chunks_(allocator_for_chunks)
            {

                NCPP_ASSERT(max_chunk_count) << "chunk count is equal to zero, cant create storage";

                init_chunks_internal();

            }
			~TF_chunk_storage() {

				release_internal();

			}



		private:
			void init_chunks_internal() {

				first_chunk_p_ = reinterpret_cast<F_chunk_header*>(allocator_for_chunks_.allocate(chunk_size() * max_chunk_count_));

                rebuild_chunks_internal();

			}

			void release_internal() {

                allocator_for_chunks_.deallocate(first_chunk_p_);

			}

			void rebuild_chunks_internal() {

				chunk_p_ring_buffer_.reset();

				for (sz i = 0; i < max_chunk_count_; ++i) {

					F_chunk_header* chunk_p = 0;

                    if constexpr (F_options::chunks_in_a_single_block){
                        chunk_p = reinterpret_cast<F_chunk_header*>(reinterpret_cast<u8*>(first_chunk_p_) + chunk_size_ * i);
                        *chunk_p = F_chunk_header{};
                    }
                    else{
                        chunk_p = reinterpret_cast<F_chunk_header*>(allocator_for_chunks_.allocate(chunk_size()));
                        *chunk_p = F_chunk_header{};
                    }

					chunk_p_ring_buffer_.push(chunk_p);

				}

			}



		public:
			inline void push_chunk(F_chunk_header* chunk_p) {

                F_options::pre_push_chunk(this);
                F_options::pre_push_chunk_with_chunk_p(this, chunk_p);

                if constexpr (!F_options::chunks_in_a_single_block){
                    if(chunk_p_ring_buffer_.size() == max_chunk_count_){
                        chunk_p->~F_chunk_header();
                        allocator_for_chunks_.deallocate(chunk_p);
                    }
                }

				chunk_p_ring_buffer_.push(chunk_p);

                F_options::post_push_chunk(this);
                F_options::post_push_chunk_with_chunk_p(this, chunk_p);

			}
			inline F_chunk_header* pop_chunk() {

                F_options::pre_pop_chunk(this);

				F_chunk_header* chunk_p = 0;

				b8 success = chunk_p_ring_buffer_.try_pop(chunk_p);

                if constexpr (F_options::chunks_in_a_single_block){
                    NCPP_ASSERT(success) << "unexpected behaviour, ring buffer is empty";
                }
                else{
                    if(!success){
                        chunk_p = new F_chunk_header();
                    }
                }

                F_options::post_pop_chunk(this);
                F_options::post_pop_chunk_with_chunk_p(this, chunk_p);

				return chunk_p;
			}
			inline F_chunk_header* chunk_from_data_p(void* p) const noexcept {

                NCPP_ASSERT(F_options::chunks_in_a_single_block) << "can only get data pointer if chunks in a single block is enabled";

				sz index = (reinterpret_cast<sz>(p) - reinterpret_cast<sz>(first_chunk_p_)) / chunk_size_;

				return reinterpret_cast<F_chunk_header*>(reinterpret_cast<u8*>(first_chunk_p_) + chunk_size_ * index);
			}
            inline b8 is_local_data_p(void* p) const noexcept {

                NCPP_ASSERT(F_options::chunks_in_a_single_block) << "can only check local data pointer if chunks in a single block is enabled";

                return (reinterpret_cast<sz>(p) - reinterpret_cast<sz>(first_chunk_p_)) < max_total_size_;
            }

		};



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		template<class F_options__>
		class TF_chunk_adaptor {

		public:
			using F_options = F_options__;
			using F_storage = TF_chunk_storage<F_options>;
			using F_adaptor = TF_chunk_adaptor<F_options>;
			using F_allocator = TF_chunk_allocator<F_options>;
			using F_global_chunk_p_ring_buffer = typename F_options::F_global_chunk_p_ring_buffer;
			using F_local_chunk_p_ring_buffer = typename F_options::F_local_chunk_p_ring_buffer;



		private:
			F_storage* storage_p_ = 0;

			F_local_chunk_p_ring_buffer chunk_p_ring_buffer_;

			sz max_chunk_count_ = 0;
			sz chunk_capacity_ = 0;

		public:
			NCPP_FORCE_INLINE F_storage* storage_p() noexcept { return storage_p_; }
			NCPP_FORCE_INLINE const F_storage* storage_p() const noexcept { return storage_p_; }

			NCPP_FORCE_INLINE sz max_chunk_count() const { return max_chunk_count_; }
			NCPP_FORCE_INLINE sz chunk_capacity() const { return chunk_capacity_; }



		public:
			inline TF_chunk_adaptor(F_storage* storage_p, sz max_chunk_count = NCPP_CHUNK_ADAPTOR_DEFAULT_MAX_CHUNK_COUNT) :
				storage_p_(storage_p),

				chunk_p_ring_buffer_(max_chunk_count),

				max_chunk_count_(max_chunk_count),
				chunk_capacity_(storage_p->chunk_capacity())
			{

				NCPP_ASSERT(storage_p_) << "storage is null, cant create adaptor";

				setup_default_chunk_pointers_internal();

			}
			~TF_chunk_adaptor() {

				reset();

			}



		private:
			void setup_default_chunk_pointers_internal() {

				for (sz i = 0; i < max_chunk_count_; ++i) {

					chunk_p_ring_buffer_.push(storage_p_->pop_chunk());

				}

			}



		public:
			void reset() {



			}

			inline void push_chunk(F_chunk_header* chunk_p) {
                
                NCPP_ASSERT(chunk_p) << "cant push nulll chunk";

				*chunk_p = F_chunk_header {};

				if (chunk_p_ring_buffer_.size() < max_chunk_count_)
					chunk_p_ring_buffer_.push(chunk_p);
				else
					storage_p_->push_chunk(chunk_p);

			}
			inline F_chunk_header* pop_chunk() {

				F_chunk_header* chunk_p = 0;

				if (!(chunk_p_ring_buffer_.try_pop(chunk_p))) {

					return storage_p_->pop_chunk();
				}

				return chunk_p;
			}

		};



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		template<class F_options__>
		class TF_chunk_allocator : public TA_allocator<TF_chunk_allocator<F_options__>, true> {

		private:
			using F_base = TA_allocator<TF_chunk_allocator<F_options__>, true>;



		public:
			using F_options = F_options__;
			using F_storage = TF_chunk_storage<F_options>;
			using F_adaptor = TF_chunk_adaptor<F_options>;
			using F_allocator = TF_chunk_allocator<F_options>;
			using F_global_chunk_p_ring_buffer = typename F_options::F_global_chunk_p_ring_buffer;
			using F_local_chunk_p_ring_buffer = typename F_options::F_local_chunk_p_ring_buffer;



		private:
			F_adaptor* adaptor_p_ = 0;
			F_storage* storage_p_ = 0;

			F_chunk_header* head_chunk_p_ = 0;
			F_chunk_header* tail_chunk_p_ = 0;
			u16 chunk_count_ = 0;

			F_chunk_header* current_chunk_p_ = 0;
			sz current_usage_ = 0;

			sz chunk_capacity_;
			u16 min_chunk_count_;



		public:
			NCPP_FORCE_INLINE F_adaptor* adaptor_p() noexcept { return adaptor_p_; }
			NCPP_FORCE_INLINE const F_adaptor* adaptor_p() const noexcept { return adaptor_p_; }
			NCPP_FORCE_INLINE F_storage* storage_p() noexcept { return storage_p_; }
			NCPP_FORCE_INLINE const F_storage* storage_p() const noexcept { return storage_p_; }

			NCPP_FORCE_INLINE sz chunk_capacity() const { return chunk_capacity_; }
			NCPP_FORCE_INLINE u16 min_chunk_count() const { return min_chunk_count_; }
			NCPP_FORCE_INLINE u16 chunk_count() const { return chunk_count_; }



		public:
			// Default chunk capacity is 2MiB
			inline TF_chunk_allocator(F_adaptor* adaptor_p = 0, u16 min_chunk_count = 0, const char* name = 0) :
				F_base(name),
				adaptor_p_(adaptor_p),

				chunk_capacity_(0),
				min_chunk_count_(min_chunk_count),
				current_usage_(0)
			{

				if (adaptor_p_) {

					storage_p_ = adaptor_p_->storage_p();

					chunk_capacity_ = adaptor_p_->chunk_capacity();
					current_usage_ = chunk_capacity_;

					validate_chunk_count();

				}

			}
			inline TF_chunk_allocator(const TF_chunk_allocator& x) :
				TF_chunk_allocator(x.adaptor_p_, x.min_chunk_count_, x.name())
			{



			}

			~TF_chunk_allocator() {

				reset();
			}



		public:
			F_chunk_header* get_new_chunk_from_adaptor() {

				NCPP_ASSERT(adaptor_p_) << "adaptor is null, cant push new chunk";

				F_chunk_header* new_chunk_p = adaptor_p_->pop_chunk();

				*new_chunk_p = {
				
					0,
					0,
					tail_chunk_p_

				};

				if (tail_chunk_p_)
					tail_chunk_p_->next_p = new_chunk_p;
				else
					head_chunk_p_ = new_chunk_p;

				tail_chunk_p_ = new_chunk_p;

				++chunk_count_;

				return new_chunk_p;
			}
			F_chunk_header* optain_next_chunk(F_chunk_header* chunk_p) {

				if (chunk_p && chunk_p->next_p) {

					chunk_p->next_p->usage = 0;

					return chunk_p->next_p;
				}

				return get_new_chunk_from_adaptor();
			}
			void erase_chunk(F_chunk_header* chunk_p) {

				NCPP_ASSERT(adaptor_p_) << "adaptor is null, cant erase chunk";

				F_chunk_header* prev_chunk_p = chunk_p->prev_p;
				F_chunk_header* next_chunk_p = chunk_p->next_p;

				if (prev_chunk_p) {

					prev_chunk_p->next_p = next_chunk_p;
				}
				else
					head_chunk_p_ = next_chunk_p;
				if (next_chunk_p) {

					next_chunk_p->prev_p = prev_chunk_p;
				}
				else
					tail_chunk_p_ = prev_chunk_p;
                
#ifdef NCPP_ENABLE_MEMORY_COUNTING
                NCPP_DECREASE_USABLE_ALLOCATED_MEMORY(chunk_p->usage);
#endif

				adaptor_p_->push_chunk(chunk_p);

				--chunk_count_;

			}

		public:
			NCPP_FORCE_INLINE void* new_mem(sz size, sz alignment, sz alignment_offset) {

				sz actual_size = alignment + alignment_offset + size;

				NCPP_ASSERT(actual_size <= chunk_capacity_) << "allocation size too big";
				NCPP_ASSERT(adaptor_p_) << "adaptor is null, cant allocate memory";

				current_usage_ += actual_size;



#ifdef NCPP_ENABLE_MEMORY_COUNTING
				NCPP_INCREASE_USABLE_ALLOCATED_MEMORY(actual_size);
#endif



				if (current_usage_ > chunk_capacity_)
				{

					current_chunk_p_ = optain_next_chunk(current_chunk_p_);

					current_usage_ = actual_size;

				}



				u8* memory_p = current_chunk_p_->current_data();



				current_chunk_p_->usage = current_usage_;

                if constexpr (F_options::enable_allocation_counting_inside_chunks)
				    ++current_chunk_p_->allocation_count;



				return reinterpret_cast<u8*>(align_address(reinterpret_cast<uintptr_t>(memory_p + alignment_offset), alignment)) - alignment_offset;

			}
			NCPP_FORCE_INLINE void delete_mem(void* p) {

				NCPP_ASSERT(adaptor_p_) << "adaptor is null, cant deallocate memory";



                if constexpr (F_options::enable_allocation_counting_inside_chunks) {

                    F_chunk_header* chunk_p = storage_p_->chunk_from_data_p(p);
                    --(chunk_p->allocation_count);
                }



                // Deprecated, need to call chunk erasing manually
//                if ((chunk_p->allocation_count == 0) && (chunk_p != current_chunk_p_)) {
//
//                    erase_chunk(chunk_p);
//
//                }

			}

			/**
			 *	Deallocates all chunks.
			 */
			inline void reset() {

				if (!adaptor_p_)
					return;

				while (chunk_count_) {

					erase_chunk(tail_chunk_p_);

				}

				current_usage_ = chunk_capacity_;

			}
			/**
			 *	Resets memory usage, sets the first chunk as current chunk and also deallocates chunks until there is only min_chunk_count_ chunks.
			 */
			inline void clear() {

				if (!adaptor_p_)
					return;

				if (chunk_count_ == 0)
					return;

				while (chunk_count_ > min_chunk_count_) {

					erase_chunk(tail_chunk_p_);

				}

				current_chunk_p_ = tail_chunk_p_;

				while (current_chunk_p_ != head_chunk_p_) {

					current_chunk_p_->usage = 0;

					current_chunk_p_ = current_chunk_p_->prev_p;

				}

				if (!current_chunk_p_)
					current_usage_ = chunk_capacity_;

			}

			inline void validate_chunk_count() {

				if (!adaptor_p_)
					return;

				while (chunk_count_ < min_chunk_count_) {

					current_chunk_p_ = optain_next_chunk(current_chunk_p_);

				}

				clear();

			}

            template<typename F_functor__>
            inline void T_iterate_chunks(F_functor__&& functor) {

                F_chunk_header* chunk_p = head_chunk_p_;

                while (chunk_p) {

                    F_chunk_header* next_chunk_p = chunk_p->next_p;
                    functor(chunk_p);
                    chunk_p = next_chunk_p;
                }

            }
            template<typename F_functor__>
            inline void T_reverse_iterate_chunks(F_functor__&& functor) {

                F_chunk_header* chunk_p = tail_chunk_p_;

                while (chunk_p) {

                    F_chunk_header* prev_chunk_p = chunk_p->prev_p;
                    functor(chunk_p);
                    chunk_p = prev_chunk_p;
                }

            }

		};



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		using F_chunk_storage = TF_chunk_storage<>;
		using F_chunk_adaptor = TF_chunk_adaptor<>;
		using F_chunk_allocator = TF_chunk_allocator<>;

	}

}

