#pragma once

/**
 *  @file ncpp/containers/fixed_vector_queue.hpp
 *  @brief Implementing fixed vector queue.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        /**
         *  A fixed_vector_queue_t is a queue storing elements inside a fixed vector
         */
        template<typename item_type, template<typename item_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN fixed_vector_queue_t final {

#pragma region Typedefs
        public:
            using item_vector_type = std::vector<item_type, allocator_t<item_type>>;
            using iterator = item_type*;
            using const_iterator = const item_type*;
#pragma endregion



#pragma region Properties
        private:
            item_vector_type item_vector_;
            size_t begin_index_;
            size_t end_index_;
            size_t capacity_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline iterator begin() { return item_vector_.data() + begin_index_ % capacity_; }
            inline const_iterator begin() const { return item_vector_.data() + begin_index_ % capacity_; }
            inline iterator end() { return item_vector_.data() + end_index_ % capacity; }
            inline const_iterator end() const { return item_vector_.data() + end_index_ % capacity_; }

            inline item_type& front() { return *begin(); }
            inline const item_type& front() const { return *begin(); }
            inline item_type& back() { return *(item_vector_.data() + (end_index_ - 1) % capacity_); }
            inline const item_type& back() const { return *(item_vector_.data() + (end_index_ - 1) % capacity_); }

            inline size_t size() const { return end_index_ - begin_index_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline explicit fixed_vector_queue_t(size_t capacity) :
                begin_index_(0),
                end_index_(0),
                capacity_(capacity)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Default constructor
             */
            inline explicit fixed_vector_queue_t() :  /** Automatically calling to the initialization constructor with the default capacity of 1024. */
                fixed_vector_queue_t(1024)
            {



            }
            /**
             *  Destructor
             */
            ~fixed_vector_queue_t() {



            }

            /**
             *  Copy constructor
             */
            inline fixed_vector_queue_t(const fixed_vector_queue_t& other) :
                fixed_vector_queue_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;

            }
            /**
             *  Copy operator
             */
            inline fixed_vector_queue_t& operator = (const fixed_vector_queue_t& other) {

                item_vector_ = other.item_vector_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline fixed_vector_queue_t(fixed_vector_queue_t&& other) :
                fixed_vector_queue_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;
                other.clear();

            }
            /**
             *  Move operator
             */
            inline fixed_vector_queue_t& operator = (fixed_vector_queue_t&& other) {

                item_vector_ = other.item_vector_;
                other.clear();

                return *this;
            }

#pragma endregion



#pragma region Methods
        private:
            template<typename item_param_type>
            inline void push_main_t(item_param_type&& item) {

                assert(size() < capacity_);

                item_vector_[end_index_ % capacity_] = std::forward<item_param_type>(item);

                ++end_index_;
            }

        
        
        public:
            /**
             *  Clear the queue by resetting the end index and the begin index.
             */
            inline void clear() {

                begin_index_ = 0;
                end_index_ = 0;

            }

            /**
             *  Push an item into the stack by move operation
             */
            inline void push(item_type&& item) {

                push_main_t(std::forward<item_type>(item));
            }
            /**
             *  Push an item into the stack by copy operation
             */
            inline void push(const item_type& item) {

                push_main_t(item);
            }
            /**
             *  Pop the front element
             */
            inline void pop() {

                assert(size() > 0);

                ++begin_index_;
                                                
            }

            /**
             *  Resizing the queue.
             */
            inline void resize(size_t size) {

                end_index_ = begin_index_ + size;

            }
#pragma endregion

        };

    }

}