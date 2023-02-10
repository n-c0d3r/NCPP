#include <ncpp/.hpp>



namespace ncpp {

	namespace dop {

        coroutine_pool::coroutine_pool() :
            coroutine_allocator_(cbjs::instance().tagged_heap(), cbjs::instance().tgh_forever_cid()),
            coroutine_p_allocator_(cbjs::instance().tagged_heap(), cbjs::instance().tgh_forever_cid()),
            coroutine_vector_(NCPP_COROUTINE_COUNT_PER_WORKER_THREAD, coroutine_allocator_),
            coroutine_p_stack_(NCPP_COROUTINE_COUNT_PER_WORKER_THREAD, coroutine_p_allocator_)
        {

            for (u32 i = 0; i < NCPP_COROUTINE_COUNT_PER_WORKER_THREAD; ++i) {

                coroutine_p_stack_.push(&coroutine_vector_[i]);

            }

        }

		void coroutine::main_loop() {

            while (cbjs::instance().is_running()) {

                if (job_p_ != 0) {

                    job_p_->execute(*this);
                    job_p_ = 0;

                }

            }

		}

	}

}

