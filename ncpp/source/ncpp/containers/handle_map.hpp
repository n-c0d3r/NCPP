#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, size_t count, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN handle_map_array_t;



        template<typename item_type, template<typename data_type> class allocator_t = std::allocator, size_t map_count = 1>
        class NCPP_DEFAULT_ALIGN handle_map_t {

#pragma region Nested Types
        public:
            friend class handle_map_array_t<item_type, map_count, allocator_t>;
#pragma endregion



#pragma region Nested Types
        public:
            struct id_type
            {

                union {

                    struct {

                        uint32_t index;
                        uint16_t generation;
                        uint16_t map_index : 15;
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
            uint32_t unique_free_list_front_;
            uint32_t& free_list_front_;

            uint32_t unique_free_list_back_;
            uint32_t& free_list_back_;

            bool unique_is_fragmented_;
            bool& is_fragmented_;

            id_set_type unique_sparse_id_set_;
            id_set_type& sparse_id_set_;

            meta_set_type meta_set_;

            bool is_shared_ = 0;

            uint16_t map_index_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_CONSTEXPR size_t size() const noexcept { return meta_set_.size(); }
            NCPP_CONSTEXPR size_t capacity() const noexcept { return meta_set_.capacity(); }

            NCPP_CONSTEXPR id_set_type& sparse_id_set() { return sparse_id_set_; }
            NCPP_CONSTEXPR const id_set_type& sparse_id_set()const { return sparse_id_set_; }
            NCPP_CONSTEXPR meta_set_type& meta_set() { return meta_set_; }
            NCPP_CONSTEXPR const meta_set_type& meta_set()const { return meta_set_; }

            NCPP_CONSTEXPR id_type& sparse_id(uint32_t index) { return sparse_id_set_[index]; }
            NCPP_CONSTEXPR const id_type& sparse_id(uint32_t index)const { return sparse_id_set_[index]; }
            NCPP_CONSTEXPR meta_type& meta(uint32_t index) { return meta_set_[index]; }
            NCPP_CONSTEXPR const meta_type& meta(uint32_t index) const { return meta_set_[index]; }

            NCPP_CONSTEXPR uint32_t free_list_front() const noexcept { return free_list_front_; }
            NCPP_CONSTEXPR uint32_t free_list_back() const noexcept { return free_list_back_; }

            NCPP_CONSTEXPR bool is_fragmented() const noexcept { return is_fragmented_; }

            NCPP_CONSTEXPR bool is_free_list_empty() const noexcept { return free_list_front_ == 0xFFFFFFFF; }

            NCPP_CONSTEXPR typename meta_set_type::iterator       begin() { return meta_set_.begin(); }
            NCPP_CONSTEXPR typename meta_set_type::const_iterator begin() const { return meta_set_.cbegin(); }
            NCPP_CONSTEXPR typename meta_set_type::iterator       end() { return meta_set_.end(); }
            NCPP_CONSTEXPR typename meta_set_type::const_iterator end() const { return meta_set_.cend(); }

            NCPP_CONSTEXPR meta_set_type front() const { return meta_set_.front().item; }
            NCPP_CONSTEXPR meta_set_type back() const { return meta_set_.back().item; }

            NCPP_CONSTEXPR bool is_shared() const { return is_shared_; }

            NCPP_CONSTEXPR uint16_t map_index() const { return map_index_; }

            NCPP_CONSTEXPR id_type get_handle(const meta_type& meta) const { 
                id_type handle = sparse_id_set_.at(meta.outer_index);
                handle.index = meta.outer_index;
                return handle;
            }
            NCPP_CONSTEXPR id_type get_handle(uint32_t inner_index) const {
                meta_type meta = meta_set_.at(inner_index);

                return get_handle(meta);
            }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit handle_map_t(size_t reserve_count) :
                is_shared_(0),

                unique_free_list_front_(0xFFFFFFFF),
                free_list_front_(unique_free_list_front_),

                unique_free_list_back_(0xFFFFFFFF),
                free_list_back_(unique_free_list_back_),

                unique_sparse_id_set_(),
                sparse_id_set_(unique_sparse_id_set_),

                unique_is_fragmented_(0),
                is_fragmented_(unique_is_fragmented_),

                map_index_(0)
            {
                sparse_id_set_.reserve(reserve_count);
                meta_set_.reserve(reserve_count);
            }
            explicit handle_map_t() :
                handle_map_t(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {

            }
            explicit handle_map_t(uint16_t map_index, size_t reserve_count, id_set_type& shared_sparse_id_set, uint32_t& shared_free_list_front, uint32_t shared_free_list_back, bool& shared_is_fragmented) :
                is_shared_(1),

                unique_free_list_front_(0xFFFFFFFF),
                free_list_front_(shared_free_list_front),

                unique_free_list_back_(0xFFFFFFFF),
                free_list_back_(shared_free_list_back),

                unique_sparse_id_set_(),
                sparse_id_set_(shared_sparse_id_set),

                unique_is_fragmented_(0),
                is_fragmented_(shared_is_fragmented),

                map_index_(map_index)
            {

                meta_set_.reserve(reserve_count);

            }
            ~handle_map_t() {

                if (is_shared_)
                    clear();
                else
                    reset();

            }

            handle_map_t(const handle_map_t& other) : 
                handle_map_t()
            {

                if (is_shared_)
                    clear();
                else
                    reset();

                for (const auto& meta : other) {

                    insert(meta.item);

                }

            }
            NCPP_CONSTEXPR handle_map_t& operator = (const handle_map_t& other) {

                if (is_shared_)
                    clear();
                else
                    reset();

                for (const auto& meta : other) {

                    insert(meta.item);

                }

                return *this;
            }

            handle_map_t(handle_map_t&& other) :
                handle_map_t()
            {

                if (is_shared_)
                    clear();
                else
                    reset();

                uint32_t i = 0;
                while (i != other.size()) {

                    insert(other[i].item);
                    other.erase(other[i]);

                }

            }
            NCPP_CONSTEXPR handle_map_t& operator = (handle_map_t&& other) {

                if (is_shared_)
                    clear();
                else
                    reset();

                uint32_t i = 0;
                while (i != other.size()) {

                    insert(other[i].item);
                    other.erase(other[i]);

                }

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
                        map_index_,
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

            NCPP_CONSTEXPR bool erase(const meta_type& meta) {
                return erase(meta.outer_index);
            }
            NCPP_CONSTEXPR bool erase(id_type handle) {

                if (!is_valid(handle)) return false;

                return erase(handle.index);
            }
            NCPP_CONSTEXPR bool erase(uint32_t outer_index) {

                is_fragmented_ = true;



                id_type inner_id = sparse_id_set_[outer_index];
                uint32_t inner_index = inner_id.index;

                inner_id.is_free = 1;
                ++inner_id.generation;
                inner_id.index = 0xFFFFFFFF;
                sparse_id_set_[outer_index] = inner_id;



                if (is_free_list_empty()) {

                    free_list_front_ = outer_index;
                    free_list_back_ = free_list_front_;

                }
                else {

                    sparse_id_set_[free_list_back_].index = outer_index;
                    free_list_back_ = outer_index;

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

                if(!is_shared_)
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
            NCPP_CONSTEXPR const meta_type& at(id_type handle) const {

                assert(handle.index < sparse_id_set_.size() && "outer index out of range");

                id_type inner_id = sparse_id_set_.at(handle.index);

                assert(handle.generation == inner_id.generation && "at called with old generation");
                assert(inner_id.index < meta_set_.size() && "inner index out of range");

                return meta_set_.at(inner_id.index);
            }

            NCPP_CONSTEXPR meta_type& at(uint32_t inner_index) {

                assert(inner_index < meta_set_.size() && "inner index out of range");

                return meta_set_[inner_index];
            }
            NCPP_CONSTEXPR const meta_type& at(uint32_t inner_index) const {

                assert(inner_index < meta_set_.size() && "inner index out of range");

                return meta_set_.at(inner_index);
            }

            NCPP_CONSTEXPR bool is_valid(id_type handle) {

                if (handle.index >= sparse_id_set_.size()) return false;

                id_type inner_id = sparse_id_set_[handle.index];

                return (
                    (handle.generation == inner_id.generation)
                    && (inner_id.index < meta_set_.size())
                );
            }
            NCPP_CONSTEXPR bool is_valid(id_type handle) const {

                if (handle.index >= sparse_id_set_.size()) return false;

                id_type inner_id = sparse_id_set_.at(handle.index);

                return (
                    (handle.generation == inner_id.generation)
                    && (inner_id.index < meta_set_.size())
                );
            }

            inline void shared_transfer(handle_map_t& src, id_type handle) {

                assert(is_shared_ && "shared transfer not working in non-shared map");
                assert(handle.map_index == src.map_index_ && "invalid handle");
                assert(this != &src && "cant shared transfer in the same map");
                
                meta_set_.push_back(std::move(src.at(handle)));
                meta_type& meta = meta_set_.back();
                
                uint32_t outer_index = handle.index;
                
                id_type inner_id = sparse_id_set_[outer_index];

                if (inner_id.index != src.meta_set_.size() - 1) {

                    std::swap(src.meta_set_[inner_id.index], src.meta_set_.back());
                    sparse_id_set_[src.meta_set_.back().outer_index].index = inner_id.index;
                    src.meta_set_.at(inner_id.index).inner_index = inner_id.index;

                }

                inner_id.map_index = map_index_;
                inner_id.index = meta_set_.size() - 1;

                sparse_id_set_[outer_index] = inner_id;


            }
#pragma endregion

        };

    }

}