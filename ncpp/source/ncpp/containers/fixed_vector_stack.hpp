#pragma once

/**
 *  @file ncpp/containers/fixed_vector_stack.hpp
 *  @brief Implements fixed vector stack.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        /**
         *  A fixed_vector_stack_t is a stack storing elements inside a fixed vector 
         */
        template<typename item_type__, template<typename item_type__> class allocator_t__ = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN fixed_vector_stack_t {

#pragma region Typedefs
        public:
            using item_type = item_type__;
            using item_vector_type = std::vector<item_type__, allocator_t__<item_type__>>;
            using iterator = item_type__*;
            using const_iterator = const item_type__*;
#pragma endregion



#pragma region Properties
        private:
            item_vector_type item_vector_;
            sz end_index_;
            sz capacity_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline iterator begin() { return item_vector_.data(); }
            inline const_iterator begin() const { return item_vector_.data(); }
            inline const_iterator cbegin() const { return item_vector_.data(); }
            inline iterator end() { return item_vector_.data() + end_index_; }
            inline const_iterator end() const { return item_vector_.data() + end_index_; }
            inline const_iterator cend() const { return item_vector_.data() + end_index_; }

            inline item_type__& front() { return *begin(); }
            inline const item_type__& front() const { return *begin(); }
            inline item_type__& back() { return *(item_vector_.data() + (end_index_ - 1)); }
            inline const item_type__& back() const { return *(item_vector_.data() + (end_index_ - 1)); }

            inline sz size() const { return end_index_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline explicit fixed_vector_stack_t(sz capacity) :
                end_index_(0),
                capacity_(capacity)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Default constructor
             */
            inline explicit fixed_vector_stack_t() : /** Automatically calls to the initialization constructor with the default capacity of 1024. */
                fixed_vector_stack_t(1024)
            {



            }
            /**
             *  Destructor
             */
            ~fixed_vector_stack_t() {



            }

            /**
             *  Copy constructor
             */
            inline fixed_vector_stack_t(const fixed_vector_stack_t& other) :
                fixed_vector_stack_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;

            }
            /**
             *  Copy operator
             */
            inline fixed_vector_stack_t& operator = (const fixed_vector_stack_t& other) {

                item_vector_ = other.item_vector_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline fixed_vector_stack_t(fixed_vector_stack_t&& other) :
                fixed_vector_stack_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;enqueue
                other.clear();

            }
            /**
             *  Move operator
             */
            inline fixed_vector_stack_t& operator = (fixed_vector_stack_t&& other) {

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

                item_vector_[end_index_] = std::forward<item_param_type>(item);

                ++end_index_;
            }

        
        
        public:
            /**
             *  Clears the stack by resetting the end index
             */
            inline void clear() {

                end_index_ = 0;

            }

            /**
             *  Pushes an item into the stack by move operation
             */
            inline void push(item_type__&& item) {

                push_main_t(std::forward<const item_type__>(item));
            }
            /**
             *  Pushes an item into the stack by copy operation
             */
            inline void push(const item_type__& item) {

                push_main_t(item);
            }
            /**
             *  Pops the front element
             */
            inline void pop() {

                assert(size() > 0);

                --end_index_;
                                                
            }

            /**
             *  Resizes the stack.
             */
            inline void resize(sz size) {

                end_index_ = size;

            }
#pragma endregion

        };

    }

}