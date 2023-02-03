#pragma once

/**
 *  @file ncpp/containers/fixed_vector_queue.hpp
 *  @brief Implements fixed vector queue.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        /**
         *  A handle_map is a map storing items in a dense set and linking each item to an id storing in sparse set.
         *  Notes: 
         *      + 'fl' means  'free list'.
         *      + 'mai' means 'meta and item'.
         */
        template<typename item_type, template<typename item_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN handle_map_t {

#pragma region Nested Types
        public:
            struct NCPP_SET_ALIGN(64) id_type {

                union {

                    struct {

                        union {

                            u32 inner_index;
                            u32 outer_index;
                            u32 fl_next_index;

                        };

                        u32 generation : 15;
                        u32 is_free : 1;

                    };
                    
                    u64 value;

                };



                inline bool is_has_next() const {

                    return fl_next_index != 0xFFFFFFFF;
                }
                inline bool operator==(const id_type& b) const { return (value == b.value); }
                inline bool operator!=(const id_type& b) const { return (value != b.value); }
                inline bool operator< (const id_type& b) const { return (value < b.value); }
                inline bool operator> (const id_type& b) const { return (value > b.value); }

            };
            friend struct id_type;

            struct NCPP_DEFAULT_SET_ALIGN mai_type {

                u32 outer_index;
                u32 inner_index;
                u32 is_sleep : 1;

                item_type item;



                inline item_type& operator * () {

                    return item;
                }
                inline const item_type& operator * () const {

                    return item;
                }
                inline item_type* operator -> () {

                    return &item;
                }
                inline const item_type* operator -> () const {

                    return &item;
                }

            };
            friend struct mai_type;

            struct erase_by_outer_index {};
            struct erase_by_handle {};
            struct erase_by_inner_index {};
            struct erase_by_mai {};
#pragma endregion



#pragma region Typedefs
        public:
            using item_set_type = typename std::vector<item_type, typename allocator_t<item_type>>;
            using mai_set_type = typename std::vector<mai_type, typename allocator_t<mai_type>>;
            using id_set_type = typename std::vector<id_type, typename allocator_t<id_type>>;
#pragma endregion



#pragma region Properties
        private:
            mai_set_type dense_set_;
            
            id_set_type unique_sparse_set_;
            id_set_type& sparse_set_;

            u32 unique_fl_front_;
            u32& fl_front_;
            u32 unique_fl_back_;
            u32& fl_back_;

            bool unique_is_fragmented_;
            bool& is_fragmented_;

            bool is_shared_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline sz size() const { return dense_set_.size(); }
            inline sz capacity() const { return dense_set_.capacity(); }

            inline bool is_full() const { return size() == capacity(); }
            inline bool is_fl_empty() const { return unique_fl_front_ == 0xFFFFFFFF; }

            inline mai_set_type& dense_set() { return dense_set_; }
            inline const mai_set_type& dense_set() const { return dense_set_; }

            inline id_set_type& sparse_set() { return sparse_set_; }
            inline const id_set_type& sparse_set() const { return sparse_set_; }

            inline u32 fl_front() const { return fl_front_; }
            inline u32 fl_back() const { return fl_back_; }

            inline bool is_fragmented() const { return is_fragmented_; }

            inline bool is_shared() const { return is_shared_; }

            inline mai_type* begin() { return dense_set_.data(); }
            inline const mai_type* begin() const { return dense_set_.data(); }
            inline mai_type* end() { return dense_set_.data() + dense_set_.size(); }
            inline const mai_type* end() const { return dense_set_.data() + dense_set_.size(); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline handle_map_t(sz reserve_count) :
                unique_sparse_set_(),
                sparse_set_(unique_sparse_set_),

                unique_fl_front_(0xFFFFFFFF),
                fl_front_(unique_fl_front_),
                unique_fl_back_(0xFFFFFFFF),
                fl_back_(unique_fl_back_),

                unique_is_fragmented_(0),
                is_fragmented_(unique_is_fragmented_),

                is_shared_(0)
            {

                unique_sparse_set_.reserve(reserve_count);
                dense_set_.reserve(reserve_count);

            }
            /**
             *  Initialization constructor for shared map
             */
            inline handle_map_t(sz reserve_count, id_set_type& shared_sparse_id_set, u32& shared_fl_front, u32& shared_fl_back, bool& shared_is_fragmented) :
                unique_sparse_set_(),
                sparse_set_(shared_sparse_id_set),

                unique_fl_front_(0xFFFFFFFF),
                fl_front_(shared_fl_front),
                unique_fl_back_(0xFFFFFFFF),
                fl_back_(shared_fl_back),

                unique_is_fragmented_(0),
                is_fragmented_(shared_is_fragmented),

                is_shared_(1)
            {

                dense_set_.reserve(reserve_count);

            }
            /**
             *  Default constructor
             */
            inline handle_map_t() :
                handle_map_t(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {



            }
            /**
             *  Destructor
             */
            virtual ~handle_map_t() {

                if (is_shared_) {

                    clear();

                }
                else {

                    reset();

                }

            }

            /**
             *  Copy Constructor
             */
            inline handle_map_t(const handle_map_t& other) :
                handle_map_t(other.capacity())
            {

                unique_sparse_set_ = other.sparse_set_;
                dense_set_ = other.dense_set_;

            }
            /**
             *  Copy Operator
             */
            inline handle_map_t& operator = (const handle_map_t& other)
            {

                if (is_shared_) {

                    clear();

                    for (auto& mai : other) {

                        insert(mai.item);

                    }

                }
                else {

                    unique_is_fragmented_ = other.is_fragmented_;
                    unique_fl_front_ = other.fl_front_;
                    unique_fl_back_ = other.fl_back_;
                    unique_sparse_set_ = other.sparse_set_;
                    dense_set_ = other.dense_set_;

                }

            }

            /**
             *  Move Constructor
             */
            inline handle_map_t(handle_map_t&& other) :
                handle_map_t(other.capacity())
            {

                unique_sparse_set_ = other.sparse_set_;
                dense_set_ = other.dense_set_;

                other.~handle_map_t();

            }
            /**
             *  Move Operator
             */
            inline handle_map_t& operator = (handle_map_t&& other)
            {

                if (is_shared_) {

                    clear();

                    for (auto& mai : other) {

                        insert(mai.item);

                    }

                }
                else {

                    unique_is_fragmented_ = other.is_fragmented_;
                    unique_fl_front_ = other.fl_front_;
                    unique_fl_back_ = other.fl_back_;
                    unique_sparse_set_ = other.sparse_set_;
                    dense_set_ = other.dense_set_;

                }

                other.~handle_map_t();

            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_passed_type>
            inline id_type insert_main_t(item_passed_type&& item) {

                assert(!is_full() && "the handle map is full, cant insert any item.");

                is_fragmented_ = true;

                id_type handle = {0, 0};

                if (is_fl_empty()) {

                    handle.outer_index = sparse_set_.size();
                    sparse_set_.push_back({ (u32)dense_set_.size(), 0, 0 });

                }
                else {

                    handle.outer_index = fl_back_;
                    id_type& id = sparse_set_[handle.outer_index];

                    if (fl_front_ == fl_back_) {
                            
                        fl_front_ = 0xFFFFFFFF;


                    }

                    fl_back_ = id.fl_next_index;

                    id.is_free = 0;
                    ++id.generation;

                    id.inner_index = dense_set_.size();

                }

                dense_set_.push_back({

                    handle.outer_index,
                    (u32)dense_set_.size(),
                    0,
                    std::forward<item_passed_type>(item)

                });

                return handle;
            }



        public:
            inline id_type insert(item_type& item) {

                return insert_main_t(std::forward<item_type&>(item));
            }
            inline id_type insert(item_type&& item) {

                return insert_main_t(std::forward<item_type>(item));
            }

            inline void erase(id_type& handle) {

                assert(handle.outer_index < sparse_set_.size() && "outer index out of range.");
                assert(!sparse_set_[handle.outer_index].is_free && "id is already free.");
                assert(handle.generation == sparse_set_[handle.outer_index].generation && "erases old generation.");

                erase(handle.outer_index);

            }
            inline void erase(erase_by_handle, id_type& handle) {

                erase(handle.outer_index);

            }
            inline void erase(mai_type& mai) {

                erase(mai.outer_index);

            }
            inline void erase(erase_by_mai, mai_type& mai) {

                erase(mai.outer_index);

            }
            inline void erase(u32 outer_index) {

                assert(outer_index < sparse_set_.size() && "outer index out of range.");

                is_fragmented_ = true;

                id_type& id = sparse_set_[outer_index];
                u32 inner_index = id.inner_index;

                id.fl_next_index = fl_back_;

                id.is_free = 1;

                if (is_fl_empty()) {

                    fl_front_ = outer_index;

                }

                fl_back_ = outer_index;

                if (id.inner_index != dense_set_.size() - 1) {

                    dense_set_.back().inner_index = inner_index;
                    sparse_set_[dense_set_.back().outer_index].inner_index = inner_index;
                    std::swap(dense_set_[inner_index], dense_set_.back());

                }

                dense_set_.pop_back();
                             
            }
            inline void erase(erase_by_outer_index, u32 outer_index) {

                erase(outer_index);

            }
            inline void erase(erase_by_inner_index, u32 inner_index) {

                assert(outer_index < dense_set_.size() && "inner index out of range.");

                erase(dense_set_[inner_index].outer_index);

            }

            inline void swap(id_type& handle1, id_type& handle2) {

                assert(handle1.outer_index < sparse_set_.size() && "outer index out of range (handle1).");
                assert(!sparse_set_[handle1.outer_index].is_free && "id is already free (handle1).");
                assert(handle1.generation == sparse_set_[handle1.outer_index].generation && "erases old generation (handle1).");

                assert(handle2.outer_index < sparse_set_.size() && "outer index out of range (handle2).");
                assert(!sparse_set_[handle2.outer_index].is_free && "id is already free (handle2).");
                assert(handle2.generation == sparse_set_[handle2.outer_index].generation && "erases old generation (handle2).");

                swap(handle1.outer_index, handle2.outer_index);

            }
            inline void swap(mai_type& mai1, mai_type& mai2) {

                swap(mai1.outer_index, mai2.outer_index);

            }
            inline void swap(u32 outer_index1, u32 outer_index2) {

                assert(outer_index1 < sparse_set_.size() && "outer index 1 out of range.");
                assert(outer_index2 < sparse_set_.size() && "outer index 2 out of range.");

                std::swap(sparse_set_[outer_index1].inner_index, sparse_set_[outer_index2].inner_index);

            }

            inline void clear() {
                              
                for (auto it = begin(); it != end();) {

                    erase(*it);

                }

            }
            inline void reset() {

                is_fragmented_ = 0;
                fl_front_ = 0xFFFFFFFF;
                fl_back_ = 0xFFFFFFFF;
                sparse_set_.clear();
                dense_set_.clear();

            }
#pragma endregion

        };

    }

}