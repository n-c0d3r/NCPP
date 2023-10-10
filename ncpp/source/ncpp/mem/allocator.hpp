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

#if defined(NCPP_ENABLE_ALLOCATOR_NAME) || defined(NCPP_ENABLE_MEMORY_COUNTING)
#define NCPP_HAS_ALLOC_DEBUG_INFO
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
		struct NCPP_ALIGN(EASTL_ALLOCATOR_MIN_ALIGNMENT) F_alloc_debug_info {

			const char* allocator_name = 0;
			sz actual_size = 0;
			sz payload_size = 0;
			bool is_default_alloc = 0;

		};
#endif



#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
		static inline F_alloc_debug_info get_alloc_debug_info(void* p) {

			return reinterpret_cast<F_alloc_debug_info*>(p)[-1];
		}
#endif



		/**
		 *	Base allocator class.
		 */
		template<class F_allocator__, b8 enable_manual_alignment__ = false>
		class TI_allocator {

		private:
			using F_this = TI_allocator<F_allocator__, enable_manual_alignment__>;



		public:
			static constexpr b8 enable_manual_alignment = enable_manual_alignment__;



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

#if NCPP_ENABLE_ALLOCATOR_NAME
				name_ = name;
#endif

			}
			inline TI_allocator(const TI_allocator& x)
			{

#if NCPP_ENABLE_ALLOCATOR_NAME
				name_ = x.name_;
#endif

			}
			inline TI_allocator(const TI_allocator& x, const char* name)
			{

#if NCPP_ENABLE_ALLOCATOR_NAME
				name_ = name;
#endif

			}

			TI_allocator& operator=(const TI_allocator& x) {

#if NCPP_ENABLE_ALLOCATOR_NAME
				name_ = x.name_;
#endif

				return *this;
			}



		private:
			template<class F_overloaded_allocator__, b8 is_default_alloc__>
			inline void* T_aligned_allocate_internal(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				if constexpr (enable_manual_alignment && !is_default_alloc__) {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					sz actual_size = sizeof(void*) + sizeof(F_alloc_debug_info) + n;
					sz actual_alignment_offset = sizeof(void*) + sizeof(F_alloc_debug_info) + alignment_offset;
#else
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					F_alloc_debug_info debug_info = {

						name_,
						actual_size,
						n,
						is_default_alloc__

					};
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(actual_size, alignment, actual_alignment_offset));

					u8* result_p = raw_p + sizeof(void*) + sizeof(F_alloc_debug_info);
                    
					reinterpret_cast<F_alloc_debug_info*>(result_p)[-1] = debug_info;
					*reinterpret_cast<void**>(reinterpret_cast<u8*>(result_p) - sizeof(F_alloc_debug_info) - sizeof(void*)) = raw_p;

					return result_p;
#else
					return reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(n, alignment, alignment_offset);
#endif

				}
				else {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					sz actual_size = alignment + sizeof(void*) + sizeof(F_alloc_debug_info) + n;
#else
					sz actual_size = alignment + sizeof(void*) + n;
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					F_alloc_debug_info debug_info = {

						name_,
						actual_size,
						n,
						is_default_alloc__

					};

#ifdef NCPP_ENABLE_MEMORY_COUNTING
					if constexpr (is_default_alloc__) {

						NCPP_INCREASE_TOTAL_ALLOCATED_MEMORY(actual_size);

					}
#endif
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					sz actual_alignment_offset = sizeof(void*) + sizeof(F_alloc_debug_info) + alignment_offset;
#else
					sz actual_alignment_offset = sizeof(void*) + alignment_offset;
#endif

					u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(actual_size, alignment, alignment_offset));

					u8* result_p = reinterpret_cast<u8*>(align_address(reinterpret_cast<uintptr_t>(raw_p + actual_alignment_offset), alignment)) - alignment_offset;

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					reinterpret_cast<F_alloc_debug_info*>(result_p)[-1] = debug_info;
					*reinterpret_cast<void**>(reinterpret_cast<u8*>(result_p) - sizeof(F_alloc_debug_info) - sizeof(void*)) = raw_p;
#else
					reinterpret_cast<void**>(result_p)[-1] = raw_p;
