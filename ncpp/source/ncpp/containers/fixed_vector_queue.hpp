#pragma once

/**
 *  @file ncpp/containers/fixed_vector_queue.hpp
 *  @brief Implements fixed vector queue.
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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/.hpp>

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

    namespace containers {



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  A fixed_vector_queue_t is a queue storing elements inside a fixed vector
         */
        template<typename item_type__, class allocator_type__ = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<item_type__>>
        class NCPP_DEFAULT_ALIGNAS fixed_vector_queue_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Typedefs
        public:
            using allocator_type = allocator_type__;
            using item_type = item_type__;
            using item_vector_type = std::vector<item_type__, allocator_type>;
            using iterator = item_type__*;
            using const_iterator = const item_type__*;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Properties
        private:
            item_vector_type item_vector_;
            sz begin_index_;
            sz end_index_;
            sz capacity_;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Getters and Setters
        public:
            inline iterator begin() { return item_vector_.data() + begin_index_ % capacity_; }
            inline const_iterator begin() const { return item_vector_.data() + begin_index_ % capacity_; }
            inline const_iterator cbegin() const { return item_vector_.data() + begin_index_ % capacity_; }
            inline iterator end() { return item_vector_.data() + end_index_ % capacity; }
            inline const_iterator end() const { return item_vector_.data() + end_index_ % capacity_; }
            inline const_iterator cend() const { return item_vector_.data() + end_index_ % capacity_; }

            inline item_type__& front() { return *begin(); }
            inline const item_type__& front() const { return *begin(); }
            inline item_type__& back() { return *(item_vector_.data() + (end_index_ - 1) % capacity_); }
            inline const item_type__& back() const { return *(item_vector_.data() + (end_index_ - 1) % capacity_); }

            inline sz size() const { return end_index_ - begin_index_; }
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline explicit fixed_vector_queue_t(sz capacity) :
                begin_index_(0),
                end_index_(0),
                capacity_(capacity)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Initialization constructor with allocator
             */
            inline explicit fixed_vector_queue_t(sz capacity, const allocator_type& allocator) :
                begin_index_(0),
                end_index_(0),
                item_vector_(allocator),
                capacity_(capacity)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Initialization constructor with allocator
             */
            inline explicit fixed_vector_queue_t(const allocator_type& allocator) :
                begin_index_(0),
                end_index_(0),
                item_vector_(allocator),
                capacity_(1024)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Default constructor
             */
            inline explicit fixed_vector_queue_t() :  /** Automatically calls to the initialization constructor with the default capacity of 1024. */
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

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Methods
        private:
            template<typename item_param_type>
            inline void push_main_t(item_param_type&& item) {

                assert(size() < capacity_);

                item_vector_[end_index_ % capacity_] = std::forward<item_param_type>(item);

                ++end_index_;
            }

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
        
        public:
            /**
             *  Clears the queue by resetting the end index and the begin index.
             */
            inline void clear() {

                begin_index_ = 0;
                end_index_ = 0;

            }

            /**
             *  Pushes an item into the stack by move operation
             */
            inline void push(item_type__&& item) {

                push_main_t(std::forward<item_type__>(item));
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

                ++begin_index_;
                                                
            }

            /**
             *  Resizes the queue.
             */
            inline void resize(sz size) {

                end_index_ = begin_index_ + size;

            }
#pragma endregion

        };

    }

}