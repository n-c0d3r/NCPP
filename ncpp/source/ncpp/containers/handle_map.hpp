#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN handle_map_t {

#pragma region Nested Types
        public:
            struct id_type
            {

                union {

                    struct {

                        uint32_t index;
                        uint16_t generation;
                        uint16_t is_free : 1;

                    };

                    uint64_t value;

                };

                NCPP_CONSTEXPR bool operator == (const id_type& b) const { return (value == b.value); }
                NCPP_CONSTEXPR bool operator != (const id_type& b) const { return (value != b.value); }
                NCPP_CONSTEXPR bool operator < (const id_type& b) const { return (value < b.value); }
                NCPP_CONSTEXPR bool operator > (const id_type& b) const { return (value > b.value); }

            };



            struct meta_type {

                uint32_t outer_index;
                uint32_t inner_index;

                struct NCPP_DEFAULT_ALIGN {

                    item_type item;

                };

            };
#pragma endregion



#pragma region Typedefs
        public:
            using id_set_type = std::vector<id_type, allocator_t<id_type>>;
            using meta_set_type = std::vector<meta_type, allocator_t<meta_type>>;
#pragma endregion



#pragma region Properties
        private:
            uint32_t free_list_front_ = 0xFFFFFFFF;
            uint32_t free_list_back_  = 0xFFFFFFFF;

            bool is_fragmented_ = 0;

            id_set_type sparse_id_set_;
            meta_set_type meta_set_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_GETTER(size_t size()) const noexcept { return meta_set_.size(); }
            NCPP_GETTER(size_t capacity()) const noexcept { return meta_set_.capacity(); }

            NCPP_GETTER(id_set_type& sparse_id_set()) { return sparse_id_set_; }
            NCPP_GETTER(const id_set_type& sparse_id_set())const { return sparse_id_set_; }
            NCPP_GETTER(meta_set_type& meta_set()) { return meta_set_; }
            NCPP_GETTER(const meta_set_type& meta_set())const { return meta_set_; }

            NCPP_GETTER(id_type& sparse_id(uint32_t index)) { return sparse_id_set_[index]; }
            NCPP_GETTER(const id_type& sparse_id(uint32_t index))const { return sparse_id_set_[index]; }
            NCPP_GETTER(meta_type& meta(uint32_t index)) { return meta_set_[index]; }
            NCPP_GETTER(const meta_type& meta(uint32_t index))const { return meta_set_[index]; }

            NCPP_GETTER(uint32_t free_list_front()) const noexcept { return free_list_front_; }
            NCPP_GETTER(uint32_t free_list_back()) const noexcept { return free_list_back_; }

            NCPP_GETTER(bool is_fragmented()) const noexcept { return is_fragmented_; }

            NCPP_GETTER(bool is_free_list_empty()) const noexcept { return free_list_front_ == 0xFFFFFFFF; }

            NCPP_GETTER(typename meta_set_type::iterator       begin()) { return meta_set_.begin(); }
            NCPP_GETTER(typename meta_set_type::const_iterator cbegin()) const { return meta_set_.cbegin(); }
            NCPP_GETTER(typename meta_set_type::iterator       end()) { return meta_set_.end(); }
            NCPP_GETTER(typename meta_set_type::const_iterator cend()) const { return meta_set_.cend(); }

            NCPP_GETTER(meta_set_type front()) const { return meta_set_.front().item; }
            NCPP_GETTER(meta_set_type back()) const { return meta_set_.back().item; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit handle_map_t(size_t reserve_count)
            {
                sparse_id_set_.reserve(reserve_count);
                meta_set_.reserve(reserve_count);
            }
            explicit handle_map_t() :
                handle_map_t(NCPP_CONTAINERS_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {

            }
            ~handle_map_t() {

                reset();

            }

            handle_map_t(const handle_map_t& other) : 
                item_type_id_(other.item_type_id_),
                sparse_id_set_(other.sparse_id_set_),
                meta_set_(other.meta_set_),
                is_fragmented_(other.is_fragmented_),
                free_list_front_(other.free_list_front_),
                free_list_back_(other.free_list_back_)
            {



            }
            NCPP_CONSTEXPR handle_map_t& operator = (const handle_map_t& other) {

                item_type_id_ = other.item_type_id_;
                sparse_id_set_ = other.sparse_id_set_;
                meta_set_ = other.meta_set_;
                is_fragmented_ = other.is_fragmented_;
                free_list_front_ = other.free_list_front_;
                free_list_back_ = other.free_list_back_;

                return *this;
            }

            handle_map_t(handle_map_t&& other) :
                item_type_id_(std::move(other.item_type_id_)),
                sparse_id_set_(std::move(other.sparse_id_set_)),
                meta_set_(std::move(other.meta_set_)),
                is_fragmented_(std::move(other.is_fragmented_)),
                free_list_front_(std::move(other.free_list_front_)),
                free_list_back_(std::move(other.free_list_back_))
            {



            }
            NCPP_CONSTEXPR handle_map_t& operator = (handle_map_t&& other) {

                item_type_id_ = std::move(other.item_type_id_);
                sparse_id_set_ = std::move(other.sparse_id_set_);
                meta_set_ = std::move(other.meta_set_);
                is_fragmented_ = std::move(other.is_fragmented_);
                free_list_front_ = std::move(other.free_list_front_);
                free_list_back_ = std::move(other.free_list_back_);

                return *this;
            }



            NCPP_CONSTEXPR meta_type& operator[](id_type handle) {

                return at(handle);
            }

            NCPP_CONSTEXPR meta_type& operator[](uint32_t inner_index) {

                return at(inner_index);
            }
#pragma endregion



#pragma region Methods
        private:
            template<typename item_param_type>
            NCPP_CONSTEXPR id_type insert_main_t(item_param_type&& item) {

                id_type handle = { 0 };

                is_fragmented_ = true;



                if (is_free_list_empty()) {

                    id_type inner_id = {
                    
                        (uint32_t)meta_set_.size(),
                        1,
                        0
                    
                    };

                    handle = inner_id;
                    handle.index = (uint32_t)sparse_id_set_.size();

                    sparse_id_set_.push_back(inner_id);

                }
                else {

                    uint32_t outer_index = free_list_front_;
                    id_type inner_id = sparse_id_set_.at(outer_index);

                    free_list_front_ = inner_id.index;
                    if (is_free_list_empty()) {
                        free_list_back_ = free_list_front_;
                    }

                    inner_id.is_free = 0;
                    inner_id.index = (uint32_t)meta_set_.size();

                    handle = inner_id;
                    handle.index = outer_index;
                }



                meta_set_.push_back({ handle.index, (uint32_t)meta_set_.size(), std::forward<item_param_type>(item)});



                return handle;
            }
        
        
        
        public:
            NCPP_CONSTEXPR id_type insert(item_type&& item) {

                return insert_main_t(std::forward<item_type>(item));
            }
            NCPP_CONSTEXPR id_type insert(const item_type& item) {

                return insert_main_t(std::forward<const item_type&>(item));
            }

            NCPP_CONSTEXPR bool erase(id_type handle) {

                if (!is_valid(handle)) return false;

                is_fragmented_ = true;



                id_type inner_id = sparse_id_set_[handle.index];
                uint32_t inner_index = inner_id.index;

                inner_id.is_free = 1;
                ++inner_id.generation;
                inner_id.index = 0xFFFFFFFF;
                sparse_id_set_[handle.index] = inner_id;



                if (is_free_list_empty()) {

                    free_list_front_ = handle.index;
                    free_list_back_ = free_list_front_;

                }
                else {

                    sparse_id_set_[free_list_back_].index = handle.index;
                    free_list_back_ = handle.index;

                }

                if (inner_index != meta_set_.size() - 1) {

                    std::swap(meta_set_.at(inner_index), meta_set_.back());

                    sparse_id_set_[meta_set_.at(inner_index).outer_index].index = inner_index;
                    meta_set_.at(inner_index).inner_index = inner_index;

                }



                meta_set_.pop_back();



                return true;
            }

            inline void clear() {

                while(meta_set_.size() != 0)
                {

                    uint32_t outer_index = meta_set_[0].outer_index;

                    id_type handle = sparse_id_set_[outer_index];
                    handle.index = outer_index;

                    erase(handle);

                }

            }

            inline void reset() {

                sparse_id_set_.clear();
                meta_set_.clear();

            }

            NCPP_CONSTEXPR meta_type& at(id_type handle) {

                assert(handle.index < sparse_id_set_.size() && "outer index out of range");
                
                id_type inner_id = sparse_id_set_[handle.index];

                assert(handle.generation == inner_id.generation && "at called with old generation");
                assert(inner_id.index < meta_set_.size() && "inner index out of range");

                return meta_set_[inner_id.index];
            }

            NCPP_CONSTEXPR meta_type& at(uint32_t inner_index) {

                assert(inner_index < meta_set_.size() && "inner index out of range");

                return meta_set_[inner_index];
            }

            NCPP_CONSTEXPR bool is_valid(id_type handle) {

                if (handle.index >= sparse_id_set_.size()) return false;

                id_type inner_id = sparse_id_set_[handle.index];

                return (
                    (handle.generation == inner_id.generation)
                    && (inner_id.index < meta_set_.size())
                );
            }
#pragma endregion

        };

    }

}