#endif

					return result_p;
				}

			}
			template<class F_overloaded_allocator__, b8 is_default_alloc__>
			inline void* T_allocate_internal(sz n, int flags = 0) {

				if constexpr (enable_manual_alignment && !is_default_alloc__) {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					sz actual_size = sizeof(void*) + sizeof(F_alloc_debug_info) + n;
					sz actual_alignment_offset = sizeof(void*) + sizeof(F_alloc_debug_info);
#else
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					F_alloc_debug_info debug_info = {

						name_,
						actual_size,
						n,
						is_default_alloc__

					};
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(actual_size, EASTL_ALLOCATOR_MIN_ALIGNMENT, actual_alignment_offset));
                    
                    u8* result_p = raw_p + actual_alignment_offset;

					reinterpret_cast<F_alloc_debug_info*>(result_p)[-1] = debug_info;
					*reinterpret_cast<void**>(reinterpret_cast<u8*>(result_p) - sizeof(F_alloc_debug_info) - sizeof(void*)) = raw_p;

					return result_p;
#else
					return reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(n, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0);
#endif

				}
				else {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					sz actual_size = EASTL_ALLOCATOR_MIN_ALIGNMENT + sizeof(F_alloc_debug_info) + n;
#else
					sz actual_size = EASTL_ALLOCATOR_MIN_ALIGNMENT + n;
#endif

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					F_alloc_debug_info debug_info = {

						name_,
						actual_size,
						n,
						is_default_alloc__

					};

#ifdef NCPP_ENABLE_MEMORY_COUNTING
					if constexpr (is_default_alloc__) {

						NCPP_INCREASE_TOTAL_ALLOCATED_MEMORY(actual_size);

					}
#endif
#endif

					u8* raw_p = reinterpret_cast<u8*>(reinterpret_cast<F_overloaded_allocator__*>(this)->new_mem(actual_size, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0));

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					u8* result_p = raw_p + EASTL_ALLOCATOR_MIN_ALIGNMENT + sizeof(F_alloc_debug_info);

					reinterpret_cast<F_alloc_debug_info*>(result_p)[-1] = debug_info;

					*reinterpret_cast<void**>(reinterpret_cast<u8*>(result_p) - sizeof(F_alloc_debug_info) - sizeof(void*)) = raw_p;
#else
					u8* result_p = raw_p + EASTL_ALLOCATOR_MIN_ALIGNMENT;

					reinterpret_cast<void**>(result_p)[-1] = raw_p;
#endif

					return result_p;

				}

			}
			template<class F_overloaded_allocator__, b8 is_default_alloc__>
			inline void T_deallocate_internal(void* p, sz n = 1) {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
				F_alloc_debug_info debug_info = get_alloc_debug_info(p);

#ifdef NCPP_ENABLE_MEMORY_COUNTING
				if (debug_info.is_default_alloc) {

					NCPP_INCREASE_TOTAL_ALLOCATED_MEMORY(debug_info.actual_size);

				}
#endif
#endif

				if constexpr (enable_manual_alignment && !is_default_alloc__) {

					reinterpret_cast<F_overloaded_allocator__*>(this)->delete_mem(p);

				}
				else {

#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
					reinterpret_cast<F_overloaded_allocator__*>(this)->delete_mem(*reinterpret_cast<void**>(reinterpret_cast<u8*>(p) - sizeof(F_alloc_debug_info) - sizeof(void*)));
#else
					reinterpret_cast<F_overloaded_allocator__*>(this)->delete_mem(reinterpret_cast<void**>(p)[-1]);
#endif

				}

			}



		public:
			/**
			 *	Allocates non-aligned memory with default new_mem(sz) function
			 */
			inline void* default_allocate(sz n, int flags = 0) {

				return T_allocate_internal<TI_allocator, true>(n, flags);
			}
			/**
			 *	Allocates aligned memory with default new_mem(sz) function
			 */
			void* default_allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

				if(alignment <= EASTL_ALLOCATOR_MIN_ALIGNMENT){

					return T_allocate_internal<TI_allocator, true>(n, flags);
				}
				else{

					return T_aligned_allocate_internal<TI_allocator, true>(n, alignment, alignment_offset, flags);
				}

				return 0;
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
			void* allocate(sz n, int flags = 0) {

#ifndef NCPP_HAS_ALLOC_DEBUG_INFO
				if constexpr (enable_manual_alignment) {

					return reinterpret_cast<F_allocator__*>(this)->new_mem(n, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0);

				}
				else 
#endif
				{

					return T_allocate_internal<F_allocator__, false>(n, flags);
				}
			}
			/**
			 *	Allocates aligned memory with default new_mem(sz) function
			 */
			void* allocate(sz n, sz alignment, sz alignment_offset, int flags = 0) {

#ifndef NCPP_HAS_ALLOC_DEBUG_INFO
				if constexpr (enable_manual_alignment) {

					return reinterpret_cast<F_allocator__*>(this)->new_mem(n, alignment, alignment_offset);

				}
				else
#endif
				{

					if (alignment <= EASTL_ALLOCATOR_MIN_ALIGNMENT) {

						return T_allocate_internal<F_allocator__, false>(n, flags);
					}
					else {

						return T_aligned_allocate_internal<F_allocator__, false>(n, alignment, alignment_offset, flags);
					}

				}
				
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
			 *	Clear some essential datas.
			 */
			inline void clear() {}

			/**
			 *
			 */
			inline void* new_mem(sz size, sz alignment = EASTL_ALLOCATOR_MIN_ALIGNMENT, sz alignment_offset = 0) {

				return malloc(size);
			}
			/**
			 *
			 */
			inline void delete_mem(void* p) { 
				
				free(p); 
			}

		};

	}

}

