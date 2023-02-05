#pragma once

/**
 *  @file ncpp/containers/handle_map.hpp
 *  @brief Implements handle map.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type__, template<typename data_type__> class allocator_t__ = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN handle_map_t {

#pragma region Nested Types
        public:
            union NCPP_SET_ALIGN(8) id_type {

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



                inline bool operator != (const id_type& other) const { return value != other.value; }
                inline bool operator == (const id_type& other) const { return value == other.value; }

            };



            struct NCPP_SET_ALIGN(16) cell_type {

                u32 outer_index;
                u32 inner_index;
                u32 is_sleep : 1;

                item_type__ item;



                inline item_type__& operator * () { return item; }
                inline const item_type__& operator * () const { return item; }
                inline item_type__* operator -> () { return &item; }
                inline const item_type__* operator -> () const { return &item; }

            };
#pragma endregion



#pragma region Typedefs
        public:
            using item_type = item_type__;
            using item_vector_type = std::vector<item_type, allocator_t__<item_type>>;            
            using cell_vector_type = std::vector<cell_type, allocator_t__<cell_type>>;
            using id_vector_type = std::vector<id_type, allocator_t__<id_type>>;
            using iterator = item_type*;
            using const_iterator = const item_type*;
#pragma endregion



#pragma region Properties
        private:
            cell_vector_type dense_vector_;
            id_vector_type sparse_vector_;
            u32 fl_front_;
            u32 fl_back_;
            bool is_fragmented_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline sz size() const { return dense_vector_.size(); }
            inline sz capacity() const { return dense_vector_.capacity(); }

            inline cell_vector_type& dense_vector() { return dense_vector_; }
            inline const cell_vector_type& dense_vector() const { return dense_vector_; }
            inline id_vector_type& sparse_vector() { return sparse_vector_; }
            inline const id_vector_type& sparse_vector() const { return sparse_vector_; }

            inline u32 fl_front() const { return fl_front_; }
            inline u32 fl_back() const { return fl_back_; }
            inline bool is_fl_empty() const { return fl_front_ == 0xFFFFFFFF; }
            
            inline bool is_fragmented() const { return is_fragmented_; }

            inline iterator begin() { return dense_vector_.data(); }
            inline const_iterator begin() const { return dense_vector_.data(); }
            inline const_iterator cbegin() const { return dense_vector_.data(); }
            inline iterator end() { return dense_vector_.data() + size(); }
            inline const_iterator end() const { return dense_vector_.data() + size(); }
            inline const_iterator cend() const { return dense_vector_.data() + size(); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline handle_map_t(sz reserve_count) :
                fl_front_(0xFFFFFFFF),
                fl_back_(0xFFFFFFFF),
                is_fragmented_(0)
            {

                dense_vector_.reserve(reserve_count);
                sparse_vector_.reserve(reserve_count);

            }
            /**
             *  Default constructor
             */
            inline handle_map_t() :  /** Automatically calls to the initialization constructor with the default reserve count. */
                handle_map_t(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {



            }
            /**
             *  Destructor
             */
            ~handle_map_t() {



            }

            /**
             *  [] Operators
             */
            inline cell_type& operator[] (u32 inner_index) {

                assert(inner_index < dense_vector_.size() && "inner index out of range.");

                return dense_vector_[inner_index];
            }
            inline const cell_type& operator[] (u32 inner_index) const {

                assert(inner_index < dense_vector_.size() && "inner index out of range.");

                return dense_vector_[inner_index];
            }
            inline cell_type& operator[] (id_type handle) {

                check_handle(handle);

                return dense_vector_[sparse_vector_[handle.outer_index].inner_index];
            }
            inline const cell_type& operator[] (id_type handle) const {

                check_handle(handle);

                return dense_vector_[sparse_vector_[handle.outer_index].inner_index];
            }
#pragma endregion



#pragma region Methods
        private:
            template<typename passed_type__>
            inline id_type insert_main_t(passed_type__&& item) {

                id_type handle = { 0 };

                is_fragmented_ = 1;

                if (is_fl_empty()) {

                    handle.inner_index = dense_vector_.size();

                    sparse_vector_.push_back(handle);

                    handle.outer_index = sparse_vector_.size() - 1;

                }
                else {

                    u32 outer_index = fl_back_;

                    id_type& id = sparse_vector_[outer_index];

                    fl_back_ = id.fl_next_index;

                    if (is_fl_empty()) {

                        fl_front_ = 0xFFFFFFFF;

                    }

                    id.is_free = 0;
                    id.inner_index = dense_vector_.size();

                    handle = id;
                    handle.outer_index = outer_index;

                }

                dense_vector_.push_back({

                    (u32)dense_vector_.size(),
                    handle.outer_index,
                    0,
                    std::forward<passed_type__>(item)

                });

                return handle;
            }



        public:
            inline id_type insert(const item_type& item) {
                return insert_main_t(item);
            }
            inline id_type insert(item_type&& item) {
                return insert_main_t(std::forward<item_type>(item));
            }

            inline void erase(id_type handle) {

                check_handle(handle);

                erase(handle.outer_index);
            }
            inline void erase(u32 outer_index) {

                assert(outer_index < sparse_vector_.size() && "outer index out of range.");

                is_fragmented_ = 1;

                id_type id = sparse_vector_[outer_index];
                u32 inner_index = id.inner_index; 

                id.is_free = 1;
                ++id.generation;
                id.fl_next_index = fl_back_;

                sparse_vector_[outer_index] = id;

                if (is_fl_empty()) {

                    fl_front_ = outer_index;

                }

                fl_back_ = outer_index;

                if (inner_index != dense_vector_.size() - 1) {

                    cell_type& last_cell = dense_vector_.back();
                    last_cell.inner_index = inner_index;
                    sparse_vector_[last_cell.outer_index].inner_index = inner_index;
                    std::swap(dense_vector_.at(inner_index), last_cell);

                }

                dense_vector_.pop_back();

            }

            inline void check_handle(id_type handle) const {

                assert(handle.outer_index < sparse_vector_.size() && "outer index out of range.");
                
                id_type id = sparse_vector_[handle.outer_index];

                assert(!id.is_free && "handle is free.");
                assert(id.generation == handle.generation && "old generation.");

            }
            inline bool is_valid(id_type handle) const {

                if (handle.outer_index >= sparse_vector_.size()) return false;

                id_type id = sparse_vector_[handle.outer_index];

                return (!id.is_free && (id.generation == handle.generation));
            }

            inline cell_type& at(u32 inner_index) {

                assert(inner_index < dense_vector_.size() && "inner index out of range.");

                return dense_vector_[inner_index];
            }
            inline const cell_type& at(u32 inner_index) const {

                assert(inner_index < dense_vector_.size() && "inner index out of range.");

                return dense_vector_[inner_index];
            }
            inline cell_type& at(id_type handle) {

                check_handle(handle);

                return dense_vector_[sparse_vector_[handle.outer_index].inner_index];
            }
            inline const cell_type& at(id_type handle) const {

                check_handle(handle);

                return dense_vector_[sparse_vector_[handle.outer_index].inner_index];
            }
#pragma endregion

        };

    }

}