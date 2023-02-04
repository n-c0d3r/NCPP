#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/.hpp>



namespace ncpp {

	namespace ecs {

		/**
		 *  A sdm buffer ('sdm' = 'shadowed data map') is a handle map which each item is std::pair<data_type, data_type> (the first is main part, the second is shadow part).
		 *	
		 */
		template<typename data_type, template<typename data_type> class allocator_t = std::allocator>
		class NCPP_DEFAULT_SET_ALIGN sd_buffer_t : 
			public containers::handle_map_t<std::pair<data_type, data_type>, allocator_t>
		{

#pragma region Typedefs
		public:
			using item_type = typename std::pair<data_type, data_type>;
            using handle_map_type = typename containers::handle_map_t<std::pair<data_type, data_type>, allocator_t>;
            using item_set_type = typename handle_map_type::item_set_type;
            using mai_set_type = typename handle_map_type::mai_set_type;
            using id_set_type = typename handle_map_type::id_set_type;
            using id_type = typename handle_map_type::id_type;
            using mai_type = typename handle_map_type::mai_type;
#pragma endregion



#pragma region Properties
		private:

#pragma endregion

#pragma region Getters and Setters
		public:

#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline sd_buffer_t(sz reserve_count) :
                handle_map_type(reserve_count)
            {



            }
            /**
             *  Default constructor
             */
            inline sd_buffer_t() :
                handle_map_type()
            {



            }
            /**
             *  Destructor
             */
            ~sd_buffer_t() {



            }

            /**
             *  Copy Constructor
             */
            inline sd_buffer_t(const sd_buffer_t& other) :
                handle_map_type(other)
            {



            }
            /**
             *  Copy Operator
             */
            inline sd_buffer_t& operator = (const sd_buffer_t& other)
            {

                ((handle_map_type&)*this) = other;

                return *this;
            }

            /**
             *  Move Constructor
             */
            inline sd_buffer_t(sd_buffer_t&& other) :
                handle_map_type(std::forward<sd_buffer_t>(other))
            {



            }
            /**
             *  Move Operator
             */
            inline sd_buffer_t& operator = (sd_buffer_t&& other)
            {

                ((handle_map_type&)*this) = std::forward<sd_buffer_t>(other);

                return *this;
            }
#pragma endregion



#pragma region Methods
        private:



        public:
            inline id_type insert(data_type& data) {

                item_type item = std::make_pair(std::forward<data_type&>(data), std::forward<data_type&>(data));

                return handle_map_type::insert(item);
            }
            inline id_type insert(data_type&& data) {

                item_type item = std::make_pair(std::forward<data_type&>(data), std::forward<data_type>(data));

                return handle_map_type::insert(std::move(item));
            }

            inline void update_shadow() {

                for (auto& mai : *this) {

                    mai->second = mai->first;

                }

            }
            inline void update_main() {

                for (auto& mai : *this) {

                    mai->first = mai->second;

                }

            }

            inline void clear() {

                handle_map_type::clear();

            }
            inline void reset() {

                handle_map_type::reset();

            }
#pragma endregion

		};

	}

}