#include <ncpp/.hpp>



namespace ncpp {

	namespace dop {

		worker_thread::worker_thread(u8 index) :
			index_(index),
			job_p_allocator_(cbjs::instance().tagged_heap(), cbjs::instance().tgh_forever_cid()),

			high_job_p_queue_(NCPP_JOB_QUEUE_CAPACITY, job_p_allocator_),
			normal_job_p_queue_(NCPP_JOB_QUEUE_CAPACITY, job_p_allocator_),
			low_job_p_queue_(NCPP_JOB_QUEUE_CAPACITY, job_p_allocator_),

			coroutine_pool_allocator_(cbjs::instance().tagged_heap(), cbjs::instance().tgh_forever_cid()),
			coroutine_pool_p_()
		{

			if (index_ == 0) {

				pac_thread_ = std::move(pac::main_thread());

			}

		}

		void worker_thread::start() {

			if (index_ == 0) {

				main_loop();

			}
			else {

				pac_thread_ = pac::thread(
					[&]() {

						main_loop();

					}
				);

			}

		}

		void worker_thread::main_loop() {

			if (index() == 0) {

				schedule(cbjs::instance().settings().entry_job);


			}

			coroutine_pool_p_ = utilities::allocate_unique_t<coroutine_pool>(coroutine_pool_allocator_);



			while (cbjs::instance().is_running()) {

				{

					for (u32 i = 0; i < 8; ++i) {

						job* job_p = 0;

						high_job_p_queue_.try_pop(job_p);

						if (job_p) {

							coroutine* coroutine_p = coroutine_pool_p_->pop();

							coroutine_p->bind_job(*job_p);

						}
						else {

							break;

						}

					}

				}



				if (
					index() == 0 
					&& cbjs::instance().settings().entry_job.is_done()
				) {

					cbjs::instance().request_stop();

				}

			}

		}

	}

}

