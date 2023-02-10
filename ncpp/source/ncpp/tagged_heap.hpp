#pragma once

/** @file ncpp/tagged_heap.hpp
 * 	@brief Implements tagged heap.
*/



#include <ncpp/prerequisites.hpp>

#include <ncpp/containers/.hpp>
#include <ncpp/mem.hpp>



namespace ncpp {

	/**
	 *	A tagged heap block represents a block of memory allocated by a tagged heap category.
	 * 	When the allocate(sz size, sz align) method called, it will increase the memory usage and then return the pointer data_p_ + usage_. 
	 * 	All memory allocation inside tagged heap block cannot be deallocated individually. The only way to deallocate it is deallocating all of the blocks in a tagged heap category. 
	 */
	struct NCPP_DEFAULT_ALIGNAS tagged_heap_block {



	private:
		sz capacity_;
		sz usage_;
		u8* data_p_;

	public:
		tagged_heap_block* prev_p = 0;
		tagged_heap_block* next_p = 0;



	public:
		inline sz capacity() const { return capacity_; }
		inline sz usage() const { return usage_; }
		inline u8* data_p() const { return data_p_; }



	public:
		inline tagged_heap_block(sz capacity) :
			capacity_(capacity),
			usage_(0),
			data_p_((u8*)(this + 1))
		{



		}
		~tagged_heap_block() {



		}



	private:
		/**
		 *	Returns aligned address shifting by the given address and align.
		 */
		inline uintptr_t align_address(uintptr_t addr, sz align)
		{
			const sz mask = align - 1;
			assert((align & mask) == 0 && "align value must be power of 2");
			return (addr + mask) & ~mask;
		}
		/**
		 *	Returns aligned pointer shifting by the given pointer and align.
		 */
		template<typename data_type>
		inline data_type* align_pointer(data_type* ptr, sz align)
		{
			const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
			return reinterpret_cast<data_type*>(align_address(addr, align));
		}
		/**
		 *	Aligned allocates a memory block by given size and align.
		 */
		inline u8* aligned_alloc(sz size, sz align)
		{

			sz actual_size = size + sizeof(sz) + align;

			u8* raw_ptr = data_p_ + usage_;
			usage_ += size + align + sizeof(sz);
			*((sz*)raw_ptr) = actual_size;
			raw_ptr += sizeof(sz);

			u8* aligned_ptr = align_pointer(raw_ptr, align);

			if (aligned_ptr == raw_ptr)
				aligned_ptr += align;

			ptrdiff_t shift = aligned_ptr - raw_ptr;
			assert(shift > 0 && shift <= 256);

			aligned_ptr[-1] = static_cast<u8>(shift & 0xFF);
			return reinterpret_cast<u8*>(aligned_ptr);
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



	public:
		/**
		 *	Checks if there is enough 'offset' free space.
		 */
		inline bool is_full(sz offset) {

			return usage_ + offset > capacity_;

		}

		/**
		 *	Allocates memory by given size and align.
		 */
		inline u8* allocate(sz size, sz align) {

			assert(size + sizeof(sz) + align + usage_ <= capacity_ && "block out of memory");

			u8* result = aligned_alloc(size, align);

			return result;
		}

		/**
		 *	Resets the usage to 0 and we can reuse the block.
		 */
		inline void reset() {

			usage_ = 0;
		}

	};



	/**
	 *	A tagged heap category is a category of allocations inside a tagged heap.
	 */
	template<
		class allocator_type__
	>
	class NCPP_DEFAULT_ALIGNAS tagged_heap_category_t {

	public:
		using allocator_type = allocator_type__;
		using block_type = tagged_heap_block;



	private:
		sz block_capacity_;
		
		u32 block_count_array_[64];
		block_type* head_block_p_array_[64];
		block_type* tail_block_p_array_[64];
		block_type* curr_block_p_array_[64];

		allocator_type allocator_;



	public:
		inline sz block_capacity() const { return block_capacity_; }

		inline allocator_type& block_allocator() { return allocator_; }
		inline const allocator_type& block_allocator() const { return allocator_; }



	public:
		inline tagged_heap_category_t() :
			block_capacity_(0)
		{



		}
		inline tagged_heap_category_t(sz block_capacity) :
			block_capacity_(block_capacity)
		{

			memset(block_count_array_, 0, sizeof(block_count_array_));
			memset(head_block_p_array_, 0, sizeof(head_block_p_array_));
			memset(tail_block_p_array_, 0, sizeof(tail_block_p_array_));
			memset(curr_block_p_array_, 0, sizeof(curr_block_p_array_));

		}
		~tagged_heap_category_t() {

			for(u8 i = 0; i < 64; ++i)
				internal_deallocate(i);

		}



