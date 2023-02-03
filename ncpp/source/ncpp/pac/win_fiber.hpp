#pragma once

/**
 *  @file ncpp/pac/win_fiber.hpp
 *  @brief Implements fiber for windows platform.
 * 	@details Must be included with #ifdef NCPP_WINDOWS_PLATFORM.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/fiber.hpp>



namespace ncpp {
	
	namespace pac {

		/**
		 *  Windows platform fiber.
		 * 	Uses WinAPI to implement fiber.
		 */
		class NCPP_DEFAULT_ALIGN win_fiber {

		public:
			using functor_type = std::function<void(win_fiber&)>;



		private:
			const fiber_creation_mode creation_mode_;
            /**
             *  The WinAPI fiber.
             */
			LPVOID platform_fiber_;
            /**
             *  The main function to be run inside the fiber.
             */
			functor_type functor_;



		public:
			inline const fiber_creation_mode creation_mode() const { return creation_mode_; }
			inline LPVOID platform_fiber() const { return platform_fiber_; }
			inline const functor_type& functor() const { return functor_; }



		public:
			win_fiber(fiber_creation_mode mode, functor_type&& functor = [](win_fiber& fiber) {});
            ~win_fiber();



		public:
            /**
             *  The main procedure of the fiber.
             */
			static VOID WINAPI proc(LPVOID data)
			{
				reinterpret_cast<win_fiber*>(data)->functor_(*reinterpret_cast<win_fiber*>(data));
			}

            /**
             *  Switches to this fiber
             */
			void switch_to_this();

		};
	
	} 

}