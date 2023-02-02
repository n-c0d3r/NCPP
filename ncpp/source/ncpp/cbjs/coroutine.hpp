#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

    namespace cbjs {

        class worker_thread;
        struct job;



        /**
         *  Indicating whether the coroutine is able to run   .
         */
        enum struct coroutine_state {

            WAITING = 0,
            RUNNABLE = 1

        };



        /**
         *  Responsible for updating the coroutine state.
         */
        class NCPP_DEFAULT_ALIGN coroutine_state_updater {

        public:
            coroutine_state_updater(){}

            virtual coroutine_state update() {

                return coroutine_state::RUNNABLE;
            }

        };

        /**
         *  Default coroutine state updater.
         *  Its the coroutine state updater using after job done and when coroutine created
         */
        extern coroutine_state_updater default_coroutine_state_updater_g;



        /**
         *  A coroutine state updater that only update coroutine state to coroutine_state::RUNNABLE after the indicated job done.
         */
        class NCPP_DEFAULT_ALIGN wait_job_done : public coroutine_state_updater {

        private:
            job& job_;



        public:
            wait_job_done(job& j) : job_(j) {}

            coroutine_state update() {

                return (coroutine_state)(job_.is_done);
            }

        };



        /**
         *  A coroutine is a function that can suspend execution to be resumed later.
         *  It contain a fiber to run the main worker loop, be able switch back to the owner thread fiber and resumed later by switching to that fiber. 
         */
        class NCPP_DEFAULT_ALIGN coroutine final
        {

        private:
            pac::fiber fiber_; /**< unique fiber of the coroutine. */
            pac::fiber* thread_fiber_p_; /**< the owner thread fiber. */
            job* job_p_; /**< the job pointer that point to the job need to be run. */
            coroutine_state_updater* state_updater_p_; /**< the current state updater. */
            coroutine_state state_; /**< the state of the coroutine. */



        public:
            inline coroutine_state state() const { return state_; }
            
            /**
             *  Indicating whether job_p_ is NULL.
             */
            inline bool is_has_job() const { return job_p_ != 0; }



        public:
            coroutine();
            ~coroutine();

        private:
            /**
             *  The main worker loop.
             */
            void loop();

        public:
            /**
             *  Binding the thread fiber to use when job done,... 
             */
            inline void bind_thread_fiber(pac::fiber& thread_fiber) {

                thread_fiber_p_ = &thread_fiber;

            }
            /**
             *  Binding the job to run.
             */
            inline void bind_job(job& j) {

                job_p_ = &j;

            }
            
            /**
             *  Changing the state updater by auto creating it from the passed arguments and switch to the owner thread fiber.
             */
            template<typename state_updater_type, typename... arg_types>
            inline void yield_t(arg_types&&... args) {

                state_updater_type sate_updater(std::forward<arg_types>(args)...);

                state_updater_p_ = &sate_updater;

                thread_fiber_p_->switch_to_this();

            }
            /**
             *  Changing the state updater and switch to the owner thread fiber.
             */
            inline void yield(coroutine_state_updater& state_updater) {

                state_updater_p_ = &state_updater;
                state_ = coroutine_state::WAITING;

                thread_fiber_p_->switch_to_this();

            }

        private:
            /**
             *  Changing the state updater to default and switch to the owner thread fiber.
             *  Also resetting job_p_ to NULL and state_ to coroutine_state::RUNNABLE.
             *  Be private because this function only need to call by the coroutine its self to switch back to the owner thread fiber when the coroutine is ready to take a new job.
             */
            inline void yield() {

                job_p_ = 0;
                state_updater_p_ = &default_coroutine_state_updater_g;
                state_ = coroutine_state::RUNNABLE;

                thread_fiber_p_->switch_to_this();

            }

        public:
            /**
             *  Switching from owner thread fiber to the coroutine's fiber.
             */
            inline void switch_to_this() {
                                
                fiber_.switch_to_this();
            }

            /**
             *  Updating the state by calling state_updater_p_->update().
             */
            inline coroutine_state update_state() {

                state_ = state_updater_p_->update();

                return state_;
            }

        };



        /**
         *  Storing coroutines.
         *  Can pop a coroutine to use and push it back again.
         */
        class NCPP_DEFAULT_ALIGN coroutine_pool final
        {

        private:
            size_t capacity_;
            containers::fixed_vector_stack_t<coroutine*> coroutine_p_stack_;
            std::vector<coroutine> coroutine_vector_;
            worker_thread& worker_thread_;



        public:
            inline size_t capacity() const { return capacity_; }
            inline worker_thread& get_worker_thread() { return worker_thread_; }
            inline const worker_thread& get_worker_thread() const { return worker_thread_; }



        public:
            coroutine_pool(size_t capacity, worker_thread& wt_);
            ~coroutine_pool();



        public:
            /**
             *  Push a coroutine pointer back to the coroutine pointer stack.
             */
            inline void push(coroutine* c) {

                coroutine_p_stack_.push(c);

            }
            /**
             *  Pop a coroutine pointer from the coroutine pointer stack.
             */
            inline coroutine* pop() {

                assert(coroutine_p_stack_.size() > 0);

                coroutine* result = coroutine_p_stack_.back();

                coroutine_p_stack_.pop();

                return result;
            }

        };

    }

}