#pragma once

/**
 *  @file ncpp/dop/worker_thread.hpp
 *  @brief Implements coroutine based job system.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

    namespace dop {

        struct NCPP_DEFAULT_ALIGNAS coroutine;
        class NCPP_DEFAULT_ALIGNAS coroutine_pool;
        struct NCPP_DEFAULT_ALIGNAS job;
        class NCPP_DEFAULT_ALIGNAS worker_thread;
        class NCPP_DEFAULT_ALIGNAS cbjs;



        /**
         *  A worker thread is a thread working in a job system.
         */
        class NCPP_DEFAULT_ALIGNAS worker_thread
        {

#pragma region Typedefs
        public:
            using job_p_allocator_type = tgh_allocator_t<job*>;
            using job_p_queue_type = containers::cfv_queue_t<job*, job_p_allocator_type>;
            using coroutine_pool_allocator_type = tgh_allocator_t<coroutine_pool>;
            using coroutine_pool_type = std::unique_ptr<coroutine_pool, utilities::allocator_deleter_t<coroutine_pool_allocator_type>>;
#pragma endregion



#pragma region Properties
        private:
            u8 index_;
            pac::thread pac_thread_;

            job_p_allocator_type job_p_allocator_;
            job_p_queue_type high_job_p_queue_;
            job_p_queue_type normal_job_p_queue_;
            job_p_queue_type low_job_p_queue_;

            coroutine_pool_allocator_type coroutine_pool_allocator_;
            coroutine_pool_type coroutine_pool_p_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline u8 index() const { return index_; }
            inline pac::thread& pac_thread() { return pac_thread_; }
            inline const pac::thread& pac_thread() const { return pac_thread_; }

            inline coroutine_pool& get_coroutine_pool() { return *coroutine_pool_p_; }
            inline const coroutine_pool& get_coroutine_pool() const { return *coroutine_pool_p_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization Constructor
             */
            worker_thread(u8 index);
            /**
             *  Destructor
             */
            ~worker_thread() {



            }

            inline worker_thread(const worker_thread&) = delete;
            inline worker_thread& operator = (const worker_thread&) = delete;
            inline worker_thread(worker_thread&&) = delete;
            inline worker_thread& operator = (worker_thread&&) = delete;
#pragma endregion

            

#pragma region Methods
        private:
            void main_loop();

        public:
            /**
             *  Starts the worker thread
             */
            void start();

            /**
             *  Waits the pac_thread done.
             */
            inline void join() {

                if (index_ == 0) {



                }
                else {

                    pac_thread_.wait();

                }

            }

            /**
             *  Schedules a job to be run in this thread.
             */
            inline void schedule(job& j) {

                switch (j.priority())
                {
                case job_priority::HIGH:
                    high_job_p_queue_.push(&j);
                    break;
                case job_priority::NORMAL:
                    normal_job_p_queue_.push(&j);
                    break;
                case job_priority::LOW:
                    low_job_p_queue_.push(&j);
                    break;
                default:
                    break;
                }

            }
#pragma endregion

        };

    }

}