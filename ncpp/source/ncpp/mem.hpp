#pragma once

/** @file ncpp/mem.hpp
*	@brief Contains the memory management utilities.
*/



#include <ncpp/prerequisites.hpp>

#ifdef NCPP_ENABLE_MEMORY_COUNTING
#include <ncpp/memory_counting.hpp>
#endif



namespace ncpp {

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

		sz actual_size = size + align;

		u8* raw_ptr = new u8[actual_size];

		u8* aligned_ptr = align_pointer(raw_ptr, align);

		if (aligned_ptr == raw_ptr)
			aligned_ptr += align;

		ptrdiff_t shift = aligned_ptr - raw_ptr;
		assert(shift > 0 && shift <= 256);

		aligned_ptr[-1] = static_cast<u8>(shift & 0xFF);
		return aligned_ptr;
	}
	/**
	 *	Gets align from given aligned pointer.
	 */
	inline ptrdiff_t get_align(void* ptr)
	{

		u8* aligned_ptr = reinterpret_cast<u8*>(ptr);

		ptrdiff_t shift = aligned_ptr[-1];
		if (shift == 0)
			shift = 256;

		return shift;
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

		u8* raw_ptr = aligned_ptr - shift;

		delete[] raw_ptr;

		return;
	}
#pragma endregion



#pragma region Allocators
	template <class value_type__>
	class aligned_allocator_t
	{
	public:
		typedef sz size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type__* pointer;
		typedef const value_type__* const_pointer;
		typedef value_type__& reference;
		typedef const value_type__& const_reference;
		typedef value_type__ value_type;

		aligned_allocator_t() {}
		aligned_allocator_t(const aligned_allocator_t&) {}



		pointer   allocate(size_type n, sz align = NCPP_DEFAULT_ALIGN) {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
			increase_memory_usage(align + n * sizeof(value_type));
#endif

			std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl;

			return (pointer)aligned_alloc(n * sizeof(value_type), align);
		}

		void      deallocate(void* p, sz n = sizeof(value_type)) {

#ifdef NCPP_ENABLE_MEMORY_COUNTING
			decrease_memory_usage(get_align(p) + n * sizeof(value_type));
#endif

			aligned_free(p);
		}

		pointer           address(reference x) const { return &x; }
		const_pointer     address(const_reference x) const { return &x; }
		aligned_allocator_t<value_type>& operator=(const aligned_allocator_t&) { return *this; }
		void              construct(pointer p, const value_type& val)
		{
			new ((value_type*)p) value_type(val);
		}
		void              destroy(pointer p) { p->~value_type(); }

		size_type         max_size() const { return size_t(-1); }

		template <class U>
		struct rebind { typedef aligned_allocator_t<U> other; };

		template <class U>
		aligned_allocator_t(const aligned_allocator_t<U>&) {}

		template <class U>
		aligned_allocator_t& operator=(const aligned_allocator_t<U>&) { return *this; }
	};
#pragma endregion

}

