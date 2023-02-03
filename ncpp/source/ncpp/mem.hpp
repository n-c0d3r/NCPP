#pragma once

/** @file ncpp/mem.hpp
*	@brief Contains the memory management utilities.
*/



#include <ncpp/prerequisites.hpp>

#ifdef NCPP_ENABLE_MEMORY_COUNTING
#include <ncpp/memory_counting.hpp>
#endif



namespace ncpp {

	/**
	 *	Uses to indicate that something need to use ncpp overloaded version,...
	 */
	struct placeholder {



	};

	struct new_mode {

		struct default {};
		struct align {};

	};



	/**
	 *	Signs that a memory pointer is allocated by a ncpp allocator.
	 */
#define NCPP_MEMORY_ALLOCATION_SIGNATURE 0xF0362F98



	/**
	 *	Describes informations about allocated memory 
	 */
	struct NCPP_DEFAULT_SET_ALIGN allocation_desc {

		sz actual_size;
		sz signature : 32;
		sz align : 1;
		sz alignment_shift : 1;

	};

	/**
	 *	Checks whether the memory locating at the given pointer is allocated by a ncpp allocator.
	 */
	inline b8 is_allocated_by_ncpp(void* ptr) { 
		return (reinterpret_cast<allocation_desc*>(ptr) - 1)->signature == NCPP_MEMORY_ALLOCATION_SIGNATURE;
	}



#pragma region Implement aligned allocation,...
	/**
	 *	Returns aligned address shifting from the given address and align.
	 */
	inline uintptr_t align_address(uintptr_t addr, sz align)
	{
		const sz mask = align - 1;
		assert((align & mask) == 0 && "align value must be power of 2");
		return (addr + mask) & ~mask;
	}
	/**
	 *	Returns aligned pointer shifting from the given pointer and align.
	 */
	template<typename data_type>
	inline data_type* align_pointer(data_type* ptr, sz align)
	{
		const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
		return reinterpret_cast<data_type*>(align_address(addr, align));
	}
	/**
	 *	Aligned allocates a memory block from given size and align.
	 */
	inline void* aligned_alloc(sz size, sz align)
	{

		sz desc_shift = max(align, sizeof(allocation_desc));
		sz actual_size = size + desc_shift + align;

		u8* raw_ptr = reinterpret_cast<u8*>(malloc(actual_size));

		u8* aligned_ptr = align_pointer(raw_ptr, align);

		allocation_desc* alloc_desc_p = reinterpret_cast<allocation_desc*>(aligned_ptr);

		alloc_desc_p->actual_size = actual_size;
		alloc_desc_p->signature = NCPP_MEMORY_ALLOCATION_SIGNATURE;
		alloc_desc_p->align = align;
		alloc_desc_p->alignment_shift = aligned_ptr - raw_ptr;

		increase_memory_usage(actual_size);

		return alloc_desc_p + 1;
	}
	/**
	 *	Aligned frees a memory block.
	 */
	inline void aligned_free(void* ptr)
	{

		allocation_desc* alloc_desc_p = (allocation_desc*)ptr - 1;

		u8* raw_ptr = reinterpret_cast<u8*>(alloc_desc_p) - alloc_desc_p->alignment_shift;

		decrease_memory_usage(alloc_desc_p->actual_size);

		free(raw_ptr);

		return;
	}
#pragma endregion

}



#pragma region new and delete operators
extern void* operator new(ncpp::sz size);
extern void* operator new(ncpp::sz size, ncpp::new_mode::align, ncpp::sz align);
extern void operator delete(void* ptr);
#pragma endregion

