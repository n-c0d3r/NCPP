#pragma once

/**
 *  @file ncpp/pac/win_thread.hpp
 *  @brief Implements thread for windows platform.
 * 	@details Must be included with #ifdef NCPP_WINDOWS_PLATFORM.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/thread.hpp>



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
		 *  Windows platform thread.
		 * 	Uses WinAPI to implement thread.
		 */
		class NCPP_DEFAULT_SET_ALIGN win_thread {

		public:
			using functor_type = std::function<void(win_thread&)>;



		private:
			/**
			 *  The WinAPI thread.
			 */
			LPVOID __platform__thread_;
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



		public:
			inline win_thread::win_thread() :
				__platform__thread_(0),
				__platform__id_(0),
				stack_size_(NCPP_DEFAULT_THREAD_STACK_SIZE)
			{



			}
			inline win_thread::win_thread(functor_type&& functor, sz stack_size = NCPP_DEFAULT_THREAD_STACK_SIZE) :
				__platform__thread_(0),
				__platform__id_(0),
				is_ready_(0),
				stack_size_(stack_size),
				functor_(std::move(functor))
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
				functor_ = std::move(other.functor_);

				other.__platform__thread_ = 0;
				other.__platform__id_ = 0;
				other.stack_size_ = 0;

			}
			inline win_thread& operator = (win_thread&& other) {

				while (!other.is_ready_.load(std::memory_order_relaxed));
				std::atomic_thread_fence(std::memory_order_acquire);

				std::atomic_thread_fence(std::memory_order_release);
				*(other.current_thread_pp_) = this;

				__platform__thread_ = other.__platform__thread_;
				__platform__id_ = other.__platform__id_;
				stack_size_ = other.stack_size_;
				functor_ = std::move(other.functor_);

				other.__platform__thread_ = 0;
				other.__platform__id_ = 0;
				other.stack_size_ = 0;

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
			 *  Sleeps and waits until the thread proc done
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