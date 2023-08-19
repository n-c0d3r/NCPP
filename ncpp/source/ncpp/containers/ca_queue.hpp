#pragma once

/**
 *  @file ncpp/containers/ca_queue.hpp
 *  @brief Implements concurrent array queue.
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
         *  A ca_queue_t is a concurrent queue storing elements inside an array
         */
        template<typename item_type__, sz capacity__>
        class NCPP_DEFAULT_ALIGNAS ca_queue_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Typedefs
        public:
            using item_type = item_type__;
            using item_array_type = std::array<item_type__, capacity__>;
            using iterator = item_type__*;
            using const_iterator = const item_type__*;

            template<sz new_capacity__>
            using rebind_capacity_t = ca_queue_t<item_type__, new_capacity__>;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Properties
        public:
            static constexpr i32 capacity() { return capacity__; };



        private:
            item_array_type item_array_;
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
            inline iterator begin() { return item_array_.data() + begin_index_.load(std::memory_order_acquire) % capacity(); }
            inline const_iterator begin() const { return item_array_.data() + begin_index_.load(std::memory_order_acquire) % capacity(); }
            inline const_iterator cbegin() const { return item_array_.data() + begin_index_.load(std::memory_order_acquire) % capacity(); }
            inline iterator end() { return item_array_.data() + end_index_.load(std::memory_order_acquire) % capacity(); }
            inline const_iterator end() const { return item_array_.data() + end_index_.load(std::memory_order_acquire) % capacity(); }
            inline const_iterator cend() const { return item_array_.data() + end_index_.load(std::memory_order_acquire) % capacity(); }

            inline item_type__& front() { return *begin(); }
            inline const item_type__& front() const { return *begin(); }
            inline item_type__& back() { return *(item_array_.data() + (end_index_.load(std::memory_order_acquire) + capacity() - 1) % capacity()); }
            inline const item_type__& back() const { return *(item_array_.data() + (end_index_.load(std::memory_order_acquire) + capacity() - 1) % capacity()); }

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
            inline explicit ca_queue_t() :
                begin_index_(0),
                end_index_(0)
            {



            }
            /**
             *  Destructor
             */
            ~ca_queue_t() {



            }

            /**
             *  Copy constructor
             */
            inline ca_queue_t(const ca_queue_t& other) :
                ca_queue_t(other.capacity_)
            {

                item_array_ = other.item_array_;
                begin_index_ = other.begin_index_;
                end_index_ = other.end_index_;

            }
            /**
             *  Copy operator
             */
            inline ca_queue_t& operator = (const ca_queue_t& other) {

                item_array_ = other.item_array_;
                begin_index_ = other.begin_index_;
                end_index_ = other.end_index_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline ca_queue_t(ca_queue_t&& other) :
                ca_queue_t(other.capacity_)
            {

                item_array_ = other.item_array_;
                begin_index_ = other.begin_index_;
                end_index_ = other.end_index_;
                other.clear();

            }
            /**
             *  Move operator
             */
            inline ca_queue_t& operator = (ca_queue_t&& other) {

                item_array_ = other.item_array_;
                begin_index_ = other.begin_index_;
                end_index_ = other.end_index_;
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

                item_array_[end_index_.load(std::memory_order_acquire) % capacity] = std::forward<item_param_type>(item);

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



                output = item_array_[begin_index % capacity()];

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