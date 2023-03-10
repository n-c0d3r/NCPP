#pragma once

/** @file ncpp/mem.hpp
*	@brief Contains the memory management utilities.
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

#ifdef NCPP_ENABLE_MEMORY_COUNTING
#include <ncpp/memory_counting.hpp>
#endif

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



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Implements aligned allocation,...
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

		sz actual_size = size + sizeof(sz) + align;

		u8* raw_ptr = new u8[actual_size];
		*((sz*)raw_ptr) = actual_size;
		raw_ptr += sizeof(sz);

		u8* aligned_ptr = align_pointer(raw_ptr, align);

		if (aligned_ptr == raw_ptr)
			aligned_ptr += align;

		ptrdiff_t shift = aligned_ptr - raw_ptr;
		assert(shift > 0 && shift <= 256);

#ifdef NCPP_ENABLE_MEMORY_COUNTING
		increase_memory_usage(actual_size);
#endif

		aligned_ptr[-1] = static_cast<u8>(shift & 0xFF);
		return aligned_ptr;
	}

	/**
	 *	Gets actual allocated size from aligned pointer
	 */
	inline sz actual_size_aligned(void* ptr)
	{

		u8* aligned_ptr = reinterpret_cast<u8*>(ptr);

		ptrdiff_t shift = aligned_ptr[-1];
		if (shift == 0)
			shift = 256;

		u8* raw_ptr = aligned_ptr - shift - sizeof(sz);

		sz actual_size = *((sz*)raw_ptr);

		return actual_size;
	}

	/**
	 *	Aligned frees a memory block.
	 */
	inline void aligned_free(void* ptr)
	{

		u8* aligned_ptr = reinterpret_cast<u8*>(ptr);

		ptrdiff_t shift = aligned_ptr[-1];
		if (shift == 0)
			shift = 256;

		u8* raw_ptr = aligned_ptr - shift - sizeof(sz);

		sz actual_size = *((sz*)raw_ptr);

#ifdef NCPP_ENABLE_MEMORY_COUNTING
		decrease_memory_usage(actual_size);
#endif

		delete[] raw_ptr;

		return;
	}
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



#pragma region Allocators
	template <class value_type__>
	class NCPP_DEFAULT_ALIGNAS aligned_allocator_t
	{

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:
		using size_type = sz;
		using difference_type = ptrdiff_t;
		using pointer = value_type__*;
		using const_pointer = const value_type__*;
		using reference = value_type__&;
		using const_reference = const value_type__&;
		using value_type = value_type__;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:
		inline aligned_allocator_t()
		{



		}

		inline aligned_allocator_t<value_type>& operator=(const aligned_allocator_t& other) {



			return *this;
		}

		template <class other_value_type__>
		inline aligned_allocator_t(const aligned_allocator_t<other_value_type__>& other) {



		}

		template <class other_value_type__>
		inline aligned_allocator_t& operator=(const aligned_allocator_t<other_value_type__>& other) {



			return *this;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		inline pointer   allocate(size_type n, sz align = NCPP_DEFAULT_ALIGN) {

			return (pointer)aligned_alloc(n * sizeof(value_type), align);
		}

		inline void      deallocate(void* p, sz n = sizeof(value_type)) {

			aligned_free(p);
		}

		inline pointer           address(reference x) const { return &x; }
		inline const_pointer     address(const_reference x) const { return &x; }
		inline void              construct(pointer p, const value_type& val)
		{
			new ((value_type*)p) value_type(val);
		}
		inline void              destroy(pointer p) { p->~value_type(); }

		inline size_type         max_size() const { return size_t(-1); }

		template <class U>
		struct rebind { typedef aligned_allocator_t<U> other; };
	};
#pragma endregion

}

