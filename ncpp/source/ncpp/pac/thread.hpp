#pragma once

/**
 *  @file ncpp/pac/thread.hpp
 *  @brief Defines targeted platform thread.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {

	namespace pac {

		class win_thread;



		/**
		 *  If current platform is Windows, uses win_thread
		 */
#ifdef NCPP_WINDOWS_PLATFORM
		using thread = win_thread;
#endif

	}

}