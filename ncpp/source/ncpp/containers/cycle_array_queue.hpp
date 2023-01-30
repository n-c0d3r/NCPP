#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>

#include <ncpp/containers/handle_map.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, size_t capacity>
        class NCPP_DEFAULT_ALIGN cycle_array_queue_t {

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
            size_t size_;
#pragma endregion



#pragma region Getters and Setters
            NCPP_GETTER(iterator begin()) { return item_array_.data() + begin_; }
            NCPP_GETTER(const_iterator cbegin()) const { return item_array_.data() + begin_; }
            NCPP_GETTER(iterator end()) { return item_array_.data() + end_; }
            NCPP_GETTER(const_iterator cend()) const { return item_array_.data() + end_; }

            NCPP_GETTER(item_type& front()) { return *begin(); }
            NCPP_GETTER(const item_type& front()) const { return *cbegin(); }
            NCPP_GETTER(item_type& back()) { return *end(); }
            NCPP_GETTER(const item_type& back()) const { return *cend(); }

            NCPP_GETTER(size_t size()) const { return size_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit cycle_array_queue_t() :
                begin_index_(0),
                end_index_(0),

                size_(0)
            {



            }
            ~cycle_array_queue_t() {



            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_param_type>
            inline bool enqueue_main_t(item_param_type&& item) {

                if (size_ == capacity) return false;



                if (end_index_ > capacity) {

                    end_index_ = 0;

                }



                item_array_[end_index_] = std::forward<item_param_type>(item);



                ++end_index_;
                ++size_;



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
#pragma endregion

        };

    }

}