#pragma once

/**
 *  @file ncpp/containers/id_map.hpp
 *  @brief Implements id map.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/containers/fls_vector.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type__>
        union NCPP_ALIGNAS(8) handle_map_id_type {

            struct {

                union {

                    u32 outer_index;
                    u32 inner_index;
                    u32 fl_next_index;

                };

                u32 generation : 31;

                u32 is_free : 1;

            };

            u64 value;



            inline bool operator != (const handle_map_id_type& other) const { return value != other.value; }
            inline bool operator == (const handle_map_id_type& other) const { return value == other.value; }

        };



        template<typename item_type__>
        struct NCPP_ALIGNAS(16) handle_map_cell_type {

            union {

                u32 outer_index;
                u32 fl_next_index;

            };

            u32 inner_index;

            u32 is_free : 1;

            item_type__ item;



            inline item_type__& operator * () { return item; }
            inline const item_type__& operator * () const { return item; }
            inline item_type__* operator -> () { return &item; }
            inline const item_type__* operator -> () const { return &item; }

        };



        template<
            typename item_type__, 
            class id_allocator_type__ = typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<typename handle_map_id_type<item_type__>>,
            class cell_allocator_type__ = typename NCPP_DEFAULT_ALLOCATOR_TEMPLATE<typename handle_map_cell_type<item_type__>>
        >
        class NCPP_DEFAULT_ALIGNAS handle_map_t {

#pragma region Nested Types
        public:
            using id_type = typename handle_map_id_type<item_type__>;
            using id_allocator_type = id_allocator_type__;
            using cell_type = typename handle_map_cell_type<item_type__>;
            using cell_allocator_type = cell_allocator_type__;
#pragma endregion



#pragma region Typedefs
        public:
            using item_type = item_type__;
            using id_vector_type = typename fls_vector_t<id_type, id_allocator_type>;
            using cell_vector_type = typename fls_vector_t<cell_type, cell_allocator_type>;

            using iterator = cell_type*;
            using const_iterator = const cell_type*;
#pragma endregion



#pragma region Properties
        private:
            u32 capacity_;

            cell_vector_type cell_vector_;
            id_vector_type id_vector_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline u32 count() const { return cell_vector_.count(); }
            inline u32 size() const { return cell_vector_.size(); }
            inline u32 capacity() const { return capacity_; }

            inline cell_vector_type& cell_vector() { return cell_vector_; }
            inline const cell_vector_type& cell_vector() const { return cell_vector_; }
            inline id_vector_type& id_vector() { return id_vector_; }
            inline const id_vector_type& id_vector() const { return id_vector_; }

            inline iterator begin() { return cell_vector_.data(); }
            inline const_iterator begin() const { return cell_vector_.data(); }
            inline const_iterator cbegin() const { return cell_vector_.data(); }
            inline iterator end() { return cell_vector_.data() + cell_vector_.count(); }
            inline const_iterator end() const { return cell_vector_.data() + cell_vector_.count(); }
            inline const_iterator cend() const { return cell_vector_.data() + cell_vector_.count(); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline handle_map_t(u32 capacity) :
                capacity_(capacity),
                cell_vector_(capacity),
                id_vector_(capacity)
            {



            }
            /**
             *  Initialization constructor with allocators
             */
            inline handle_map_t(u32 capacity, const id_allocator_type& id_allocator, const cell_allocator_type& cell_allocator) :
                capacity_(capacity),
                cell_vector_(capacity, id_allocator),
                id_vector_(capacity, cell_allocator)
            {



            }
            /**
             *  Default constructor
             */
            inline handle_map_t() :
                handle_map_t(1024)
            {



            }
            /**
             *  Destructor
             */
            ~handle_map_t() {

                reset();

            }

            /**
             *  Copy constructor
             */
            inline handle_map_t(const handle_map_t& other) :
                handle_map_t(other.capacity_)
            {

                for (auto& cell : other) {

                    insert(cell.item);

                }

            }
            /**
             *  Copy operator
             */
            inline handle_map_t& operator = (const handle_map_t& other)
            {

                reset();

                for (auto& cell : other) {

                    insert(cell.item);

                }

            }

            /**
             *  Move constructor
             */
            inline handle_map_t(handle_map_t&& other) :
                handle_map_t(other.capacity_)
            {

                for (auto& cell : other) {

                    insert(cell.item);

                }

                other.clear();

            }
            /**
             *  Move operator
             */
            inline handle_map_t& operator = (handle_map_t&& other)
            {

                reset();

                for (auto& cell : other) {

                    insert(cell.item);

                }

                other.clear();

            }

            /**
             *  [] operator
             */
            inline cell_type& operator [] (u32 inner_index) {

                return at(inner_index);
            }
            /**
             *  [] operator
             */
            inline const cell_type& operator [] (u32 inner_index) const {

                return at(inner_index);
            }
            /**
             *  [] operator
             */
            inline cell_type& operator [] (id_type handle) {

                return at(handle);
            }
            /**
             *  [] operator
             */
            inline const cell_type& operator [] (id_type handle) const {

                return at(handle);
            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_passed_type>
            inline id_type insert_main_t(item_passed_type&& item, u32 insertion_index) {

                id_type handle = { 0 };

                handle.inner_index = insertion_index;

                cell_type cell;

                cell.item = std::forward<item_passed_type>(item);
                cell.outer_index = id_vector_.insertable_index();
                cell.inner_index = handle.inner_index;

                if(id_vector_.size() > cell.outer_index)
                    handle.generation = id_vector_[cell.outer_index].generation;

                id_vector_.insert(handle);

                handle.outer_index = cell.outer_index;

                cell_vector_.insert(std::move(cell), insertion_index);

                return handle;
            }



        public:
            inline id_type insert(const item_type& item) {

                return insert_main_t(std::forward<const item_type&>(item), cell_vector_.insertable_index());
            }
            inline id_type insert(item_type&& item) {

                return insert_main_t(std::forward<item_type>(item), cell_vector_.insertable_index());
            }
            inline id_type insert(const item_type& item, u32 insertion_index) {

                return insert_main_t(std::forward<const item_type&>(item), insertion_index);
            }
            inline id_type insert(item_type&& item, u32 insertion_index) {

                return insert_main_t(std::forward<item_type>(item), insertion_index);
            }

            inline void erase(id_type handle) {

                check_handle(handle);

                erase(handle.outer_index);
            }

            inline void erase(cell_type& cell) {
                              
                erase(cell.outer_index);
            }

            inline void erase(u32 outer_index) {

                assert(outer_index < cell_vector_.size() && "outer index out of range");

                id_type id = id_vector_[outer_index];

                u32 inner_index = id.inner_index;

                u32 back_index = cell_vector_.back_index();
                
                if (back_index != inner_index) {

                    cell_vector_.swap_items(back_index, inner_index);

                }

                id_vector_[cell_vector_[inner_index].outer_index].inner_index = inner_index;
                cell_vector_[inner_index].inner_index = inner_index;
                ++(id_vector_[outer_index].generation);

                id_vector_.erase(outer_index);
                cell_vector_.erase(back_index);

            }

            inline bool is_valid(id_type handle) {

                if (handle.outer_index >= cell_vector_.size()) return false;

                id_type id = id_vector_[handle.outer_index];

                return (
                    (id.generation == handle.generation)
                    && !id.is_free
                );
            }

            inline void check_handle(id_type handle) {

                assert(handle.outer_index < cell_vector_.size() && "outer index out of range");

                id_type id = id_vector_[handle.outer_index];

                assert((id.generation == handle.generation) && "old generation");
                
            }

            inline void clear() {

                for (auto it = begin(); count() != 0;) {

                    erase(it->outer_index);

                }

            }
            inline void reset() {

                cell_vector_.clear();
                id_vector_.clear();

            }

            inline cell_type& at(u32 inner_index) {

                return cell_vector_[inner_index];
            }
            inline const cell_type& at(u32 inner_index) const {

                return cell_vector_[inner_index];
            }
            inline cell_type& at(id_type handle) {

                check_handle(handle);

                return cell_vector_[id_vector_[handle.outer_index].inner_index];
            }
            inline const cell_type& at(id_type handle) const {

                check_handle(handle);

                return cell_vector_[id_vector_[handle.outer_index].inner_index];
            }
#pragma endregion

        };

    }

}