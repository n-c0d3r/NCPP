#pragma once

/**
 *  @file ncpp/containers/cfv_queue.hpp
 *  @brief Implements concurrent fixed vector queue.
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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/pac/spinlock.hpp>

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
         *  A cfv_queue_t is a concurrent queue storing elements inside a fixed vector
         */
        template<typename item_type__, class allocator_type__ = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<item_type__>>
        class NCPP_DEFAULT_ALIGNAS cfv_queue_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Typedefs
        public:
            using allocator_type = rebind_allocator_t<allocator_type__, item_type__>;
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
            asz begin_index_;
            asz end_index_;
            sz capacity_;

            pac::spinlock writer_lock_;
            pac::spinlock reader_lock_;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Getters and Setters
        public:
            inline iterator begin() { return item_vector_.data() + begin_index_.load(std::memory_order_acquire) % capacity_; }
            inline const_iterator begin() const { return item_vector_.data() + begin_index_.load(std::memory_order_acquire) % capacity_; }
            inline const_iterator cbegin() const { return item_vector_.data() + begin_index_.load(std::memory_order_acquire) % capacity_; }
            inline iterator end() { return item_vector_.data() + end_index_.load(std::memory_order_acquire) % capacity_; }
            inline const_iterator end() const { return item_vector_.data() + end_index_.load(std::memory_order_acquire) % capacity_; }
            inline const_iterator cend() const { return item_vector_.data() + end_index_.load(std::memory_order_acquire) % capacity_; }

            inline item_type__& front() { return *begin(); }
            inline const item_type__& front() const { return *begin(); }
            inline item_type__& back() { return *(item_vector_.data() + (end_index_.load(std::memory_order_acquire) + capacity_ - 1) % capacity_); }
            inline const item_type__& back() const { return *(item_vector_.data() + (end_index_.load(std::memory_order_acquire) + capacity_ - 1) % capacity_); }

            inline sz size() const { 
                sz end_index = end_index_.load(std::memory_order_acquire);
                sz begin_index = begin_index_.load(std::memory_order_acquire);
                return end_index - begin_index;
            }

            inline pac::spinlock& writer_lock() { return writer_lock_; }
            inline pac::spinlock& reader_lock() { return reader_lock_; }
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline explicit cfv_queue_t(sz capacity) :
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
            inline explicit cfv_queue_t(sz capacity, const allocator_type& allocator) :
                begin_index_(0),
                end_index_(0),
                item_vector_(allocator),
                capacity_(capacity)
            {

                item_vector_.reserve(capacity_);
                item_vector_.resize(capacity_);

            }
            /**
             *  Default constructor
             */
            inline explicit cfv_queue_t() :  /** Automatically calls to the initialization constructor with the default capacity of 1024. */
                cfv_queue_t(1024)
            {



            }
            /**
             *  Destructor
             */
            ~cfv_queue_t() {



            }

            /**
             *  Copy constructor
             */
            inline cfv_queue_t(const cfv_queue_t& other) :
                cfv_queue_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;

            }
            /**
             *  Copy operator
             */
            inline cfv_queue_t& operator = (const cfv_queue_t& other) {

                item_vector_ = other.item_vector_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline cfv_queue_t(cfv_queue_t&& other) :
                cfv_queue_t(other.capacity_)
            {

                item_vector_ = other.item_vector_;
                other.clear();

            }
            /**
             *  Move operator
             */
            inline cfv_queue_t& operator = (cfv_queue_t&& other) {

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

                utilities::unique_lock_t lock_guard(writer_lock_);

                item_vector_[end_index_.load(std::memory_order_acquire) % capacity_] = std::forward<item_param_type>(item);

                end_index_.fetch_add(1, std::memory_order_release);

            }

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
        
        public:
            /**
             *  Clears the queue by resetting the end index and the begin index.
             */
            inline void clear() {

                utilities::unique_lock_t lock_guard(writer_lock_);
                utilities::unique_lock_t lock_guard(reader_lock_);

                std::atomic_thread_fence(std::memory_order_release);

                begin_index_.store(0, std::memory_order_relaxed);
                end_index_.store(0, std::memory_order_relaxed);

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
             *  Tries to pop the front element
             */
            inline bool try_pop(item_type& output) {

                utilities::unique_lock_t lock_guard(reader_lock_);

                sz begin_index = begin_index_.load(std::memory_order_acquire);

                sz end_index = end_index_.load(std::memory_order_acquire);
                if (end_index <= begin_index) return false;

                begin_index_.fetch_add(1, std::memory_order_release);



                output = item_vector_[begin_index % capacity_];

                return true;
            }

            /**
             *  Tries to pop the front element
             */
            inline bool try_pop() {

                utilities::unique_lock_t lock_guard(reader_lock_);

                sz begin_index = begin_index_.load(std::memory_order_acquire);

                sz end_index = end_index_.load(std::memory_order_acquire);
                if (end_index <= begin_index) return false;

                begin_index_.fetch_add(1, std::memory_order_release);

                return true;
            }
#pragma endregion

        };

    }

}