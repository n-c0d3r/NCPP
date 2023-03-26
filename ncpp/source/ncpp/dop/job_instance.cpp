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



		job_instance::job_instance() :
			pac_fiber_(
				pac::fiber_creation_mode::NEW,
				[&](pac::fiber& pac_fiber) {

					worker_loop();

				}
			),
			instance_index_(0)
		{



		}

		job_instance::~job_instance() {



		}

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		void job_instance::worker_loop() {

			while (job_system::instance().is_running()) {

				job& j = *(handle_ref_->owner_job_ref_);

				j.execute(*this);

				stack_allocator_.stack_heap().clear_group(stack_group_);

				handle_ref_->decrease_counter();

				current_wthread().pac_thread_ref_->owned_fiber().switch_to_this();

			}

		}

		void job_instance::setup_for_handle(job_handle& handle, u32 instance_index) {

			instance_index_ = instance_index;

			handle_ref_ = handle;



			job& j = *(handle_ref_->owner_job_ref_);

			utilities::lref_t<stack_heap_t<>> heap;

			switch (j.stack_allocator_option_)
			{
			case job_stack_allocator_option::LARGE:
				heap = current_wthread().stack_heap_LARGE_;
				break;
			case job_stack_allocator_option::NORMAL:
				heap = current_wthread().stack_heap_NORMAL_;
				break;
			case job_stack_allocator_option::SMALL:
				heap = current_wthread().stack_heap_SMALL_;
				break;
			default:
				break;
			}

			stack_allocator_ = stack_allocator_t<u8>(*heap, stack_group_);

		}

		void job_instance::switch_to_this() {

			pac_fiber_.switch_to_this();

		}

		void job_instance::wait_for_counter(utilities::lref_t<au32> counter_ref) {

			counter_ref_ = counter_ref;

			current_wthread().pac_thread_ref_->owned_fiber().switch_to_this();

		}

	}

}