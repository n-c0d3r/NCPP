#include <ncpp/.hpp>



namespace ncpp {

	namespace cbjs {

		coroutine_state_updater default_coroutine_state_updater_g;



		coroutine::coroutine() :
			fiber_(pac::fiber_creation_mode::NEW, [this](pac::fiber& fiber) {

				this->loop();

			}),
			thread_fiber_p_(0),
			job_p_(0),
			state_updater_p_(&default_coroutine_state_updater_g)
		{



		}
		coroutine::~coroutine() {

			

		}

		void coroutine::loop() {

			while (system::instance().is_running()) {

				if (job_p_ != 0) {

					job_p_->functor(*job_p_, *this);

					job_p_->is_done = true;

					yield();

				}

			}

			assert(thread_fiber_p_ != 0 && "thread fiber is null, cant release coroutine!");
			thread_fiber_p_->switch_to_this();

		}



		coroutine_pool::coroutine_pool(size_t capacity, worker_thread& wt) :
			capacity_(capacity),
			coroutine_p_stack_(capacity),
			coroutine_vector_(capacity),
			worker_thread_(wt)
		{

			coroutine_vector_.reserve(capacity_);
			coroutine_vector_.resize(capacity_);
			for (size_t i = 0; i < capacity_; ++i) {

				coroutine_p_stack_.push(&coroutine_vector_[i]);

			}

			for (auto& coroutine : coroutine_vector_) {

				coroutine.bind_thread_fiber(worker_thread_.fiber());

			}

		}
		coroutine_pool::~coroutine_pool() {



		}

	}

}