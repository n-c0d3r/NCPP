#pragma once

/**
 *  @file ncpp/containers/fixed_vector_queue.hpp
 *  @brief Implements fixed vector queue.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/containers/handle_map.hpp>



namespace ncpp {

    namespace containers {

        /**
         *  A handle_map is a map storing items in a dense set and linking each item to an id storing in sparse set.
         */
        template<typename item_type, template<typename data_type> class allocator_t = std::allocator>
		class NCPP_DEFAULT_SET_ALIGN handle_multimap
		{

#pragma region Typedefs
		public:
            using handle_map_type = typename containers::handle_map_t<item_type, allocator_t>;
            using handle_map_vector_type = typename std::vector<handle_map_type, typename allocator_t<handle_map_type>>;
            using item_set_type = typename handle_map_type::item_set_type;
            using mai_set_type = typename handle_map_type::mai_set_type;
            using id_set_type = typename handle_map_type::id_set_type;
            using id_type = typename handle_map_type::id_type;
            using mai_type = typename handle_map_type::mai_type;
#pragma endregion



#pragma region Properties
		private:
            handle_map_vector_type vector_;
            sz map_capacity_;

            id_set_type sparse_set_;

            u32 fl_front_;
            u32 fl_back_;

            bool is_fragmented_;
#pragma endregion

#pragma region Getters and Setters
		public:
            inline handle_map_vector_type& vector() { return vector_; }
            inline const handle_map_vector_type& vector() const { return vector_; }

            inline sz map_capacity() const { return map_capacity_; }
            inline sz sparse_set_capacity() const { return sparse_set_.capacity(); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline handle_multimap(sz vector_reserve_count, sz map_reserve_count) :
                map_capacity_(map_reserve_count),
                is_fragmented_(0),
                fl_front_(0xFFFFFFFF),
                fl_back_(0xFFFFFFFF)
            {

                sparse_set_.reserve(map_reserve_count * vector_reserve_count);

            }
            /**
             *  Default constructor
             */
            inline handle_multimap() :
                handle_multimap(NCPP_DEFAULT_HANDLE_MAP_VECTOR_RESERVE_COUNT, NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {



            }
            /**
             *  Destructor
             */
            ~handle_multimap() {

                clear();

            }

            inline handle_map_type& operator[](sz index) {
                assert(index < vector_.size() && "map index out of range.");
                return vector_.at(index);
            }
            inline const handle_map_type& operator[](sz index) const {
                assert(index < vector_.size() && "map index out of range.");
                return vector_.at(index);
            }
#pragma endregion



#pragma region Methods
        public:
            inline handle_map_type& insert_new() {

                return vector_.emplace_back((sz)map_capacity_, (id_set_type&)sparse_set_, (u32&)fl_front_, (u32&)fl_back_, (bool&)is_fragmented_);
            }
            inline void erase(handle_map_type& map) {

                vector_.erase(&map);
            }

            void clear() {



            }
#pragma endregion

		};

    }

}