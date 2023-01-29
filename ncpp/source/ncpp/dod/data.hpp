#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>



namespace ncpp {

    namespace dod {

        template<template<typename data_type> class allocator_t = std::allocator, typename... column_types>
        class NCPP_DEFAULT_ALIGN data_t {

#pragma region Static Constants
        public:
            static constexpr const size_t column_count = sizeof...(column_types);
#pragma endregion



#pragma region Typedefs
        public:
            template<size_t column_index>
            using item_type_t = typename tmp_helper::nth_template_arg_t<column_index, column_types...>::type;

            template<size_t column_index>
            using item_set_type_t = typename std::vector<typename item_type_t<column_index>, class allocator_t<typename item_type_t<column_index>>>;

            template<size_t column_index>
            using item_map_type_t = typename containers::handle_map_t<typename item_type_t<column_index>, allocator_t>;

            template<size_t column_index>
            using column_type_t = typename item_map_type_t<column_index>;

            template<size_t column_index>
            using meta_type_t = typename column_type_t<column_index>::meta_type;
            template<size_t column_index>
            using meta_set_type_t = typename column_type_t<column_index>::meta_set_type;

            template<size_t column_index>
            using id_type_t = typename column_type_t<column_index>::id_type;
            template<size_t column_index>
            using id_set_type_t = typename column_type_t<column_index>::id_set_type;

            using row_type = typename std::tuple<column_types...>;
            using row_id_type = typename std::tuple<typename containers::handle_map_t<column_types, allocator_t>::id_type...>;
            using map_tuple_type = typename std::tuple<typename containers::handle_map_t<column_types, allocator_t>...>;
#pragma endregion



#pragma region Properties
        private:
            map_tuple_type map_tuple_;
#pragma endregion



#pragma region Getters and Setters
        public:
            map_tuple_type& map_tuple() { return map_tuple_; }
            const map_tuple_type& map_tuple() const { return map_tuple_; }

            template<size_t index>
            NCPP_GETTER(typename column_type_t<index>& column_t()) { return std::get<typename column_type_t<index>>(map_tuple_); }
            template<size_t index>
            NCPP_GETTER(typename const column_type_t<index>& column_t()) const { return std::get<typename column_type_t<index>>(map_tuple_); }

            template<size_t index>
            NCPP_GETTER(typename item_set_type_t<index>& item_set_t()) { return column_t<index>().item_set(); }
            template<size_t index>
            NCPP_GETTER(typename const item_set_type_t<index>& item_set_t()) const { return column_t<index>().item_set(); }

            template<size_t index>
            NCPP_GETTER(typename meta_set_type_t<index>& meta_set_t()) { return column_t<index>().meta_set(); }
            template<size_t index>
            NCPP_GETTER(typename const meta_set_type_t<index>& meta_set_t()) const { return column_t<index>().meta_set(); }

            template<size_t index>
            NCPP_GETTER(typename id_set_type_t<index>& sparse_id_set_t()) { return column_t<index>().sparse_id_set(); }
            template<size_t index>
            NCPP_GETTER(typename const id_set_type_t<index>& sparse_id_set_t()) const { return column_t<index>().sparse_id_set(); }

            template<size_t index>
            NCPP_GETTER(typename meta_type_t<index>& meta_t(uint32_t i)) { return meta_set_t<index>().at(i); }
            template<size_t index>
            NCPP_GETTER(typename const meta_type_t<index>& meta_t(uint32_t i))const { return meta_set_t<index>().at(i); }

            template<size_t index>
            NCPP_GETTER(typename id_type_t<index>& sparse_id_t(uint32_t i)) { return sparse_id_set_t<index>().at(i); }
            template<size_t index>
            NCPP_GETTER(typename const id_type_t<index>& sparse_id_t(uint32_t i))const { return sparse_id_set_t<index>().at(i); }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            explicit data_t(size_t reserve_count) :
                map_tuple_()
            {

                tmp_helper::templated_for_t<construct_map_tuple_t, 0, column_count>(map_tuple_, reserve_count);

            }
            explicit data_t() :
                data_t(NCPP_CONTAINERS_DEFAULT_HANDLE_MAP_RESERVE_COUNT)
            {



            }
            ~data_t() {

                reset();

            }
#pragma endregion



#pragma region Methods
        private:
            NCPP_LOOP_FUNCTION_T(
                construct_map_tuple_t, (map_tuple_type& map_tuple, size_t reserve_count),
                {

                    using map_type = typename data_t::item_map_type_t<index>;

                    std::get<map_type>(map_tuple) = std::move(map_type(index, reserve_count));

                }
            );

