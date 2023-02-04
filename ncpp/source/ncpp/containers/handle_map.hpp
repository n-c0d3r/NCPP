#pragma once

/**
 *  @file ncpp/containers/handle_map_t.hpp
 *  @brief Implements handle_map_t.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, template<typename item_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN handle_multimap_t;



        /**
         *  A handle_map is a map storing items in a dense set and linking each item to an id storing in sparse set.
         *  Notes: 
         *      + 'fl' means  'free list'.
         *      + 'mai' means 'meta and item'.
         */
        template<typename item_type, template<typename item_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN handle_map_t {

        public:
            friend class handle_multimap_t<item_type, allocator_t>;



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
                u32 map_index : 15;
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
            using multimap_type = typename handle_multimap_t<item_type, allocator_t>;
#pragma endregion



#pragma region Properties
        private:
            u32 map_index_;

            mai_set_type dense_set_;
            
            id_set_type unique_sparse_set_;
            id_set_type* sparse_set_p_;

            u32 unique_fl_front_;
            u32* fl_front_p_;
            u32 unique_fl_back_;
            u32* fl_back_p_;

            bool unique_is_fragmented_;
            bool* is_fragmented_p_;

            bool is_shared_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline u32 map_index() const { return map_index_; }

            inline sz size() const { return dense_set_.size(); }
            inline sz capacity() const { return dense_set_.capacity(); }

            inline bool is_full() const { return size() == capacity(); }
            inline bool is_fl_empty() const { return (*fl_front_p_) == 0xFFFFFFFF; }

            inline mai_set_type& dense_set() { return dense_set_; }
            inline const mai_set_type& dense_set() const { return dense_set_; }

            inline id_set_type& sparse_set() { return *sparse_set_p_; }
            inline const id_set_type& sparse_set() const { return *sparse_set_p_; }

            inline u32 fl_front() const { return *fl_front_p_; }
            inline u32 fl_back() const { return *fl_back_p_; }

            inline bool is_fragmented() const { return *is_fragmented_p_; }

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
                map_index_(0),

                dense_set_(0),

                unique_sparse_set_(),
                sparse_set_p_(&unique_sparse_set_),

                unique_fl_front_(0xFFFFFFFF),
                fl_front_p_(&unique_fl_front_),
                unique_fl_back_(0xFFFFFFFF),
                fl_back_p_(&unique_fl_back_),

                unique_is_fragmented_(0),
                is_fragmented_p_(&unique_is_fragmented_),

                is_shared_(0)
            {

                (*sparse_set_p_).reserve(reserve_count);
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
             *  Initialization constructor (shared mode)
             */
            inline handle_map_t(
                sz reserve_count, 
                u32 map_index, 
                id_set_type& sparse_set, 
                u32& fl_front,
                u32& fl_back,
                bool& is_fragmented
            ) :
                map_index_(map_index),

                dense_set_(0),

                unique_sparse_set_(0),
                sparse_set_p_(&sparse_set),

                unique_fl_front_(0xFFFFFFFF),
                fl_front_p_(&fl_front),
                unique_fl_back_(0xFFFFFFFF),
                fl_back_p_(&fl_back),

                unique_is_fragmented_(0),
                is_fragmented_p_(&is_fragmented),

                is_shared_(1)
            {

                dense_set_.reserve(reserve_count);

            }
            /**
             *  Destructor
             */
            virtual ~handle_map_t() {

                if (is_shared_)
                    clear();
                else
                    reset();

            }

            /**
             *  Copy Constructor
             */
            inline handle_map_t(const handle_map_t& other) :
                handle_map_t(other.capacity())
            {

                for (const auto& mai : other) {

                    insert(mai.item);

                }

            }
            /**
             *  Copy Operator
             */
            inline handle_map_t& operator = (const handle_map_t& other)
            {

                clear();
                for (const auto& mai : other) {

                    insert(mai.item);

                }

                return *this;
            }

            /**
             *  Move Constructor
             */
            inline handle_map_t(handle_map_t&& other) :
                handle_map_t(other.capacity())
            {
                
                for (auto& mai : other) {

                    insert(mai.item);

                }
                other.clear();

            }
            /**
             *  Move Operator
             */
            inline handle_map_t& operator = (handle_map_t&& other)
            {

                clear();
                for (auto& mai : other) {

                    insert(mai.item);

                }
                other.clear();
                
                return *this;
            }



            /**
             *  [] Operators
             */
            inline mai_type& operator [] (sz inner_index)
            {

                return at(inner_index);
            }
            inline const mai_type& operator [] (sz inner_index) const
            {

                return at(inner_index);
            }
            inline mai_type& operator [] (id_type handle)
            {

                return at(handle);
            }
            inline const mai_type& operator [] (id_type handle) const
            {

                return at(handle);
            }
#pragma endregion



#pragma region Methods
        private:
            inline void make_shared(multimap_type& multimap) {

                sparse_set_p_ = &multimap.sparse_set_;
                fl_front_p_ = &multimap.fl_front_;
                fl_back_p_ = &multimap.fl_back_;
                is_fragmented_p_ = &multimap.is_fragmented_;
                dense_set_.reserve(multimap.map_capacity_);

            }

            template<typename item_passed_type>
            inline id_type insert_main_t(item_passed_type&& item) {

                assert(!is_full() && "the handle map is full, cant insert any item.");

                *is_fragmented_p_ = true;

                id_type handle = {0, 0};

                if (is_fl_empty()) {

                    handle.outer_index = sparse_set_p_->size();
                    sparse_set_p_->push_back({ (u32)dense_set_.size(), 0, 0 });

                }
                else {

                    handle.outer_index = *fl_back_p_;
                    id_type& id = (*sparse_set_p_)[handle.outer_index];

                    if (*fl_front_p_ == *fl_back_p_) {
                            
                        *fl_front_p_ = 0xFFFFFFFF;


                    }

                    *fl_back_p_ = id.fl_next_index;

                    id.is_free = 0;
                    ++id.generation;

                    id.inner_index = dense_set_.size();

                }

                dense_set_.push_back({

                    handle.outer_index,
                    (u32)dense_set_.size(),
                    map_index_,
                    0,
                    std::forward<item_passed_type>(item)

                });

                return handle;
            }



        public:
            inline mai_type& at(sz inner_index)
            {

                return dense_set_[inner_index];
            }
            inline const mai_type& at(sz inner_index) const
            {

                return dense_set_[inner_index];
            }
            inline mai_type& at(id_type handle)
            {

                assert(handle.outer_index < *sparse_set_p_.size() && "outer index out of range.");
                assert(!(*sparse_set_p_)[handle.outer_index].is_free && "id is already free.");
                assert(handle.generation == *sparse_set_p_[handle.outer_index].generation && "erases old generation.");

                return dense_set_[(*sparse_set_p_)[handle.outer_index].inner_index];
            }
            inline const mai_type& at(id_type handle) const
            {

                assert(handle.outer_index < *sparse_set_p_.size() && "outer index out of range.");
                assert(!(*sparse_set_p_)[handle.outer_index].is_free && "id is already free.");
                assert(handle.generation == *sparse_set_p_[handle.outer_index].generation && "erases old generation.");

                return dense_set_[(*sparse_set_p_)[handle.outer_index].inner_index];
            }



            inline id_type insert(const item_type& item) {

                return insert_main_t(std::forward<const item_type&>(item));
            }
            inline id_type insert(item_type&& item) {

                return insert_main_t(std::forward<item_type>(item));
            }



            inline void erase(id_type handle) {

                assert(handle.outer_index < *sparse_set_p_.size() && "outer index out of range.");
                assert(!(*sparse_set_p_)[handle.outer_index].is_free && "id is already free.");
                assert(handle.generation == *sparse_set_p_[handle.outer_index].generation && "erases old generation.");

                erase(handle.outer_index);

            }
            inline void erase(erase_by_handle, id_type handle) {

                erase(handle.outer_index);

            }
            inline void erase(mai_type& mai) {

                erase(mai.outer_index);

            }
            inline void erase(erase_by_mai, mai_type& mai) {

                erase(mai.outer_index);

            }
            inline void erase(u32 outer_index) {

                assert(outer_index < (*sparse_set_p_).size() && "outer index out of range.");

                *is_fragmented_p_ = true;

                id_type& id = (*sparse_set_p_)[outer_index];
                u32 inner_index = id.inner_index;

                id.fl_next_index = *fl_back_p_;

                id.is_free = 1;

                if (is_fl_empty()) {

                    *fl_front_p_ = outer_index;

                }

                *fl_back_p_ = outer_index;

                if (inner_index != dense_set_.size() - 1) {

                    dense_set_.back().inner_index = inner_index;
                    (*sparse_set_p_)[dense_set_.back().outer_index].inner_index = inner_index;
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

            inline void swap(id_type handle1, id_type handle2) {

                assert(handle1.outer_index < *sparse_set_p_.size() && "outer index out of range (handle1).");
                assert(!(*sparse_set_p_)[handle1.outer_index].is_free && "id is already free (handle1).");
                assert(handle1.generation == *sparse_set_p_[handle1.outer_index].generation && "erases old generation (handle1).");

                assert(handle2.outer_index < *sparse_set_p_.size() && "outer index out of range (handle2).");
                assert(!(*sparse_set_p_)[handle2.outer_index].is_free && "id is already free (handle2).");
                assert(handle2.generation == *sparse_set_p_[handle2.outer_index].generation && "erases old generation (handle2).");

                swap(handle1.outer_index, handle2.outer_index);

            }
            inline void swap(mai_type& mai1, mai_type& mai2) {

                swap(mai1.outer_index, mai2.outer_index);

            }
            inline void swap(u32 outer_index1, u32 outer_index2) {

                assert(outer_index1 < (*sparse_set_p_).size() && "outer index 1 out of range.");
                assert(outer_index2 < (*sparse_set_p_).size() && "outer index 2 out of range.");

                std::swap((*sparse_set_p_)[outer_index1].inner_index, (*sparse_set_p_)[outer_index2].inner_index);

            }

            inline void clear() {
                              
                for (auto it = begin(); it != end();) {

                    erase(*it);

                }

            }
            inline void reset() {

                *is_fragmented_p_ = 0;
                *fl_front_p_ = 0xFFFFFFFF;
                *fl_back_p_ = 0xFFFFFFFF;
                sparse_set_p_->clear();
                dense_set_.clear();

            }
#pragma endregion

        };

    }

}