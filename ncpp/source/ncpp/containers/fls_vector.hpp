#pragma once

/**
 *  @file ncpp/containers/fls_vector.hpp
 *  @brief Implements free list supported vector.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type__, class allocator_type__  = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<item_type__>>
        class NCPP_DEFAULT_ALIGNAS fls_vector_t {

#pragma region Nested Types
        public:
            /**
             *  Sample item type.
             *  A item type must have:
             *      + U32 fl_next_index.
             *      + U32 is_free : 1.
             */
            struct NCPP_ALIGNAS(8) sample_item_type
            {

                u32 fl_next_index;
                u32 is_free : 1;

            };
#pragma endregion



#pragma region Typedefs
        public:
            using allocator_type = allocator_type__;
            using item_type = item_type__;
            using item_vector_type = std::vector<item_type, allocator_type__>;
            using iterator = item_type*;
            using const_iterator = const item_type*;
#pragma endregion



#pragma region Properties
        private:
            item_vector_type item_vector_;
            u32 fl_head_;
            u32 fl_tail_;
            bool is_fragmented_;
            u32 count_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline u32 count() const { return count_; }
            inline u32 size() const { return item_vector_.size(); }
            inline u32 capacity() const { return item_vector_.capacity(); }
            inline item_vector_type& item_vector() { return item_vector_; }
            inline const item_vector_type& item_vector() const { return item_vector_; }
            inline u32 fl_head() const { return fl_head_; }
            inline u32 fl_tail() const { return fl_tail_; }
            inline bool is_fl_empty() const { return fl_tail_ == NCPP_U32_MAX; }
            inline bool is_fragmented() const { return is_fragmented_; }

            inline iterator data() { return item_vector_.data(); }
            inline const_iterator data() const { return item_vector_.data(); }
            inline const_iterator cdata() const { return item_vector_.data(); }
            inline iterator begin() { return item_vector_.data(); }
            inline const_iterator begin() const { return item_vector_.data(); }
            inline const_iterator cbegin() const { return item_vector_.data(); }
            inline iterator end() { return item_vector_.data() + item_vector_.size(); }
            inline const_iterator end() const { return item_vector_.data() + item_vector_.size(); }
            inline const_iterator cend() const { return item_vector_.data() + item_vector_.size(); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline fls_vector_t(u32 capacity) :
                count_(0),
                fl_head_(NCPP_U32_MAX),
                fl_tail_(NCPP_U32_MAX),
                is_fragmented_(0)
            {

                item_vector_.reserve(capacity);

            }
            /**
             *  Initialization constructor with allocator
             */
            inline fls_vector_t(u32 capacity, const allocator_type& allocator) :
                count_(0),
                fl_head_(NCPP_U32_MAX),
                fl_tail_(NCPP_U32_MAX),
                is_fragmented_(0),
                item_vector_(allocator)
            {

                item_vector_.reserve(capacity);

            }
            /**
             *  Default constructor
             */
            inline fls_vector_t() :
                fls_vector_t(16)
            {



            }
            ~fls_vector_t() {

                clear();

            }

            /**
             *  Copy constructor
             */
            inline fls_vector_t(const fls_vector_t& other) :
                fls_vector_t(other.capacity())
            {

                fl_head_ = other.fl_head_;
                fl_tail_ = other.fl_tail_;
                is_fragmented_ = other.is_fragmented_;
                item_vector_ = other.item_vector_;

            }
            /**
             *  Copy operator
             */
            inline fls_vector_t& operator = (const fls_vector_t& other)
            {

                fl_head_ = other.fl_head_;
                fl_tail_ = other.fl_tail_;
                is_fragmented_ = other.is_fragmented_;
                item_vector_ = other.item_vector_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline fls_vector_t(fls_vector_t&& other) :
                fls_vector_t(other.capacity())
            {

                fl_head_ = other.fl_head_;
                fl_tail_ = other.fl_tail_;
                is_fragmented_ = other.is_fragmented_;
                item_vector_ = other.item_vector_;

                other.clear();

            }
            /**
             *  Move operator
             */
            inline fls_vector_t& operator = (fls_vector_t&& other)
            {

                fl_head_ = other.fl_head_;
                fl_tail_ = other.fl_tail_;
                is_fragmented_ = other.is_fragmented_;
                item_vector_ = other.item_vector_;

                other.clear();

                return *this;
            }

            /**
             *  [] operator
             */
            inline item_type& operator [] (u32 index) {

                return at(index);
            }
            /**
             *  [] const operator
             */
            inline const item_type& operator [] (u32 index) const {

                return at(index);
            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_passed_type>
            inline u32 insert_main_t(item_passed_type&& item, u32 insertion_index) {

                ++count_;

                if (is_fl_empty() || (item_vector_.size() == insertion_index)) {

                    item_vector_.resize(item_vector_.size() + 1);
                    is_fragmented_ = 0;

                }
                else {

                    if(insertion_index == insertable_index())
                        fl_pop();

                }

                item_vector_[insertion_index] = std::forward<item_passed_type>(item);
                item_vector_[insertion_index].is_free = 0;

                return insertion_index;
            }



        public:
            inline u32 insert(const item_type& item) {

                return insert_main_t(std::forward<const item_type&>(item), insertable_index());
            }
            inline u32 insert(item_type&& item) {

                return insert_main_t(std::forward<item_type>(item), insertable_index());
            }
            inline u32 insert(const item_type& item, u32 insertion_index) {

                return insert_main_t(std::forward<const item_type&>(item), insertion_index);
            }
            inline u32 insert(item_type&& item, u32 insertion_index) {

                return insert_main_t(std::forward<item_type>(item), insertion_index);
            }

            inline void erase(u32 index) {

                fl_push(index);

            }

            inline void fl_push(u32 index) {

                --count_;

                item_type& tail_item = item_vector_[index];
                tail_item.fl_next_index = fl_tail_;
                tail_item.is_free = 1;

                fl_tail_ = index;
                if (fl_head_ == NCPP_U32_MAX)
                    fl_head_ = fl_tail_;

                is_fragmented_ = 1;

            }

            inline void fl_pop() {

                item_type& tail_item = item_vector_[fl_tail_];
                fl_tail_ = tail_item.fl_next_index;
                if (fl_tail_ == NCPP_U32_MAX) {

                    fl_head_ = NCPP_U32_MAX;
                    is_fragmented_ = 0;

                }

            }

            inline u32 back_index() const {

                i64 i = size() - 1;
                for (; i >= 0; --i) {

                    if (item_vector_[i].is_free == 0) {

                        return i;

                    }

                }

            }

            inline void swap_items(u32 index1, u32 index2) {

                std::swap(item_vector_[index1], item_vector_[index2]);

            }

            inline item_type& at(u32 index) {

                assert(index < item_vector_.size() && "index out of range");

                return item_vector_[index];
            }
            inline const item_type& at(u32 index) const {

                assert(index < item_vector_.size() && "index out of range");

                return item_vector_[index];
            }

            inline void clear() {

                fl_head_ = NCPP_U32_MAX;
                fl_tail_ = NCPP_U32_MAX;
                is_fragmented_ = 0;
                item_vector_.clear();

            }

            inline u32 insertable_index() const {

                return (
                    fl_tail_ * (fl_tail_ != NCPP_U32_MAX)
                    + (fl_tail_ == NCPP_U32_MAX) * item_vector_.size()
                );
            }

            inline void __unsafe__clear_fl() {

                fl_head_ = NCPP_U32_MAX;
                fl_tail_ = NCPP_U32_MAX;

            }
            inline void __unsafe__resize(u32 new_size) {

                item_vector_.resize(new_size);

            }
            inline void __unsafe__set_count(u32 new_count) {

                count_ = new_count;

            }
#pragma endregion

        };

    }

}












