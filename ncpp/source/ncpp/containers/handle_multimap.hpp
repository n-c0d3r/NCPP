#pragma once

/**
 *  @file ncpp/containers/handle_multimap.hpp
 *  @brief Implements handle_multimap_t.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/containers/handle_map.hpp>



namespace ncpp {

    namespace containers {

        /**
         *  A handle_multimap is a multimap storing items in dense sets and linking each item to an id storing in a sparse set.
         *  Notes:
         *      + 'fl' means  'free list'.
         *      + 'mai' means 'meta and item'.
         */
        template<typename item_type, template<typename data_type> class allocator_t = std::allocator>
		class NCPP_DEFAULT_SET_ALIGN handle_multimap_t
		{

#pragma region Typedefs
		public:
            using map_type = typename handle_map_t<item_type, allocator_t>;
            using map_set_type = typename std::vector<map_type, typename allocator_t<map_type>>;
            using id_type = typename map_type::id_type;
            using mai_type = typename map_type::mai_type;
            using item_set_type = typename std::vector<item_type, typename allocator_t<item_type>>;
            using mai_set_type = typename std::vector<mai_type, typename allocator_t<mai_type>>;
            using id_set_type = typename std::vector<id_type, typename allocator_t<id_type>>;
#pragma endregion



        public:
            friend class map_type;



#pragma region Properties
		private:
            u32 map_capacity_;

            map_set_type map_set_;

            u32 map_index_;

            id_set_type sparse_set_;

            u32 fl_front_;
            u32 fl_back_;

            bool is_fragmented_;
#pragma endregion

#pragma region Getters and Setters
		public:
            inline u32 map_capacity() const { return map_capacity_; }

            inline sz map_count() const { return map_set_.size(); }

            inline bool is_fl_empty() const { return fl_front_ == 0xFFFFFFFF; }

            inline id_set_type& sparse_set() { return sparse_set_; }
            inline const id_set_type& sparse_set() const { return sparse_set_; }

            inline u32 fl_front() const { return fl_front_; }
            inline u32 fl_back() const { return fl_back_; }

            inline bool is_fragmented() const { return is_fragmented_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline handle_multimap_t(sz map_count, sz map_reserve_count) :
                map_capacity_(map_reserve_count),
                sparse_set_(),

                fl_front_(0xFFFFFFFF),
                fl_back_(0xFFFFFFFF),

                is_fragmented_(0)
            {

                map_set_.reserve(map_count);
                sparse_set_.reserve(map_capacity_ * map_count);

                for (sz i = 0; i < map_count; ++i) {

                    insert_new();

                }

            }
            /**
             *  Default constructor
             */
            inline handle_multimap_t() :
                handle_multimap_t(NCPP_DEFAULT_HANDLE_MAP_VECTOR_RESERVE_COUNT, NCPP_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {



            }
            /**
             *  Destructor
             */
            virtual ~handle_multimap_t() {

                reset();

            }

            /**
             *  Copy Constructor
             */
            inline handle_multimap_t(const handle_multimap_t& other) :
                handle_multimap_t(other.map_count(), other.map_capacity())
            {

                for (sz i = 0; i < other.map_count(); ++i) {

                    (*this)[i] = other[i];

                }

            }
            /**
             *  Copy Operator
             */
            inline handle_multimap_t& operator = (const handle_multimap_t& other)
            {

                clear();
                for (sz i = 0; i < other.map_count(); ++i) {

                    (*this)[i] = other[i];

                }

                return *this;
            }

            /**
             *  Move Constructor
             */
            inline handle_multimap_t(handle_multimap_t&& other) :
                handle_multimap_t(other.map_count(), other.map_capacity())
            {

                for (sz i = 0; i < other.map_count(); ++i) {

                    (*this)[i] = std::move(other[i]);

                }

            }
            /**
             *  Move Operator
             */
            inline handle_multimap_t& operator = (handle_multimap_t&& other)
            {

                clear();
                for (sz i = 0; i < other.map_count(); ++i) {

                    (*this)[i] = std::move(other[i]);

                }

                return *this;
            }

            /**
             *  [] Operators
             */
            inline map_type& operator [] (sz index)
            {

                return at(index);
            }
            inline const map_type& operator [] (sz index) const
            {

                return at(index);
            }
#pragma endregion



#pragma region 
        private:
            inline map_type& insert_new() {

                map_set_.push_back(map_type(0, map_set_.size(), sparse_set_, fl_front_, fl_back_, is_fragmented_));

                map_set_.back().make_shared(*this);

                return map_set_.back();
            }



        public:
            inline map_type& at(sz index)
            {

                assert(index < map_set_.size() && "index out of range.");

                return map_set_[index];
            }
            inline const map_type& at(sz index) const
            {

                assert(index < map_set_.size() && "index out of range.");

                return map_set_[index];
            }

            inline void clear() {

                for (auto& map : map_set_) {

                    map.clear();

                }

            }
            inline void reset() {

                for (auto& map : map_set_) {

                    map.reset();

                }

            }
#pragma endregion

		};

    }

}