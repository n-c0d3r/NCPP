#pragma once

/** @file ncpp/log.hpp
*	@brief Implement logging functionalities.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/containers/.hpp>
#include <ncpp/iostream.hpp>

#pragma endregion



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	template<typename item_type__, class allocator_type__>
	std::ostream& operator << (
		std::ostream& os, 
		const ostream_input_t<
			std::vector<item_type__, allocator_type__>
		>& input
	)
	{

		if (input.second > NCPP_MAX_TAB_COUNT) {

			os << "...";

			return os;
		}

		os << "{" << std::endl;

		for (sz i = 0; i < input.first.size(); ++i) {

			for (u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

				os << " ";

			}

			os << i << ": ";

			safe_ostream_with_tab_t<std::ostream, item_type__>(os, { input.first[i], input.second + 1 });

			if (i != input.first.size() - 1)
				os << ",";

			os << std::endl;

		}

		for (u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}
		os << "}";

		return os;
	}

	template<typename item_type__, class allocator_type__>
	std::ostream& operator << (std::ostream& os, const std::vector<item_type__, allocator_type__>& v)
	{

		os << ostream_input_t<std::vector<item_type__, allocator_type__>> { v, 0 };

		return os;
	}



	template<
		typename item_type__,
		class id_allocator_type__,
		class cell_allocator_type__
	>
	std::ostream& operator << (
		std::ostream& os, 
		const ostream_input_t<
			containers::handle_map_t<item_type__, id_allocator_type__, cell_allocator_type__>
		>& input
	)
	{

		if (input.second > NCPP_MAX_TAB_COUNT) {

			os << "...";

			return os;
		}

		os << "{" << std::endl;

		for (sz i = 0; i < input.first.count(); ++i) {

			for (u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

				os << " ";

			}

			os << input.first[i].outer_index << ": ";

			safe_ostream_with_tab_t<std::ostream, item_type__>(os, { input.first[i].item, input.second + 1 });

			if (i != input.first.count() - 1)
				os << ",";

			os << std::endl;

		}

		for (u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

			os << " ";

		}
		os << "}";

		return os;
	}

	template<
		typename item_type__,
		class id_allocator_type__,
		class cell_allocator_type__
	>
	std::ostream& operator << (std::ostream& os, const containers::handle_map_t<item_type__, id_allocator_type__, cell_allocator_type__>& handle_map)
	{

		os << ostream_input_t<containers::handle_map_t<item_type__, id_allocator_type__, cell_allocator_type__>> { handle_map, 0 };

		return os;
	}

}

