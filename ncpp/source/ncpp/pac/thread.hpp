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
		 *  Returns the thread count of CPUs.
		 */
		static inline u8 hardware_concurrency() {

			return std::thread::hardware_concurrency();
		}



		/**
		 *  If current platform is Windows, uses win_thread
		 */
#ifdef NCPP_WINDOWS_PLATFORM
		using thread = win_thread;
#endif

	}

}