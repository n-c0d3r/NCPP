#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

    namespace cbjs {

        class worker_thread;
        struct job;



        enum struct coroutine_state {

            WAITING = 0,
            RUNNABLE = 1

        };



        class NCPP_DEFAULT_ALIGN coroutine_state_updater {

        public:
            coroutine_state_updater(){}

            virtual coroutine_state update() {

                return coroutine_state::RUNNABLE;
            }

        };

        extern coroutine_state_updater default_coroutine_state_updater_g;



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
         *  A function that can suspend execution to be resumed later.
         */
        class NCPP_DEFAULT_ALIGN coroutine final
        {

        private:
            pac::fiber fiber_;
            pac::fiber* thread_fiber_p_;
            job* job_p_;
            coroutine_state_updater* state_updater_p_;
            coroutine_state state_;



        public:
            inline coroutine_state state() const { return state_; }
            inline bool is_has_job() const { return job_p_ != 0; }



        public:
            coroutine();
            ~coroutine();

        private:
            void loop();

        public:
            inline void bind_thread_fiber(pac::fiber& thread_fiber) {

                thread_fiber_p_ = &thread_fiber;

            }
            inline void bind_job(job& j) {

                job_p_ = &j;

            }

            template<typename state_updater_type, typename... arg_types>
            inline void yield_t(arg_types&&... args) {

                state_updater_type sate_updater(std::forward<arg_types>(args)...);

                state_updater_p_ = &sate_updater;

                thread_fiber_p_->switch_to_this();

            }
            inline void yield(coroutine_state_updater& state_updater) {

                state_updater_p_ = &state_updater;
                state_ = coroutine_state::WAITING;

                thread_fiber_p_->switch_to_this();

            }
            inline void yield() {

                job_p_ = 0;
                state_updater_p_ = &default_coroutine_state_updater_g;
                state_ = coroutine_state::RUNNABLE;

                thread_fiber_p_->switch_to_this();

            }

            inline void switch_to_this() {
                                
                fiber_.switch_to_this();
            }

            inline coroutine_state update_state() {

                state_ = state_updater_p_->update();

                return state_;
            }

        };



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
            inline void push(coroutine* c) {

                coroutine_p_stack_.push(c);

            }
            inline coroutine* pop() {

                assert(coroutine_p_stack_.size() > 0);

                coroutine* result = coroutine_p_stack_.back();

                coroutine_p_stack_.pop();

                return result;
            }

        };

    }

}