#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>

#include <ncpp/containers/handle_map.hpp>



namespace ncpp {

    namespace containers {

        template<typename item1_type, typename item2_type, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN bridge_map_t {

#pragma region Typedefs
        public:
            using handle_map1_type = handle_map_t<item1_type, allocator_t>;
            using handle_map2_type = handle_map_t<item2_type, allocator_t>;
            using id_type1 = typename handle_map1_type::id_type;
            using id_type2 = typename handle_map1_type::id_type;
            using index_set_type = std::vector<uint32_t>;
#pragma endregion



#pragma region Properties
        private:
            const handle_map1_type& map1_;
            const handle_map2_type& map2_;

            index_set_type map1_to_map2_index_set_;
            index_set_type map2_to_map1_index_set_;
#pragma endregion



#pragma region Getters and Setters
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit bridge_map_t(const handle_map1_type& map1, const handle_map2_type& map2) :
                map1_(map1),
                map2_(map2)
            {

                map1_to_map2_index_set_.reserve(map1.capacity());
                map2_to_map1_index_set_.reserve(map2.capacity());

            }
            ~bridge_map_t() {

                clear();

            }



            bridge_map_t(const bridge_map_t& other) :
                map1_(other.map1_),
                map2_(other.map2_),

                map1_to_map2_index_set_(other.map1_to_map2_index_set_),
                map2_to_map1_index_set_(other.map2_to_map1_index_set_)
            {



            }
            NCPP_CONSTEXPR bridge_map_t& operator = (const bridge_map_t& other) {

                map1_ = other.map1_;
                map2_ = other.map2_;

                map1_to_map2_index_set_ = other.map1_to_map2_index_set_;
                map2_to_map1_index_set_ = other.map2_to_map1_index_set_;

                return *this;
            }

            bridge_map_t(bridge_map_t&& other) :
                map1_(other.map1_),
                map2_(other.map2_),

                map1_to_map2_index_set_(std::move(other.map1_to_map2_index_set_)),
                map2_to_map1_index_set_(std::move(other.map2_to_map1_index_set_))
            {



            }
            NCPP_CONSTEXPR bridge_map_t& operator = (bridge_map_t&& other) {

                map1_ = other.map1_;
                map2_ = other.map2_;

                map1_to_map2_index_set_ = std::move(other.map1_to_map2_index_set_);
                map2_to_map1_index_set_ = std::move(other.map2_to_map1_index_set_);

                return *this;
            }
#pragma endregion



#pragma region Methods
        private:
            NCPP_CONSTEXPR id_type2 get_handle2(uint32_t outer_index) const {

                id_type2 handle = map2_.sparse_id_set()[outer_index];
            
                handle.index = outer_index;

                return handle;
            }
            NCPP_CONSTEXPR id_type1 get_handle1(uint32_t outer_index) const {

                id_type1 handle = map1_.sparse_id_set()[outer_index];

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

            inline void connect(id_type1 handle1, id_type2 handle2) {

                map1_to_map2_index_set_.resize(map1_.sparse_id_set().size());
                map2_to_map1_index_set_.resize(map2_.sparse_id_set().size());

                map1_to_map2_index_set_[handle1.index] = handle2.index;
                map2_to_map1_index_set_[handle2.index] = handle1.index;

            }

            inline void clear() {

                map1_to_map2_index_set_.clear();
                map2_to_map1_index_set_.clear();

            }
#pragma endregion

        };

    }

}