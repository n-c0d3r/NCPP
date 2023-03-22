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



		job_system::job_system(
			utilities::lref_t<dop::job> entry_job_ref,
			u8 wthread_count,
			u32 job_handle_queue_capacity,
			u32 job_instance_pool_capacity
		) :
			entry_job_ref_(entry_job_ref),
			wthread_count_(wthread_count),
			job_handle_queue_capacity_(job_handle_queue_capacity),
			job_instance_pool_capacity_(job_instance_pool_capacity),

			tagged_heap_(),
			tgh_sys_lifetime_cid_(tagged_heap_.create_category()),

			wthread_ref_vector_(tgh_global_allocator_t<utilities::lref_t<job_wthread>>()),

			is_running_(false)
		{

			pac::reset_thread_indices();

			create_wthreads();
			init_wthreads();
			
		}

		job_system::~job_system() {



		}

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		void job_system::create_wthreads() {

			wthread_ref_vector_.resize(wthread_count_);

			for (u8 i = 0; i < wthread_count_; ++i) {

				wthread_ref_vector_[i] = tgh_create_sys_lifetime_t<job_wthread>(
					i,
					job_handle_queue_capacity_,
					job_instance_pool_capacity_
				);

			}

		}
		void job_system::init_wthreads() {
			
			for (u8 i = 0; i < wthread_count_; ++i) {

				wthread_ref_vector_[i]->init();

			}

		}
		void job_system::run_wthreads() {

			is_running_.store(true, std::memory_order_release);



			for (u8 i = 1; i < wthread_count_; ++i) {

				wthread_ref_vector_[i]->run();

			}

			wthread_ref_vector_[0]->run();

		}
		void job_system::wait_wthreads() {

			for (u8 i = 0; i < wthread_count_; ++i) {

				wthread_ref_vector_[i]->wait();

			}

			pac::reset_thread_indices();

		}



		void job_system::run() {

			run_wthreads();

		}
		void job_system::wait() {

			wait_wthreads();

		}

		job_handle& job_system::schedule(job& j) {

			job_handle handle(j);

			job_wthread& current_thread = current_wthread();

			return handle;
		}

	}

}