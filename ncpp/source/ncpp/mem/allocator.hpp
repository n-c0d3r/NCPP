#pragma once

/** @file ncpp/allocator_base.hpp
*	@brief Implements allocator base class template.
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

#include <ncpp/mem/memory_helper.hpp>

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

#if !defined(NDEBUG) || defined(NCPP_ENABLE_MEMORY_COUNTING)
#define HAS_DATA_OFFSET
#endif

		/**
		 *	Base allocator class implementing base functionalities for simply allocating both non-aligned and aligned memory.
		 *	TI_allocator is capable of choosing the actual memory allocation size to pass into F_allocator__::new_mem(sz size) function, and the memory pointer to pass into F_allocator__::delete_mem(void* pointer) function.
		 *	\n
		 *	By this way, F_allocator__ won't need to care about alignment, it's automatically did by TI_allocator.
		 *	\n
		 *	@param <F_allocator__> allocator type that implements TI_allocator and has to provide these functions:
		 *		+ new_mem(sz size): to allocate memory.
		 *		+ delete_mem(void* pointer): to deallocate memory.
		 */
		template<class F_allocator__>
		class TI_allocator {

		protected:
			// \cond INTERNAL
			const char* name_;
			// \endcond

		public:
			inline const char* name() const { return name_; }
			inline void set_name(const char* new_name) { name_ = new_name; }



		protected:
			inline TI_allocator(const char* name = 0)
			{

#if EASTL_NAME_ENABLED
				name_ = name;
#endif

			}
			inline TI_allocator(const TI_allocator& x)
			{

#if EASTL_NAME_ENABLED
				name_ = x.name_;
#endif

			}
			inline TI_allocator(const TI_allocator& x, const char* name)
			{

#if EASTL_NAME_ENABLED
				name_ = name;
#endif

			}

			TI_allocator& operator=(const TI_allocator& x) {

#if EASTL_NAME_ENABLED
				name_ = x.name_;
#endif

				return *this;
			}



		private:
			template<class F_overloaded_allocator__, b8 auto_count_memory__>
			inline void* T_allocate_internal(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				// Setup data offset
#ifdef HAS_DATA_OFFSET
				sz data_offset = 0;
#ifndef NDEBUG
				data_offset += sizeof(const char*);
				sz name_p_offset = data_offset;
#endif
#ifdef NCPP_ENABLE_MEMORY_COUNTING
				sz size_offset = 0;

				if constexpr (auto_count_memory__) {

					data_offset += sizeof(sz);

					size_offset = data_offset;

				}
#endif
#endif



				// Actual size
#ifdef HAS_DATA_OFFSET
				sz actual_size = alignment + data_offset + n;
#else
#endif



				// Allocate raw memory
#ifdef HAS_DATA_OFFSET
				u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(actual_size));
#else
				u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(alignment + n));
#endif



				// align pointer
#ifdef HAS_DATA_OFFSET
				sz actual_alignment_offset = alignment_offset + data_offset;

				u8* result_p = reinterpret_cast<u8*>(
					align_address(
						reinterpret_cast<uintptr_t>(raw_p + actual_alignment_offset),
						alignment
					)
				) - actual_alignment_offset;
#else
				// align pointer
				u8* result_p = reinterpret_cast<u8*>(
					align_address(
						reinterpret_cast<uintptr_t>(raw_p + alignment_offset),
						alignment
					)
				) - alignment_offset;
#endif



				result_p += alignment * (result_p == raw_p);



				// Goto data pointer
#ifdef HAS_DATA_OFFSET
				result_p += data_offset;
#endif



				// Save shift value
#ifdef HAS_DATA_OFFSET
				*(result_p - data_offset - 1) = (result_p - raw_p - data_offset - 1) & 0xFF;
#else
				*(result_p - 1) = (result_p - raw_p - 1) & 0xFF;
#endif



				// Save name and memory actual size
#ifndef NDEBUG
				*reinterpret_cast<const char**>(result_p - name_p_offset) = name_;
#endif
#ifdef NCPP_ENABLE_MEMORY_COUNTING
				if constexpr (auto_count_memory__) {

					*reinterpret_cast<sz*>(result_p - size_offset) = actual_size;

					NCPP_INCREASE_TOTAL_ALLOCATED_MEMORY(actual_size);

				}
#endif



				return result_p;
			}
			template<class F_overloaded_allocator__, b8 auto_count_memory__>
			inline void T_deallocate_internal(void* p, sz n = 1) {

				// Setup data offset
#ifdef HAS_DATA_OFFSET
				sz data_offset = 0;
#ifndef NDEBUG
				data_offset += sizeof(const char*);
				sz name_p_offset = data_offset;
#endif
#ifdef NCPP_ENABLE_MEMORY_COUNTING
				sz size_offset = 0;

				if constexpr (auto_count_memory__) {

					data_offset += sizeof(sz);

					size_offset = data_offset;

				}

				if constexpr (auto_count_memory__) {

					NCPP_DECREASE_TOTAL_ALLOCATED_MEMORY(*reinterpret_cast<sz*>(reinterpret_cast<u8*>(p) - size_offset));

				}
#endif
#endif



				// Read shift value
#ifdef HAS_DATA_OFFSET
				u8 shift = *(reinterpret_cast<u8*>(p) - data_offset - 1);
#else
				u8 shift = *(reinterpret_cast<u8*>(p) - 1);
#endif



				// Delete mem
#ifdef HAS_DATA_OFFSET
				reinterpret_cast<F_overloaded_allocator__*>(this)->delete_mem(reinterpret_cast<u8*>(p) - data_offset - shift - 1);
#else
				reinterpret_cast<F_overloaded_allocator__*>(this)->delete_mem(reinterpret_cast<u8*>(p) - shift - 1);
#endif


			}



		protected:
			/**
			 *	Allocates non-aligned memory with default new_mem(sz) function
			 */
			inline void* default_allocate(sz n, int flags = 0) {

				return default_allocate(n, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0, flags);
			}
			/**
			 *	Allocates aligned memory with default new_mem(sz) function
			 */
			void* default_allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				return T_allocate_internal<TI_allocator, true>(n, alignment, alignment_offset, flags);
			}
			/**
			 *	Deallocates memory with default delete_mem(void*) function
			 */
			void default_deallocate(void* p, sz n = 1) {

				T_deallocate_internal<TI_allocator, true>(p, n);
			}



		public:
			/**
			 *	Allocates non-aligned memory with default new_mem(sz) function
			 */
			inline void* allocate(sz n, int flags = 0) {
				
				return allocate(n, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0, flags);
			}
			/**
			 *	Allocates aligned memory with default new_mem(sz) function
			 */
			void* allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				return T_allocate_internal<F_allocator__, false>(n, alignment, alignment_offset, flags);
			}
			/**
			 *	Deallocates memory with default delete_mem(void*) function
			 */
			void  deallocate(void* p, sz n = 1) {

				T_deallocate_internal<F_allocator__, false>(p, n);
			}

			/**
			 *	Clears everything and to be the same as the default instance.
			 */
			inline void reset() {}
			/**
			 *	Not clears everything but clear some essential datas.
			 */
			inline void clear() {}

			/**
			 *
			 */
			inline void* new_mem(sz size) { return malloc(size); }
			/**
			 *
			 */
			inline void delete_mem(void* p) { free(p); }

		};



#ifdef HAS_DATA_OFFSET
#undef HAS_DATA_OFFSET
#endif

	}

}

