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
		class NCPP_DEFAULT_ALIGNAS win_fiber {

		public:
			using functor_type = std::function<void(win_fiber&)>;



		private:
			fiber_creation_mode creation_mode_;
            /**
             *  The WinAPI fiber.
             */
			LPVOID __platform__fiber_;
            /**
             *  The main function to be run inside the fiber.
             */
			functor_type functor_;



		public:
			inline const fiber_creation_mode creation_mode() const { return creation_mode_; }
			inline LPVOID __platform__fiber() const { return __platform__fiber_; }
			inline const functor_type& functor() const { return functor_; }



		public:
			inline win_fiber() :
				creation_mode_(fiber_creation_mode::UNKNOWN),
				__platform__fiber_(0) 
			{



			}
			inline win_fiber::win_fiber(fiber_creation_mode mode, functor_type&& functor = [](win_fiber&){}) :
				creation_mode_(mode),
				__platform__fiber_(0),
				functor_(std::move(functor))
			{

				switch (creation_mode_)
				{
				case ncpp::pac::fiber_creation_mode::CONVERT_FROM_THREAD:
					__platform__fiber_ = ConvertThreadToFiber(0);
					break;
				case ncpp::pac::fiber_creation_mode::NEW:
					__platform__fiber_ = CreateFiber(0, proc, this);
					break;
				default:
					break;
				}

			}
			inline win_fiber::win_fiber(functor_type&& functor) :
				win_fiber(fiber_creation_mode::NEW, std::move(functor))
			{



			}
			win_fiber::~win_fiber() {

				if (creation_mode_ == fiber_creation_mode::NEW)
					DeleteFiber(__platform__fiber_);
				else
					ConvertFiberToThread();

			}

			win_fiber(const win_fiber&) = delete;
			win_fiber& operator = (const win_fiber&) = delete;
			inline win_fiber(win_fiber&& other) noexcept :
				creation_mode_(other.creation_mode_),
				__platform__fiber_(other.__platform__fiber_),
				functor_(std::move(other.functor_))
			{



			}
			inline win_fiber& operator = (win_fiber&& other)  noexcept
			{

				creation_mode_ = other.creation_mode_;
				__platform__fiber_ = other.__platform__fiber_;
				functor_ = std::move(other.functor_);

				return *this;
			}



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
			inline void switch_to_this(){

				SwitchToFiber(__platform__fiber_);

			}

		};
	
	} 

}