#pragma once

/**
 *  @file ncpp/pac/fiber.hpp
 *  @brief Defines targeted platform fiber. 
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {
	
	namespace pac {

		class win_fiber;



		/**
		 *  Indicates how to create a fiber.
		 */
		enum class fiber_creation_mode {

			CONVERT_FROM_THREAD,
			NEW

		};		


	
		/**
		 *  If current platform is Windows, uses win_fiber
		 */
#ifdef NCPP_WINDOWS_PLATFORM
		using fiber = win_fiber;
#endif
	
	} 

}