	private:
		inline block_type* push_block() {

			block_type* prev_block_p = tail_block_p_array_[pac::current_thread_index()];

			block_type* block_p = (block_type*)allocator_.allocate(sizeof(block_type) + block_capacity_);
			new(block_p) block_type(block_capacity_);

			block_p->prev_p = prev_block_p;

			if (prev_block_p != 0)
				prev_block_p->next_p = block_p;
			else
				head_block_p_array_[pac::current_thread_index()] = block_p;

			tail_block_p_array_[pac::current_thread_index()] = block_p;
			curr_block_p_array_[pac::current_thread_index()] = block_p;
			block_count_array_[pac::current_thread_index()]++;

			return block_p;
		}
		inline block_type* pick_a_block(sz offset) {

			block_type* block_p = curr_block_p_array_[pac::current_thread_index()];

			if (block_p == 0) {

				block_p = push_block();

			}
			else {

				while (block_p->is_full(offset)) {

					if (block_p->next_p == 0) {

						block_p = push_block();
						break;

					}

					block_p = block_p->next_p;

				}

			}

			curr_block_p_array_[pac::current_thread_index()] = block_p;

			return block_p;
		}

		inline void internal_deallocate(u8 thread_index) {

			block_type* block_p = tail_block_p_array_[thread_index];

			while (block_p != 0) {

				block_type* block_prev_p = block_p->prev_p;
				allocator_.deallocate(block_p, block_capacity_ + sizeof(block_type));
				block_p = block_prev_p;

			}

			block_count_array_[pac::current_thread_index()] = 0;

		}
		inline void internal_reset_blocks(u8 thread_index) {

			block_type* block_p = tail_block_p_array_[thread_index];

			while (block_p != 0) {

				block_type* block_prev_p = block_p->prev_p;

				block_p->reset();

				block_p = block_prev_p;

			}

			curr_block_p_array_[thread_index] = head_block_p_array_[thread_index];

		}



	public:
		/**
		 *	Deallocates all blocks in the current thread.
		 */
		inline void deallocate() {

			internal_deallocate(pac::current_thread_index());

		}
		/**
		 *	Resets all blocks in the current thread.
		 */
		inline void reset_blocks() {

			internal_reset_blocks(pac::current_thread_index());

		}
		inline u8* allocate(sz size, sz align) {

			block_type* block_p = pick_a_block(size + sizeof(sz) + align);			

			return block_p->allocate(size, align);
		}
		inline block_type& head_block() {

			return *head_block_p_array_[pac::current_thread_index()];
		}
		inline block_type& tail_block() {

			return *tail_block_p_array_[pac::current_thread_index()];
		}
		inline block_type& current_block() {

			return *curr_block_p_array_[pac::current_thread_index()];
		}
		inline u32 block_count() {

			return block_count_array_[pac::current_thread_index()];
		}

	};



	/**
	 *	A tagged heap manages memory block allocations and categories.
	 */
	template<
		class allocator_type__ = typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<u8>,
		class category_cell_allocator_type__ = typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<
			typename containers::handle_map_cell_type<typename tagged_heap_category_t<allocator_type__>>
		>,
		class category_id_allocator_type__ = typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<
			typename containers::handle_map_id_type<typename tagged_heap_category_t<allocator_type__>>
		>
	>
	class NCPP_DEFAULT_ALIGNAS tagged_heap_t {

	public:




	public:
		using allocator_type = allocator_type__;
		using block_type = tagged_heap_block;
		using category_type = typename tagged_heap_category_t<allocator_type__>;
		using category_cell_allocator_type = category_cell_allocator_type__;
		using category_id_allocator_type = category_id_allocator_type__;
		using category_map = typename containers::handle_map_t<category_type, category_id_allocator_type, category_cell_allocator_type>;
		using category_id_type = typename category_map::id_type;
		using category_cell_type = typename category_map::cell_type;



	private:
		sz capacity_;

		category_map category_map_;



	public:
		inline sz capacity() const { return capacity_; }

		inline category_map& get_category_map_() { return category_map_; }
		inline const category_map& get_category_map_() const { return category_map_; }



	public:
		inline tagged_heap_t(
			sz capacity = NCPP_DEFAULT_TAGGED_HEAP_CAPACITY
		) :
			capacity_(capacity),
			category_map_(capacity)
		{



		}
		inline tagged_heap_t(
			const category_id_allocator_type& category_id_allocator,
			const category_cell_allocator_type& category_cell_allocator,
			sz capacity = NCPP_TAGGED_HEAP_DEFAULT_CAPACITY
		) :
			capacity_(capacity),
			category_map_(capacity, category_id_allocator, category_cell_allocator)
		{



		}
		~tagged_heap_t() {



		}

