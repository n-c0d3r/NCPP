#pragma once

/**
 *  @file ncpp/pac/win_fiber.hpp
 *  @brief Implementing fiber for windows platform.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/fiber.hpp>



namespace ncpp {
	
	namespace pac {
	
#ifdef NCPP_WINDOWS_PLATFORM
		class NCPP_DEFAULT_ALIGN win_fiber {

		public:
			using functor_type = std::function<void(win_fiber&)>;



		private:
			const fiber_creation_mode creation_mode_;
			LPVOID platform_fiber_;
			functor_type functor_;



		public:
			inline const fiber_creation_mode creation_mode() const { return creation_mode_; }
			inline LPVOID platform_fiber() const { return platform_fiber_; }
			inline const functor_type& functor() const { return functor_; }



		public:
			win_fiber(fiber_creation_mode mode, functor_type&& functor = [](win_fiber& fiber) {});
            ~win_fiber();



		public:
			static VOID WINAPI proc(LPVOID data)
			{
				reinterpret_cast<win_fiber*>(data)->functor_(*reinterpret_cast<win_fiber*>(data));
			}

			void switch_to_this();

		};
#endif
	
	} 

}