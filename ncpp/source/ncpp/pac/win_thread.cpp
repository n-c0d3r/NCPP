#include <ncpp/.hpp>



namespace ncpp {

	namespace pac {

#ifdef NCPP_WINDOWS_PLATFORM
		NCPP_THREAD_LOCAL_DATA u32 current_thread_index_g = 0;
		static std::atomic_uint32_t thread_created_count_g = 1;



		u32 current_thread_id() {

			return GetCurrentThreadId();
		}
		u32 current_thread_index() {

			return current_thread_index_g;
		}
		win_thread& main_thread() {

			return win_thread::main_thread_g;
		}



		DWORD WINAPI win_thread::proc(LPVOID lpParam)
		{

			win_thread& wt = *reinterpret_cast<win_thread*>(lpParam);

			auto functor = std::move(wt.functor_);

			current_thread_index_g = thread_created_count_g.load(std::memory_order_acquire);

			thread_created_count_g.fetch_add(1, std::memory_order_release);

#ifdef NCPP_ENABLE_FIBER
			wt.owned_fiber_.delayed_init();
#endif

			wt.is_ready_.store(1, std::memory_order_release);

			functor();

			return 0;
		}
#endif



		win_thread win_thread::main_thread_g = win_thread(win_thread::main_thread_creation_placeholder());

	}

}