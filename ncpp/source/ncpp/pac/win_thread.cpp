#include <ncpp/.hpp>



namespace ncpp {

	namespace pac {

		NCPP_THREAD_DATA win_thread* current_thread_pg = 0;
		win_thread& current_thread() {

			return *current_thread_pg;
		}

		void win_thread::set_current_thread_pg(win_thread& thread) {

			current_thread_pg = &thread;
			
			std::atomic_thread_fence(std::memory_order_release);

			thread.current_thread_pp_ = &current_thread_pg;

		}

	}

}