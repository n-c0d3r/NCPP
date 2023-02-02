#pragma once

/** @file ncpp/memory_counting.hpp
*	@brief Implementing memory counting functionalities.
*/



#include <ncpp/prerequisites.hpp>



namespace ncpp {

	/**
	 *	Use to get current memory usage. 
	 */
	extern inline size_t memory_usage();
	/**
	 *	Increasing memory usage by given bytes.
	 */
	extern inline void increase_memory_usage(size_t bytes);
	/**
	 *	Decreasing memory usage by given bytes.
	 */
	extern inline void decrease_memory_usage(size_t bytes);

}