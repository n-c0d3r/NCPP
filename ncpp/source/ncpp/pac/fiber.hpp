#pragma once

/**
 *  @file ncpp/pac/fiber.hpp
 *  @brief Defining targeted platform fiber.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {
	
	namespace pac {

		class win_fiber;



		enum class fiber_creation_mode {

			CONVERT_FROM_THREAD,
			NEW

		};		


	
#ifdef NCPP_WINDOWS_PLATFORM
		using fiber = win_fiber;
#endif
	
	} 

}