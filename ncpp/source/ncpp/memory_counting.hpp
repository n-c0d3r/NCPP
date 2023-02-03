#pragma once

/** @file ncpp/memory_counting.hpp
*	@brief Implements memory counting functionalities.
*/



#include <ncpp/prerequisites.hpp>



namespace ncpp {

	/**
	 *	Uses to get current memory usage. 
	 */
	extern inline sz memory_usage();
	/**
	 *	Increases memory usage by given bytes.
	 */
	extern inline void increase_memory_usage(sz bytes);
	/**
	 *	Decreases memory usage by given bytes.
	 */
	extern inline void decrease_memory_usage(sz bytes);

}