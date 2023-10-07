#pragma once

/** @file ncpp/chunk_allocator.hpp
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

		/**
		 * An allocator is similar to F_incremental_chunk_allocator but is capable of releasing empty chunks.
		 * It maintains a count of used memory and returns a pointer to the chunk plus the
		 * memory count each time memory is allocated.
		 *
		 * When deallocating memory, this allocator follows a smart approach:
		 * - If the chunk of the allocation is not the latest chunk and
		 * - The memory usage in that chunk after deallocation of this allocation is zero,
		 * Then it deallocates that chunk.
		 */
		class F_smart_chunk_allocator : public TI_allocator<F_smart_chunk_allocator> {



		private:
			struct F_chunk_header {

				sz usage = 0;
				F_chunk_header* pev_p = 0;
				F_chunk_header* next_p = 0;

				inline u8* data_root() {

					return reinterpret_cast<u8*>(this + 1);
				}

				inline u8* current_data() {

					return data_root() + usage;
				}

			};
			struct F_allocation_header {

				sz actual_size = 0;
				F_chunk_header* chunk_p = 0;

				inline u8* data_root() {

					return reinterpret_cast<u8*>(this + 1);
				}

			};



		private:
			F_chunk_header* head_chunk_p_ = 0;
			F_chunk_header* tail_chunk_p_ = 0;
			u16 chunk_count_ = 0;

			F_chunk_header* current_chunk_p_ = 0;
			sz current_usage_ = 0;

			sz chunk_capacity_;
			u16 min_chunk_count_;

#ifdef NCPP_ENABLE_MEMORY_COUNTING
			sz usable_allocated_memory_ = 0;
#endif



		public:
			inline sz chunk_capacity() const { return chunk_capacity_; }
			inline u16 min_chunk_count() const { return min_chunk_count_; }
			inline u16 chunk_count() const { return chunk_count_; }



		public:
			// Default chunk capacity is 2MiB
			inline F_smart_chunk_allocator(sz chunk_capacity = 2097152, u16 min_chunk_count = 0, const char* name = 0) :
				TI_allocator(name),
				chunk_capacity_(chunk_capacity),
				min_chunk_count_(min_chunk_count),
				current_usage_(chunk_capacity)
			{

				validate_chunk_count();

			}
			inline F_smart_chunk_allocator(const F_smart_chunk_allocator& x) :
				F_smart_chunk_allocator(x.chunk_capacity_, x.min_chunk_count_, x.name_)
			{



			}

			~F_smart_chunk_allocator() {

				reset();
			}



		private:
			inline F_chunk_header* push_new_chunk() {

				F_chunk_header* new_chunk_p = reinterpret_cast<F_chunk_header*>(default_allocate(sizeof(F_chunk_header) + chunk_capacity_));

				*new_chunk_p = {
				
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
			inline F_chunk_header* optain_next_chunk(F_chunk_header* chunk_p) {

				if (chunk_p && chunk_p->next_p) {

					chunk_p->next_p->usage = 0;

					return chunk_p->next_p;
				}

				return push_new_chunk();
			}
			inline void erase_chunk(F_chunk_header* chunk_p) {

				F_chunk_header* prev_chunk_p = chunk_p->pev_p;
				F_chunk_header* next_chunk_p = chunk_p->next_p;

				if (prev_chunk_p) {

					prev_chunk_p->next_p = next_chunk_p;
				}
				else
					head_chunk_p_ = next_chunk_p;
				if (next_chunk_p) {

					next_chunk_p->pev_p = prev_chunk_p;
				}
				else
					tail_chunk_p_ = prev_chunk_p;

				default_deallocate(chunk_p);

				--chunk_count_;

			}

		public:
			inline void* new_mem(sz size) {

				sz actual_size = sizeof(F_allocation_header) + size;

				current_usage_ += actual_size;



#ifdef NCPP_ENABLE_MEMORY_COUNTING
				NCPP_INCREASE_USABLE_ALLOCATED_MEMORY(size);
				usable_allocated_memory_ += size;
#endif



				if (current_usage_ > chunk_capacity_)
				{

					current_chunk_p_ = optain_next_chunk(current_chunk_p_);

					current_usage_ = actual_size;

				}



				F_allocation_header* allocation_header_p = reinterpret_cast<F_allocation_header*>(current_chunk_p_->current_data());
				*allocation_header_p = {

					actual_size,
					current_chunk_p_

				};



				current_chunk_p_->usage = current_usage_;



				return allocation_header_p->data_root();

			}
			inline void delete_mem(void* p) {

				F_allocation_header* allocation_header_p = reinterpret_cast<F_allocation_header*>(p) - 1;

				F_chunk_header* chunk_p = allocation_header_p->chunk_p;



#ifdef NCPP_ENABLE_MEMORY_COUNTING
				NCPP_DECREASE_USABLE_ALLOCATED_MEMORY(allocation_header_p->actual_size - sizeof(F_allocation_header));
				usable_allocated_memory_ -= allocation_header_p->actual_size - sizeof(F_allocation_header);
#endif



				if ((allocation_header_p->actual_size == chunk_p->usage) && (chunk_p != current_chunk_p_)) {

					erase_chunk(chunk_p);

				}
				else
					chunk_p->usage -= allocation_header_p->actual_size;

			}

			/**
			 *	Deallocates all chunks.
			 */
			void reset() {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
				NCPP_DECREASE_USABLE_ALLOCATED_MEMORY(usable_allocated_memory_);
				usable_allocated_memory_ = 0;
#endif

				while (chunk_count_) {

					erase_chunk(tail_chunk_p_);

				}

				current_usage_ = chunk_capacity_;

			}
			/**
			 *	Resets memory usage, sets the first chunk as current chunk and also deallocates chunks until there is only min_chunk_count_ chunks.
			 */
			void clear() {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
				NCPP_DECREASE_USABLE_ALLOCATED_MEMORY(usable_allocated_memory_);
				usable_allocated_memory_ = 0;
#endif

				if (chunk_count_ == 0)
					return;

				while (chunk_count_ > min_chunk_count_) {

					erase_chunk(tail_chunk_p_);

				}

				current_chunk_p_ = tail_chunk_p_;

				while (current_chunk_p_ != head_chunk_p_) {

					current_chunk_p_->usage = 0;

					current_chunk_p_ = current_chunk_p_->pev_p;

				}

				if (!current_chunk_p_)
					current_usage_ = chunk_capacity_;

			}

			void validate_chunk_count() {

				while (chunk_count_ < min_chunk_count_) {

					current_chunk_p_ = optain_next_chunk(current_chunk_p_);

				}

				clear();

			}

		};

	}

}

