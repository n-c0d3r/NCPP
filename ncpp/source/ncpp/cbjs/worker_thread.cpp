#include <ncpp/.hpp>



namespace ncpp {

	namespace cbjs {

		worker_thread::worker_thread(u32 index) :
			index_(index),
			fiber_p_(),
			coroutine_pool_p_()
		{



		}
		worker_thread::~worker_thread() {



		}



		void worker_thread::start() {

			if (index_ != 0) {

				std::thread std_thread(
					[](worker_thread* wt_p) {

						wt_p->loop();

					},
					this
				);

				std_thread_.swap(std_thread);

			}
			else {

				loop();

			}

		}
		void worker_thread::join() {

			std_thread_.join();

		}
		void worker_thread::loop() {

			fiber_p_ = std::make_unique<pac::fiber>(pac::fiber_creation_mode::CONVERT_FROM_THREAD);
			coroutine_pool_p_ = std::make_unique<coroutine_pool>(system::instance().settings().coroutine_count_per_worker_thread, *this);



			if (index_ != 0) {

				system::instance().ready_semaphore().notify();

			}
			system::instance().ready_semaphore().try_wait();



			while(system::instance().is_running()) {
								
				//process job queues
				for (u8 job_queue_index = 0; job_queue_index < NCPP_DEFAULT_JOB_PRIORITY_COUNT; ++job_queue_index) {

					job_p_queue_type& job_p_queue = job_p_queue_array_[job_queue_index];

					for (u8 i = 0; i < min(NCPP_DEFAULT_JOB_PRIORITY_COUNT - job_queue_index, job_p_queue.size()); ++i) {

						job* job_p = 0;

						{

							utilities::unique_lock_t<pac::spinlock> lock_guard(job_p_queue_lock_array_[job_queue_index]);

							job_p = job_p_queue.front();

							job_p_queue.pop();

						}

						if (job_p != 0) {

							coroutine* coroutine_p = coroutine_pool_p_->pop();

							coroutine_p->bind_job(*job_p);

							coroutine_p_queue_array_[job_p->priority].push(coroutine_p);

						}

					}

				}



				//process wait queues
				for (u8 job_queue_index = 0; job_queue_index < NCPP_DEFAULT_JOB_PRIORITY_COUNT; ++job_queue_index) {

					coroutine_p_queue_type& coroutine_p_queue = coroutine_p_queue_array_[job_queue_index];

					const u8 coroutine_count = min(NCPP_DEFAULT_JOB_PRIORITY_COUNT - job_queue_index, coroutine_p_queue.size());

					for (u8 i = 0; i < coroutine_count; ++i) {

						coroutine* coroutine_p = coroutine_p_queue.front();

						coroutine_p_queue.pop();

						if (coroutine_p->update_state() == coroutine_state::RUNNABLE) {

							coroutine_p->switch_to_this();

							if (coroutine_p->is_has_job()) {

								coroutine_p_queue.push(coroutine_p);

							}
							else {

								coroutine_pool_p_->push(coroutine_p);

							}

						}
						else {

							coroutine_p_queue.push(coroutine_p);

						}

					}

				}



				if (index_ == 0 && system::instance().settings_.entry_job.is_done) {

					system::instance().request_stop();

				}

			}

		}

		void worker_thread::schedule(job& job) {

			assert(job.priority >= 0 && job.priority < NCPP_DEFAULT_JOB_PRIORITY_COUNT);

			job_p_queue_array_[job.priority].push(&job);

		}

	}

}