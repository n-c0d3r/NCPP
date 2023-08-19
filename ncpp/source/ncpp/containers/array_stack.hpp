#pragma once

/**
 *  @file ncpp/containers/array_stack.hpp
 *  @brief Implements array stack.
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
         *  A array_stack_t is a stack storing elements inside an array
         */
        template<typename item_type__, sz capacity__>
        class NCPP_DEFAULT_ALIGNAS array_stack_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Typedefs
        public:
            using item_type = item_type__;
            using item_array_type = std::array<item_type__, capacity__>;
            using iterator = item_type__*;
            using const_iterator = const item_type__*;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Properties
        public:
            static constexpr i32 capacity() { return capacity__; };



        private:
            item_array_type item_array_;
            sz end_index_;
            sz capacity_;
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Getters and Setters
        public:
            inline iterator begin() { return item_array_.data(); }
            inline const_iterator begin() const { return item_array_.data(); }
            inline const_iterator cbegin() const { return item_array_.data(); }
            inline iterator end() { return item_array_.data() + end_index_; }
            inline const_iterator end() const { return item_array_.data() + end_index_; }
            inline const_iterator cend() const { return item_array_.data() + end_index_; }

            inline item_type__& front() { return *begin(); }
            inline const item_type__& front() const { return *begin(); }
            inline item_type__& back() { return *(item_array_.data() + (end_index_ - 1)); }
            inline const item_type__& back() const { return *(item_array_.data() + (end_index_ - 1)); }

            inline sz size() const { return end_index_; }
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Default constructor
             */
            inline explicit array_stack_t() :
                end_index_(0)
            {



            }
            /**
             *  Destructor
             */
            ~array_stack_t() {



            }

            /**
             *  Copy constructor
             */
            inline array_stack_t(const array_stack_t& other) :
                array_stack_t(other.capacity_)
            {

                item_array_ = other.item_array_;
                end_index_ = other.end_index_;

            }
            /**
             *  Copy operator
             */
            inline array_stack_t& operator = (const array_stack_t& other) {

                item_array_ = other.item_array_;
                end_index_ = other.end_index_;

                return *this;
            }

            /**
             *  Move constructor
             */
            inline array_stack_t(array_stack_t&& other) :
                array_stack_t(other.capacity_)
            {

                item_array_ = other.item_array_;
                end_index_ = other.end_index_;
                other.clear();

            }
            /**
             *  Move operator
             */
            inline array_stack_t& operator = (array_stack_t&& other) {

                item_array_ = other.item_array_;
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

                assert(size() < capacity());

                item_array_[end_index_] = std::forward<item_param_type>(item);

                ++end_index_;
            }

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////        

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
            inline bool try_pop(item_type__& out_item) {

                if (size() == 0)
                    return false;

                --end_index_;

                out_item = item_array_[end_index_];

                return true;
            }
            /**
             *  Pops the front element
             */
            inline bool try_pop() {

                if (size() == 0)
                    return false;

                --end_index_;

                return true;
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