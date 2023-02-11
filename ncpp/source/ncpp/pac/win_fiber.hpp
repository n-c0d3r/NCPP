#pragma once

/**
 *  @file ncpp/pac/win_fiber.hpp
 *  @brief Implements fiber for windows platform.
 * 	@details Must be included with #ifdef NCPP_WINDOWS_PLATFORM.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/fiber.hpp>



#ifndef NCPP_WINDOWS_PLATFORM
static_assert(false, "Must be included with #ifdef NCPP_WINDOWS_PLATFORM");
#endif



namespace ncpp {
	
	namespace pac {

		extern u32 current_thread_index();



		/**
		 *  Windows platform fiber.
		 * 	Uses WinAPI to implement fiber.
		 */
		class NCPP_DEFAULT_ALIGNAS win_fiber {

#pragma region Typedefs
		public:
			using functor_type = std::function<void(win_fiber&)>;
#pragma endregion



#pragma region Properties
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
			sz stack_size_;
#pragma endregion



#pragma region Getters and Setters
		public:
			inline const fiber_creation_mode creation_mode() const { return creation_mode_; }
			inline LPVOID __platform__fiber() const { return __platform__fiber_; }
			inline const functor_type& functor() const { return functor_; }
			inline sz stack_size() const { return stack_size_; }
#pragma endregion



#pragma region Constructors, Destructor and Operator
		public:
			/**
			 *  Default constructor.
			 *	This constructor will construct an empty fiber object.
			 */
			inline win_fiber() :
				creation_mode_(fiber_creation_mode::UNKNOWN),
				__platform__fiber_(0) 
			{



			}
			/**
			 *  Initialization constructor.
			 */
			inline win_fiber::win_fiber(fiber_creation_mode mode, functor_type&& functor = [](win_fiber&) {}, sz stack_size = NCPP_DEFAULT_FIBER_STACK_SIZE) :
				creation_mode_(mode),
				__platform__fiber_(0),
				functor_(std::move(functor)),
				stack_size_(stack_size)
			{

				switch (creation_mode_)
				{
				case ncpp::pac::fiber_creation_mode::CONVERT_FROM_THREAD:
					__platform__fiber_ = ConvertThreadToFiber(this);
					break;
				case ncpp::pac::fiber_creation_mode::NEW:
					__platform__fiber_ = CreateFiber(stack_size_, proc, this);
					break;
				default:
					break;
				}

			}
			/**
			 *  NEW-mode fiber constructor.
			 */
			inline win_fiber::win_fiber(functor_type&& functor, sz stack_size = NCPP_DEFAULT_FIBER_STACK_SIZE):
				win_fiber(fiber_creation_mode::NEW, std::forward<functor_type>(functor), stack_size)
			{



			}
			/**
			 *  Destructor
			 */
			win_fiber::~win_fiber() {

				if (__platform__fiber_ == 0) return;

				if (creation_mode_ == fiber_creation_mode::NEW || creation_mode_ == fiber_creation_mode::NEW_DI) {

					DeleteFiber(__platform__fiber_);

				}
				else {

					ConvertFiberToThread();

				}

			}

			win_fiber(const win_fiber&) = delete;
			win_fiber& operator = (const win_fiber&) = delete;

			/**
			 *  Move constructor.
			 */
			inline win_fiber(win_fiber&& other) noexcept :
				creation_mode_(other.creation_mode_),
				__platform__fiber_(other.__platform__fiber_),
				functor_(std::move(other.functor_))
			{



			}
			/**
			 *  Move operator.
			 */
			inline win_fiber& operator = (win_fiber&& other)  noexcept
			{

				creation_mode_ = other.creation_mode_;
				__platform__fiber_ = other.__platform__fiber_;
				stack_size_ = other.stack_size_;
				functor_ = std::move(other.functor_);

				other.creation_mode_ = fiber_creation_mode::UNKNOWN;
				other.__platform__fiber_ = 0;
				other.stack_size_ = 0;

				return *this;
			}
#pragma endregion



#pragma region Methods
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
			/**
			 *	Delayed Initializes the fiber
			 */
			inline void delayed_init() {

				switch (creation_mode_)
				{
				case ncpp::pac::fiber_creation_mode::CONVERT_FROM_THREAD_DI:
					__platform__fiber_ = ConvertThreadToFiber(this);
					break;
				case ncpp::pac::fiber_creation_mode::NEW_DI:
					__platform__fiber_ = CreateFiber(stack_size_, proc, this);
					break;
				default:
					break;
				}

			}
#pragma endregion

		};
	
	} 

}