#pragma once

/**
 *  @file ncpp/pac/win_thread.hpp
 *  @brief Implements thread for windows platform.
 * 	@details Must be included with #ifdef NCPP_WINDOWS_PLATFORM.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>

#include <ncpp/pac/thread.hpp>



namespace ncpp {

	namespace pac {

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
			win_thread::win_thread(functor_type&& functor, sz stack_size = 1048576) :
				__platform__thread_(0),
				__platform__id_(0),
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

				if (__platform__thread_ == NULL)
				{
					std::cout << "thread creating failed" << std::endl;
				}

			}
			win_thread::~win_thread() {



			}

			inline win_thread(const win_thread&) = delete;
			inline win_thread& operator = (const win_thread&) = delete;
			inline win_thread(win_thread&&) = delete;
			inline win_thread& operator = (win_thread&&) = delete;



		public:
			/**
			 *  The main procedure of the thread.
			 */
			static inline DWORD WINAPI proc(LPVOID lpParam)
			{

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