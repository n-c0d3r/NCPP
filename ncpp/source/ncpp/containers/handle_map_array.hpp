#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/containers/handle_map.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type, size_t count, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN handle_map_array_t {

#pragma region Typedefs
        public:
            using handle_map_type = typename handle_map_t<item_type, allocator_t, count>;
            using handle_map_array_type = typename std::array<handle_map_type, count>;
            using id_type = typename handle_map_type::id_type;
            using meta_type = typename handle_map_type::meta_type;
            using id_set_type = typename handle_map_type::id_set_type;
            using meta_set_type = typename handle_map_type::meta_set_type;
#pragma endregion



#pragma region Properties
        private:
            uint32_t free_list_front_;
            uint32_t free_list_back_;

            bool is_fragmented_;

            id_set_type sparse_id_set_;

            handle_map_array_type array_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_CONSTEXPR uint32_t free_list_front() const noexcept { return free_list_front_; }
            NCPP_CONSTEXPR uint32_t free_list_back() const noexcept { return free_list_back_; }

            NCPP_CONSTEXPR bool is_fragmented() const noexcept { return is_fragmented_; }

            NCPP_CONSTEXPR id_set_type& sparse_id_set() { return sparse_id_set_; }
            NCPP_CONSTEXPR const id_set_type& sparse_id_set()const { return sparse_id_set_; }
            NCPP_CONSTEXPR meta_set_type& meta_set() { return meta_set_; }
            NCPP_CONSTEXPR const meta_set_type& meta_set() const { return meta_set_; }

            NCPP_CONSTEXPR size_t get_count() const { return count; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit handle_map_array_t(size_t reserve_count) :
                free_list_front_(0xFFFFFFFF),

                free_list_back_(0xFFFFFFFF),

                is_fragmented_(0),

                sparse_id_set_()
            {

                sparse_id_set_.reserve(reserve_count);

                for (size_t i = 0; i < count; ++i) {

                    array_[i].~handle_map_type();
                    new(&array_[i]) handle_map_type(i, reserve_count, sparse_id_set_, free_list_front_, free_list_back_, is_fragmented_);

                }

            }
            explicit handle_map_array_t() :
                handle_map_array_t(NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {

            }
            ~handle_map_array_t() {

                reset();

            }

            handle_map_array_t(const handle_map_array_t& other) :
                handle_map_array_t()
            {

                copy_from(other);

            }
            NCPP_CONSTEXPR handle_map_array_t& operator = (const handle_map_array_t& other) {

                copy_from(other);

                return *this;
            }

            handle_map_array_t(handle_map_array_t&& other) :
                handle_map_array_t()
            {

                move_from(std::forward<handle_map_array_t>(other));

            }
            NCPP_CONSTEXPR handle_map_array_t& operator = (handle_map_array_t&& other) {

                move_from(std::forward<handle_map_array_t>(other));

                return *this;
            }



            NCPP_CONSTEXPR handle_map_type& operator [] (uint32_t index) {

                return at(index);
            }
            NCPP_CONSTEXPR const handle_map_type& operator [] (uint32_t index) const {

                return at(index);
            }
#pragma endregion



#pragma region Methods
        public:
            inline void clear() {

                free_list_front_ = 0xFFFFFFFF;
                free_list_back_ = 0xFFFFFFFF;
                is_fragmented_ = 0;

                for (size_t i = 0; i < count; ++i) {

                    array_[i].clear();

                }

                sparse_id_set_.clear();

            }
            inline void reset() {

                free_list_front_ = 0xFFFFFFFF;
                free_list_back_ = 0xFFFFFFFF;
                is_fragmented_ = 0;

                sparse_id_set_.clear();

                for (size_t i = 0; i < count; ++i) {

                    array_[i].reset();

                }

            }

            NCPP_CONSTEXPR handle_map_type& at(uint32_t index) {

                assert(index < count && "index out of range");

                return array_.at(index);
            }
            NCPP_CONSTEXPR const handle_map_type& at(uint32_t index) const {

                assert(index < count && "index out of range");

                return array_.at(index);
            }

            inline void transfer(uint16_t dst_map_index, uint16_t src_map_index, id_type handle) {

                transfer(at(dst_map_index), at(src_map_index), handle);
            }
            inline void transfer(handle_map_type& dst_map, handle_map_type& src_map, id_type handle) {

                dst_map.shared_transfer(src_map, handle);

            }

            inline void copy_from(const handle_map_array_t& other) {

                reset();

                sparse_id_set_.reserve(other.sparse_id_set_.capacity());

                for (auto inner_id : other.sparse_id_set()) {

                    auto other_map = other[inner_id.map_index];
                    meta_type& meta = other_map[inner_id.index];

                    array_[inner_id.map_index].insert(meta.item);

                }

            }

            inline void move_from(handle_map_array_t&& other) {

                sparse_id_set_.reserve(other.sparse_id_set_.capacity());

                sparse_id_set_ = std::move(other.sparse_id_set_);

                for (size_t i = 0; i < count; ++i) {

                    array_[i].meta_set() = std::move(other.array_[i].meta_set());
                    array_[i].sparse_id_set() = std::move(other.array_[i].sparse_id_set());

                }

                other.reset();

            }
#pragma endregion

        };

    }

}