		inline tagged_heap_t(const tagged_heap_t&) = delete;
		inline tagged_heap_t& operator = (const tagged_heap_t&) = delete;
		inline tagged_heap_t(tagged_heap_t&&) = delete;
		inline tagged_heap_t& operator = (tagged_heap_t&&) = delete;



	public:
		inline category_id_type create_category() {
			return create_category(NCPP_DEFAULT_TAGGED_HEAP_BLOCK_CAPACITY);
		}
		inline category_id_type create_category(sz block_capacity) {					

			return category_map_.insert(category_type(block_capacity));
		}
		inline category_type& category(category_id_type handle) {

			return category_map_.at(handle).item;
		}
		inline void delete_category(category_id_type handle) {

			return category_map_.erase(handle);
		}
		inline u8* allocate(category_id_type category_id, sz size, sz align = NCPP_DEFAULT_ALIGN) {

			category_cell_type& category_cell = category_map_.at(category_id);

			return category_cell.item.allocate(size, align);
		}
		inline void deallocate(category_id_type category_id) {

			category_cell_type& category_cell = category_map_.at(category_id);

			category_cell.item.deallocate();

		}
		inline void reset_blocks(category_id_type category_id) {

			category_cell_type& category_cell = category_map_.at(category_id);

			category_cell.item.reset_blocks();

		}

	};



#pragma region Allocators
	template <class value_type__, class tagged_heap_type__ = tagged_heap_t<>>
	class NCPP_DEFAULT_ALIGNAS tgh_allocator_t
	{
	public:
		using size_type = sz;
		using difference_type = ptrdiff_t;
		using pointer = value_type__*;
		using const_pointer = const value_type__*;
		using reference = value_type__&;
		using const_reference = const value_type__&;
		using value_type = value_type__;
		using tagged_heap_type = tagged_heap_type__;
		using tagged_heap_cid_type = typename tagged_heap_type::category_id_type;



	private:
		tagged_heap_type* tagged_heap_p_;

		tagged_heap_cid_type category_id_;



	public:
		inline tagged_heap_type& tagged_heap() { return *tagged_heap_p_; }
		inline const tagged_heap_type& tagged_heap() const { return *tagged_heap_p_; }

		inline tagged_heap_cid_type category_id() const { return category_id_; }



	public:
		inline tgh_allocator_t() :
			tagged_heap_p_(0),
			category_id_({ 0 })
		{



		}
		inline tgh_allocator_t(tagged_heap_type& tagged_heap, tagged_heap_cid_type category_id) :
			tagged_heap_p_(&tagged_heap),
			category_id_(category_id)
		{
		

		
		}
		inline tgh_allocator_t(const tgh_allocator_t& other) :
			tgh_allocator_t((tagged_heap_type&)(*other.tagged_heap_p_), other.category_id_)
		{


		
		}

		inline tgh_allocator_t<value_type>& operator=(const tgh_allocator_t& other) {
			
			tagged_heap_p_ = other.tagged_heap_p_;
			category_id_ = other.category_id_;

			return *this; 
		}

		template <class other_value_type__>
		inline tgh_allocator_t(typename const tgh_allocator_t<other_value_type__, tagged_heap_type>& other) :
			tgh_allocator_t((tagged_heap_type&)other.tagged_heap(), other.category_id())
		{



		}

		template <class other_value_type__>
		inline tgh_allocator_t& operator=(typename const tgh_allocator_t<other_value_type__, tagged_heap_type>& other) {

			tagged_heap_p_ = &(other.other.tagged_heap());
			category_id_ = other.category_id();

			return *this;
		}



		inline pointer   allocate(size_type n, sz align = NCPP_DEFAULT_ALIGN) {

			assert(tagged_heap_p_ && "tagged heap is null");

			return (pointer)(tagged_heap_p_->allocate(category_id_, n * sizeof(value_type), align));
		}

		inline void      deallocate(void* p, sz n = sizeof(value_type)) {


		}

		inline void reset_blocks() {

			assert(tagged_heap_p_ && "tagged heap is null");

			tagged_heap_p_->reset_blocks(category_id_);

		}
		inline void deallocate_blocks() {

			assert(tagged_heap_p_ && "tagged heap is null");

			tagged_heap_p_->deallocate(category_id_);

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
		struct rebind { typedef tgh_allocator_t<U> other; };
	};
#pragma endregion

}

