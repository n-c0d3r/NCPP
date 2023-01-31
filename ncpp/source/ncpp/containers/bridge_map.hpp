#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/containers/handle_map.hpp>
#include <ncpp/containers/handle_map_array.hpp>



namespace ncpp {

    namespace containers {

        template<typename item_type1, typename item_type2, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN bridge_map_t {

#pragma region Typedefs
        public:
            using handle_map_type1 = handle_map_t<item_type1, allocator_t>;
            using handle_map_type2 = handle_map_t<item_type2, allocator_t>;
            using id_type1 = typename handle_map_type1::id_type;
            using id_type2 = typename handle_map_type2::id_type;
            using id_set_type1 = typename handle_map_type1::id_set_type;
            using id_set_type2 = typename handle_map_type2::id_set_type;
            using meta_type1 = typename handle_map_type1::meta_type;
            using meta_type2 = typename handle_map_type2::meta_type;
            using meta_set_type1 = typename handle_map_type1::meta_set_type;
            using meta_set_type2 = typename handle_map_type2::meta_set_type;
            using index_set_type = std::vector<uint32_t>;
#pragma endregion



#pragma region Properties
        private:
            const id_set_type1& sparse_id_set1_;
            const id_set_type2& sparse_id_set2_;

            index_set_type map1_to_map2_index_set_;
            index_set_type map2_to_map1_index_set_;
#pragma endregion



#pragma region Getters and Setters
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit bridge_map_t(const id_set_type1& sparse_id_set1, const id_set_type2& sparse_id_set2) :
                sparse_id_set1_(sparse_id_set1),
                sparse_id_set2_(sparse_id_set2)
            {

                map1_to_map2_index_set_.reserve(sparse_id_set1_.capacity());
                map2_to_map1_index_set_.reserve(sparse_id_set2_.capacity());

            }
            explicit bridge_map_t(const handle_map_type1& map1, const handle_map_type2& map2) :
                bridge_map_t(map1.sparse_id_set(), map2.sparse_id_set())
            {



            }
            template<size_t map_count>
            explicit bridge_map_t(
                const handle_map_array_t<item_type1, map_count, allocator_t>& map_array1,
                const handle_map_array_t<item_type2, map_count, allocator_t>& map_array2
            ) :
                bridge_map_t(map_array1.sparse_id_set(), map_array2.sparse_id_set())
            {



            }
            ~bridge_map_t() {

                clear();

            }

            bridge_map_t(const bridge_map_t& other) :
                sparse_id_set1_(other.sparse_id_set1_),
                sparse_id_set2_(other.sparse_id_set2_),

                map1_to_map2_index_set_(other.map1_to_map2_index_set_),
                map2_to_map1_index_set_(other.map2_to_map1_index_set_)
            {



            }
            NCPP_CONSTEXPR bridge_map_t& operator = (const bridge_map_t& other) {

                sparse_id_set1_ = other.sparse_id_set1_;
                sparse_id_set2_ = other.sparse_id_set2_;

                map1_to_map2_index_set_ = other.map1_to_map2_index_set_;
                map2_to_map1_index_set_ = other.map2_to_map1_index_set_;

                return *this;
            }

            bridge_map_t(bridge_map_t&& other) :
                sparse_id_set1_(other.sparse_id_set1_),
                sparse_id_set2_(other.sparse_id_set2_),

                map1_to_map2_index_set_(std::move(other.map1_to_map2_index_set_)),
                map2_to_map1_index_set_(std::move(other.map2_to_map1_index_set_))
            {



            }
            NCPP_CONSTEXPR bridge_map_t& operator = (bridge_map_t&& other) {

                sparse_id_set1_ = other.sparse_id_set1_;
                sparse_id_set2_ = other.sparse_id_set2_;

                map1_to_map2_index_set_ = std::move(other.map1_to_map2_index_set_);
                map2_to_map1_index_set_ = std::move(other.map2_to_map1_index_set_);

                return *this;
            }
#pragma endregion



#pragma region Methods
        private:
            NCPP_CONSTEXPR id_type2 get_handle2(uint32_t outer_index) const {

                id_type2 handle = sparse_id_set2_[outer_index];
            
                handle.index = outer_index;

                return handle;
            }
            NCPP_CONSTEXPR id_type1 get_handle1(uint32_t outer_index) const {

                id_type1 handle = sparse_id_set1_[outer_index];

                handle.index = outer_index;

                return handle;
            }



        public:
            NCPP_CONSTEXPR id_type2 right(id_type1 handle1) const  {

                assert(handle1.index < map1_to_map2_index_set_.size() && "handle1.index out of range");

                return get_handle2(map1_to_map2_index_set_[handle1.index]);
            }
            NCPP_CONSTEXPR id_type1 left(id_type2 handle2) const {

                assert(handle2.index < map2_to_map1_index_set_.size() && "handle2.index out of range");

                return get_handle1(map2_to_map1_index_set_[handle2.index]);
            }

            inline void connect(const meta_type1& meta1, const meta_type2& meta2) {

                map1_to_map2_index_set_.resize(sparse_id_set1_.size());
                map2_to_map1_index_set_.resize(sparse_id_set2_.size());

                map1_to_map2_index_set_[meta1.outer_index] = meta2.outer_index;
                map2_to_map1_index_set_[meta2.outer_index] = meta1.outer_index;

            }
            inline void connect(id_type1 handle1, id_type2 handle2) {

                map1_to_map2_index_set_.resize(sparse_id_set1_.size());
                map2_to_map1_index_set_.resize(sparse_id_set2_.size());

                map1_to_map2_index_set_[handle1.index] = handle2.index;
                map2_to_map1_index_set_[handle2.index] = handle1.index;

            }
            inline void connect(uint32_t outer_index1, uint32_t outer_index2) {

                map1_to_map2_index_set_.resize(sparse_id_set1_.size());
                map2_to_map1_index_set_.resize(sparse_id_set2_.size());

                map1_to_map2_index_set_[outer_index1] = outer_index2;
                map2_to_map1_index_set_[outer_index2] = outer_index1;

            }

            inline void clear() {

                map1_to_map2_index_set_.clear();
                map2_to_map1_index_set_.clear();

            }
#pragma endregion

        };

    }

}