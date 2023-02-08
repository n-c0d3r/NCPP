#include <ncpp/.hpp>



namespace ncpp {

	namespace pac {

		NCPP_THREAD_LOCAL_DATA win_thread* current_thread_pg = 0;
		win_thread& current_thread() {

			return *current_thread_pg;
		}

		NCPP_THREAD_LOCAL_DATA u32 current_thread_index_g = 0;
		static std::atomic_uint32_t last_thread_index = 0;
		u32 current_thread_index() {

			return current_thread_index_g;
		}

		void win_thread::set_current_thread_pg(win_thread& thread) {

			current_thread_pg = &thread;
			
			std::atomic_thread_fence(std::memory_order_release);

			thread.current_thread_pp_ = &current_thread_pg;

			current_thread_index_g = last_thread_index.load(std::memory_order_acquire);

			last_thread_index.fetch_add(1, std::memory_order_relaxed);

		}



		win_thread win_thread::main_thread_g = win_thread(win_thread::main_thread_creation_placeholder());

	}

}