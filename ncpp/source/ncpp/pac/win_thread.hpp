#pragma once

/**
 *  @file ncpp/pac/win_thread.hpp
 *  @brief Implements thread for windows platform.
 * 	@details Must be included with #ifdef NCPP_WINDOWS_PLATFORM.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/thread.hpp>

#ifdef NCPP_ENABLE_FIBER
#include <ncpp/pac/fiber.hpp>
#endif



#ifndef NCPP_WINDOWS_PLATFORM
static_assert(false, "Must be included with #ifdef NCPP_WINDOWS_PLATFORM");
#endif



namespace ncpp {

	namespace pac {

		class win_thread;


		/**
		 *	Specifies a variable storing in thread local storage. 
		 */
#define NCPP_THREAD_LOCAL_DATA __declspec(thread)



		/**
		 *	Gets current thread id
		 */
		extern u32 current_thread_id();
		/**
		 *	Gets current thread index
		 */
		extern u32 current_thread_index();
		/**
		 *	Gets main thread
		 */
		extern win_thread& main_thread();



		/**
		 *  The windows platform version of pac::thread
		 */
		class NCPP_DEFAULT_ALIGNAS win_thread {

		public:
			friend win_thread& main_thread();



#pragma region Typedefs
		public:
			using functor_type = std::function<void()>;
#pragma endregion



#pragma region Nested Types
		private:
			struct main_thread_creation_placeholder {};
#pragma endregion



#pragma region Properties
		private:
			/**
			 *  The WinAPI thread.
			 */
			HANDLE __platform__thread_;
			/**
			 *  The id of __platform__thread_.
			 */
			DWORD __platform__id_;
			/**
			 *  The main function to be run inside the thread.
			 */
			functor_type functor_;
			sz stack_size_;
			std::atomic_bool is_ready_;
			bool is_main_;

#ifdef NCPP_ENABLE_FIBER
			fiber owned_fiber_;
#endif
#pragma endregion



#pragma region Getters and Setters
		public:
			inline LPVOID __platform__thread() const { return __platform__thread_; }
			inline DWORD __platform__id() const { return __platform__id_; }
			inline u32 id() const { return __platform__id_; }
			inline const functor_type& functor() const { return functor_; }
			inline bool is_done() const {

				DWORD ex_code;

				bool r = GetExitCodeThread(
					__platform__thread_,
					&ex_code
				);

				return (!r) || (ex_code != STILL_ACTIVE);
			}
			inline bool is_main() { return is_main_; }

			inline fiber& owned_fiber() { return owned_fiber_; }
#pragma endregion



#pragma region Constructors, Destrutor and Operators
		private:
			/**
			 *  The constructor to create main thread instance.
			 */
			inline win_thread::win_thread(main_thread_creation_placeholder) :
				__platform__thread_(GetCurrentThread()),
				__platform__id_(GetCurrentThreadId()),
				stack_size_(0),
				is_ready_(1),
				
#ifdef NCPP_ENABLE_FIBER
				owned_fiber_(fiber_creation_mode::CONVERT_FROM_THREAD),
#endif
				
				is_main_(1)
			{

				sz sl_low = 0;
				sz sl_high = 0;
				GetCurrentThreadStackLimits(&sl_low, &sl_high);

				stack_size_ = sl_high - sl_low;

			}

			static win_thread main_thread_g;



		public:
			/**
			 *	Default constructor.
			 *	This constructor will construct an empty thread object
			 */
			inline win_thread::win_thread() :
				__platform__thread_(0),
				__platform__id_(0),
				stack_size_(NCPP_DEFAULT_THREAD_STACK_SIZE),

#ifdef NCPP_ENABLE_FIBER
				owned_fiber_(),
#endif

				is_main_(0)
			{



			}
			/**
			 *	Initialization constructor.
			 */
			inline win_thread::win_thread(functor_type&& functor, sz stack_size = NCPP_DEFAULT_THREAD_STACK_SIZE) :
				__platform__thread_(0),
				__platform__id_(0),
				is_ready_(0),
				stack_size_(stack_size),
				functor_(std::move(functor)),

#ifdef NCPP_ENABLE_FIBER
				owned_fiber_(fiber_creation_mode::CONVERT_FROM_THREAD_DI),
#endif

				is_main_(0)
			{

				__platform__thread_ = CreateThread(
					0,
					stack_size,
					proc,
					this,
					STACK_SIZE_PARAM_IS_A_RESERVATION,
					&__platform__id_
				);

				assert(__platform__thread_ != 0 && "thread creating failed");

				while (!is_ready_.load(std::memory_order_acquire));

			}
			/**
			 *	Destructor
			 */
			win_thread::~win_thread() {

				if (__platform__thread_ == 0) return;

				if (!is_main_) {

					assert(is_done() && "Cant release currently running thread");

					CloseHandle(__platform__thread_);

				}

			}

			inline win_thread(const win_thread&) = delete;
			inline win_thread& operator = (const win_thread&) = delete;

			/**
			 *	Move constructor
			 */
			inline win_thread(win_thread&& other) noexcept  :
				win_thread()
			{

				while (!other.is_ready_.load(std::memory_order_relaxed));
				std::atomic_thread_fence(std::memory_order_acquire);

				__platform__thread_ = other.__platform__thread_;
				__platform__id_ = other.__platform__id_;
				stack_size_ = other.stack_size_;
				is_main_ = other.is_main_;
				functor_ = std::move(other.functor_);

#ifdef NCPP_ENABLE_FIBER
				owned_fiber_ = std::move(other.owned_fiber_);
#endif

				other.__platform__thread_ = 0;
				other.__platform__id_ = 0;
				other.stack_size_ = 0;
				other.is_main_ = 0;

			}

			/**
			 *	Move operator
			 */
			inline win_thread& operator = (win_thread&& other) noexcept {

				while (!other.is_ready_.load(std::memory_order_relaxed));
				std::atomic_thread_fence(std::memory_order_acquire);

				__platform__thread_ = other.__platform__thread_;
				__platform__id_ = other.__platform__id_;
				stack_size_ = other.stack_size_;
				is_main_ = other.is_main_;
				functor_ = std::move(other.functor_);

#ifdef NCPP_ENABLE_FIBER
				owned_fiber_ = std::move(other.owned_fiber_);
#endif

				other.__platform__thread_ = 0;
				other.__platform__id_ = 0;
				other.stack_size_ = 0;
				other.is_main_ = 0;

				return *this;
			}
#pragma endregion



#pragma region Methods
		public:
			/**
			 *  The main procedure of the thread.
			 */
			static DWORD WINAPI proc(LPVOID lpParam);

			/**
			 *  Sleeps and waits until the thread proc done.
			 *	Notes: calling this method in main thread can cause std::cout not working.
			 */
			inline void sleep_and_wait() {

				assert(__platform__thread_ != 0 && "thread is null");

				WaitForSingleObject(__platform__thread_, 0);

			}
			/**
			 *  Waits the thread proc done
			 */
			inline void wait() {

				assert(__platform__thread_ != 0 && "thread is null");

				while (!is_done());

			}

			/**
			 *	Sets thread affinity by mask
			 */
			inline u64 set_affinity_mask(u64 mask) {

				assert(__platform__thread_ != 0 && "thread is null");

				return SetThreadAffinityMask(__platform__thread_, mask);
			}
#pragma endregion

		};

	}

}