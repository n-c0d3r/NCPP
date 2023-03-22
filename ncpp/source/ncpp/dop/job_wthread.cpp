#include <ncpp/.hpp>



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

	namespace dop {



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		thread_local utilities::lref_t<job_wthread> current_wthread_g;

		job_wthread& current_wthread() {

			return *current_wthread_g;
		}



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		job_wthread::job_wthread(
			u8 index,
			u32 job_handle_queue_capacity,
			u32 job_instance_pool_capacity
		) :
			index_(index),
			job_handle_queue_capacity_(job_handle_queue_capacity),
			job_instance_pool_capacity_(job_instance_pool_capacity),

			scheduler_ref_vector_(tgh_global_allocator_t<utilities::lref_t<job_wthread_scheduler>>())
		{

			job_instance_pool_ref_ = tgh_create_sys_lifetime_t<job_instance_pool>(
				*this,
				job_instance_pool_capacity_
			);

			create_schedulers();

		}

		job_wthread::~job_wthread() {



		}

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		void job_wthread::worker_loop() {

			/// setups
			current_wthread_g = *this;



			/// main loop
			while (job_system::instance().is_running()) {

				/// processes job queues
				{



				}



				/// processes job instances
				{



				}



				/// checks if entry job was done
				if (index_ == 0)
				{

					if (job_system::instance().entry_job_ref_->is_done_) {

						job_system::instance().is_running_.store(false, std::memory_order_release);

					}

				}

			}

		}

		void job_wthread::create_schedulers() {

			u8 wthread_count = job_system::instance().wthread_count_;

			scheduler_ref_vector_.resize(wthread_count);

			for (u8 i = 0; i < wthread_count; ++i) {

				scheduler_ref_vector_[i] = tgh_create_sys_lifetime_t<job_wthread_scheduler>(
					*this,
					*job_system::instance().wthread_ref_vector_[i],
					job_handle_queue_capacity_
				);

			}

		}

		void job_wthread::init() {

			init_schedulers();

		}
		void job_wthread::init_schedulers() {



		}

		bool job_wthread::try_make_job_instance(job_handle& handle) {

			u32 job_instance_index = 0;
				
			if (!handle.owner_job_ref_->try_optain_instance_index(job_instance_index))
				return false;

			

			return true;
		}



		void job_wthread::run() {
			
			if (index_ != 0) {

				pac_thread_ref_ = tgh_create_sys_lifetime_t<pac::thread>(
					[&]() {

						worker_loop();

					}
				);

			}
			else {

				pac_thread_ref_ = pac::main_thread();

				worker_loop();

			}

		}
		void job_wthread::wait() {

			if(index_ != 0)
				pac_thread_ref_->wait();

		}

	}

}