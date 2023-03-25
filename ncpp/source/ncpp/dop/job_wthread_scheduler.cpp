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



		job_wthread_scheduler::job_wthread_scheduler(
			job_wthread& owner_wthread,
			u32 job_handle_queue_capacity
		) :
			owner_wthread_ref_(owner_wthread),
			job_handle_queue_capacity_(job_handle_queue_capacity),

			local_job_handle_queue_(job_handle_queue_capacity, tgh_global_allocator_t<job_handle>()),
			shared_job_handle_ref_queue_(job_handle_queue_capacity, tgh_global_allocator_t<utilities::lref_t<job_handle>>())
		{

			index_ = owner_wthread_ref_->index_;



			for (u32 i = 0; i < job_handle_queue_capacity_; ++i) {

				shared_job_handle_ref_queue_.push(local_job_handle_queue_.front());

			}
			for (u32 i = 0; i < job_handle_queue_capacity_; ++i) {

				shared_job_handle_ref_queue_.pop();

			}

		}

		job_wthread_scheduler::~job_wthread_scheduler() {



		}

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		void job_wthread_scheduler::schedule(job& j) {

			assert((index_ == current_wthread().index_) && "schedule is not allowed to be called in another thread.");



			std::atomic_thread_fence(std::memory_order_release);

			job_handle& handle = *local_job_handle_queue_.end();

			handle.increase_generation_index();
			handle.instance_count_.store(j.instance_count_, std::memory_order_relaxed);
			handle.owner_job_ref_ = j;



			u32 shared_wthread_count = min(job_system::instance().wthread_count_, j.batch_count_) - 1;
			u8 wthread_count = job_system::instance().wthread_count_;
			for (u16 i = 0; i < shared_wthread_count; ++i) {

				u8 shared_wthread_index = (index_ + 1 + i) % wthread_count;

				job_wthread& shared_wthread = *(job_system::instance().wthread_ref_vector_[shared_wthread_index]);
				job_wthread_scheduler& shared_shceduler = *(shared_wthread.scheduler_ref_);

				shared_shceduler.shared_job_handle_ref_queue_.push(handle);

			}



			local_job_handle_queue_.push(handle);
			
		}

		b8 job_wthread_scheduler::try_pop_local(utilities::lref_t<job_handle>& out_handle_ref) {

			utilities::lref_t<job_handle> handle_ref;

			if (local_job_handle_queue_.try_pop(handle_ref)) {

				out_handle_ref = handle_ref;

				return true;
			}

			return false;
		}
		b8 job_wthread_scheduler::try_pop_shared(utilities::lref_t<job_handle>& out_handle_ref) {

			utilities::lref_t<job_handle> handle_ref;

			if (shared_job_handle_ref_queue_.try_pop(handle_ref)) {

				out_handle_ref = handle_ref;

				return true;
			}
			
			return false;
		}
		b8 job_wthread_scheduler::try_steal(utilities::lref_t<job_handle>& out_handle_ref) {



			return false;
		}

	}

}