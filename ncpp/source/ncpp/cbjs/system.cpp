#include <ncpp/.hpp>



namespace ncpp {

	namespace cbjs {

		system::system(const system_settings& settings) :
			settings_(settings),
			ready_semaphore_(settings.worker_thread_count - 1)
		{

			is_running_.store(false, std::memory_order_release);



			worker_thread_vector_.resize(settings_.worker_thread_count);
			for (uint16_t i = 0; i < settings_.worker_thread_count; ++i) {

				worker_thread_vector_[i] = std::make_unique<cbjs::worker_thread>(i);

			}

		}
		system::~system() {



		}



		void system::start() {

			is_running_.store(true, std::memory_order_release);

			worker_thread_vector_[1]->schedule(settings_.entry_job);

			for (uint16_t i = 1; i < settings_.worker_thread_count; ++i) {

				worker_thread_vector_[i]->start();

			}

			worker_thread_vector_[0]->start();

			join();

		}

		void system::request_stop() {

			is_running_.store(false, std::memory_order_release);

		}
		void system::join() {

			for (uint16_t i = 1; i < settings_.worker_thread_count; ++i) {

				worker_thread_vector_[i]->join();

			}

		}

	}

}