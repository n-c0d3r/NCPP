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



#define NCPP_THREAD_DATA __declspec(thread)
#define NCPP_DEFAULT_THREAD_STACK_SIZE 1048576



		extern win_thread& current_thread();



		/**
		 *  The windows platform version of pac::thread
		 */
		class NCPP_DEFAULT_SET_ALIGN win_thread {

		public:
			using functor_type = std::function<void(win_thread&)>;



		private:
			struct main_thread_creation_placeholder {};



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
			win_thread** current_thread_pp_;
			bool is_main_;

#ifdef NCPP_ENABLE_FIBER
			fiber owned_fiber_;
#endif



		public:
			inline LPVOID __platform__thread() const { return __platform__thread_; }
			inline DWORD __platform__id() const { return __platform__id_; }
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



		private:
			/**
			 *  The constructor to create main thread instance.
			 */
			inline win_thread::win_thread(main_thread_creation_placeholder) :
				__platform__thread_(GetCurrentThread()),
				__platform__id_(GetCurrentThreadId()),
				stack_size_(0),
				
#ifdef NCPP_ENABLE_FIBER
				owned_fiber_(fiber_creation_mode::CONVERT_FROM_THREAD),
#endif
				
				is_main_(1)
			{

				sz sl_low = 0;
				sz sl_high = 0;
				GetCurrentThreadStackLimits(&sl_low, &sl_high);

				stack_size_ = sl_high - sl_low;

				set_current_thread_pg(*this);

			}

			static win_thread main_thread_g;



		public:
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
			inline win_thread::win_thread(functor_type&& functor, sz stack_size = NCPP_DEFAULT_THREAD_STACK_SIZE) :
				__platform__thread_(0),
				__platform__id_(0),
				is_ready_(0),
				stack_size_(stack_size),
				functor_(std::move(functor)),

#ifdef NCPP_ENABLE_FIBER
				owned_fiber_(fiber_creation_mode::CONVERT_FROM_THREAD),
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

			}
			win_thread::~win_thread() {

				if (!is_main_) {

					assert(is_done() && "Cant release currently running thread");

					CloseHandle(__platform__thread_);

				}

			}

			inline win_thread(const win_thread&) = delete;
			inline win_thread& operator = (const win_thread&) = delete;
			inline win_thread(win_thread&& other) :
				win_thread()
			{

				while (!other.is_ready_.load(std::memory_order_relaxed));
				std::atomic_thread_fence(std::memory_order_acquire);

				std::atomic_thread_fence(std::memory_order_release);
				*(other.current_thread_pp_) = this;

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
			inline win_thread& operator = (win_thread&& other) {

				while (!other.is_ready_.load(std::memory_order_relaxed));
				std::atomic_thread_fence(std::memory_order_acquire);

				std::atomic_thread_fence(std::memory_order_release);
				*(other.current_thread_pp_) = this;

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



		private:
			static void set_current_thread_pg(win_thread& thread);



		public:
			/**
			 *  The main procedure of the thread.
			 */
			static inline DWORD WINAPI proc(LPVOID lpParam)
			{

				set_current_thread_pg(*reinterpret_cast<win_thread*>(lpParam));

				reinterpret_cast<win_thread*>(lpParam)->is_ready_.store(1, std::memory_order_release);

				reinterpret_cast<win_thread*>(lpParam)->functor_(*reinterpret_cast<win_thread*>(lpParam));

				return 0;
			}

			/**
			 *  Sleeps and waits until the thread proc done.
			 *	Notes: calling this method in main thread can cause std::cout not working.
			 */
			inline void sleep_and_wait() {

				WaitForSingleObject(__platform__thread_, 0);

			}
			/**
			 *  Waits the thread proc done
			 */
			inline void wait() {

				while (!is_done());

			}

		};

	}

}