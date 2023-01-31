#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, size_t capacity>
        class NCPP_DEFAULT_ALIGN array_queue_t {

#pragma region Typedefs
        public:
            using item_array_type = std::array<item_type, capacity>;
            using iterator = item_type*;
            using const_iterator = const item_type*;
#pragma endregion



#pragma region Properties
        private:
            item_array_type item_array_;
            size_t begin_index_;
            size_t end_index_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_CONSTEXPR iterator begin() { return item_array_.data() + begin_index_ % capacity; }
            NCPP_CONSTEXPR const_iterator begin() const { return item_array_.data() + begin_index_ % capacity; }
            NCPP_CONSTEXPR iterator end() { return item_array_.data() + end_index_ % capacity; }
            NCPP_CONSTEXPR const_iterator end() const { return item_array_.data() + end_index_ % capacity; }

            NCPP_CONSTEXPR item_type& front() { return *begin(); }
            NCPP_CONSTEXPR const item_type& front() const { return *begin(); }
            NCPP_CONSTEXPR item_type& back() { return *(item_array_.data() + (end_index_ - 1) % capacity); }
            NCPP_CONSTEXPR const item_type& back() const { return *(item_array_.data() + (end_index_ - 1) % capacity); }

            NCPP_CONSTEXPR size_t size() const { return end_index_ - begin_index_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit array_queue_t() :
                begin_index_(0),
                end_index_(0)
            {



            }
            ~array_queue_t() {



            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_param_type>
            inline bool enqueue_main_t(item_param_type&& item) {

                if (size() == capacity) return false;

                item_array_[end_index_ % capacity] = std::forward<item_param_type>(item);

                ++end_index_;

                return true;
            }

        
        
        public:
            inline void clear() {

                begin_index_ = 0;
                end_index_ = 0;

            }

            inline bool enqueue(item_type&& item) {

                return enqueue_main_t(std::forward<item_type>(item));
            }
            inline bool enqueue(const item_type& item) {

                return enqueue_main_t(item);
            }
            inline void dequeue() {

                if (size() == 0) return;

                ++begin_index_;
                                                
            }
#pragma endregion

        };

    }

}