            NCPP_LOOP_FUNCTION_T(
                clear_map_tuple_t, (map_tuple_type& map_tuple),
                {

                    using map_type = typename data_t::item_map_type_t<index>;

                    std::get<map_type>(map_tuple).clear();

                }
            );

            NCPP_LOOP_FUNCTION_T(
                reset_map_tuple_t, (map_tuple_type& map_tuple),
                {

                    using map_type = typename data_t::item_map_type_t<index>;

                    std::get<map_type>(map_tuple).reset();

                }
            );

            NCPP_LOOP_FUNCTION_T(
                emplace_row_copy_t, (map_tuple_type& map_tuple, const row_type& row, row_id_type& row_handle),
                {

                    using map_type = typename data_t::item_map_type_t<index>;
                    using item_type = typename data_t::item_type_t<index>;
                    using id_type = typename data_t::id_type_t<index>;

                    std::get<id_type>(row_handle) = std::get<map_type>(map_tuple).insert(std::get<item_type>(row));

                }
            );
            NCPP_LOOP_FUNCTION_T(
                emplace_row_move_t, (map_tuple_type& map_tuple, const row_type& row, row_id_type& row_handle),
                {

                    using map_type = typename data_t::item_map_type_t<index>;
                    using item_type = typename data_t::item_type_t<index>;
                    using id_type = typename data_t::id_type_t<index>;

                    std::get<id_type>(row_handle) = std::get<map_type>(map_tuple).insert(std::move(std::get<item_type>(row)));

                }
            );

            NCPP_LOOP_FUNCTION_T(
                erase_row_t, (map_tuple_type& map_tuple, row_id_type& row_handle),
                {

                    using map_type = typename data_t::item_map_type_t<index>;
                    using id_type = typename data_t::id_type_t<index>;

                    std::get<map_type>(map_tuple).erase(std::get<id_type>(row_handle));

                }
            );



        public:
            template<size_t index>
            NCPP_CONSTEXPR typename item_type_t<index>& at_t(typename id_type_t<index> handle) {

                return column_t<index>().at(handle);
            }

            template<size_t index>
            NCPP_CONSTEXPR typename item_type_t<index>& at_t(uint32_t inner_index) {

                return column_t<index>().at(inner_index);
            }

            template<size_t index>
            NCPP_CONSTEXPR typename item_type_t<index>& at_t(typename meta_type_t<index> meta) {

                return column_t<index>().at(meta);
            }

            template<size_t index>
            NCPP_CONSTEXPR bool is_valid_t(typename id_type_t<index> handle) {

                return column_t<index>().is_valid(handle);
            }

            void clear() {

                tmp_helper::templated_for_t<clear_map_tuple_t, 0, column_count>(map_tuple_);

            }
            void reset() {

                tmp_helper::templated_for_t<reset_map_tuple_t, 0, column_count>(map_tuple_);

            }

            row_id_type emplace(const row_type& row) {

                row_id_type row_handle;

                tmp_helper::templated_for_t<emplace_row_copy_t, 0, column_count>(map_tuple_, row, row_handle);

                return row_handle;
            }
            row_id_type emplace(const column_types&... items) {

                row_type row = std::make_tuple(items...);

                return emplace(row);
            }
            row_id_type emplace(row_type&& row) {

                row_id_type row_handle;

                tmp_helper::templated_for_t<emplace_row_move_t, 0, column_count>(map_tuple_, std::forward<row_type>(row), row_handle);

                return row_handle;
            }
            row_id_type emplace(column_types&&... items) {

                return emplace(std::move(std::make_tuple(items...)));
            }

            void erase(row_id_type row_handle) {

                tmp_helper::templated_for_t<erase_row_t, 0, column_count>(map_tuple_, row_handle);
            }
            void erase(typename containers::handle_map_t<column_types, allocator_t>::id_type... handles) {

                return erase(std::move(std::make_tuple(handles...)));
            }
#pragma endregion

        };



        template<typename... column_types>
        using standard_data_t = typename data_t<std::allocator, column_types...>;

    }

}