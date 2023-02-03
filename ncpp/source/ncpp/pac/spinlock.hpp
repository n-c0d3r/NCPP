#pragma once

/**
 *  @file ncpp/pac/spinlock.hpp
 *  @brief Implementing spinlock.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {
	
	namespace pac {
	
		/**
		 *	Implements spinlock
		 */
		class NCPP_DEFAULT_ALIGN spinlock {

		private:
			std::atomic_flag flag_;



		public:
			spinlock() {



			}

			void lock() {

				while (!flag_.test_and_set(std::memory_order_acquire));

			}
			void unlock() {

				flag_.clear(std::memory_order_release);

			}

		};
	
	} 

}