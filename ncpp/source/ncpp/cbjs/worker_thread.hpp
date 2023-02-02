#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/coroutine.hpp>



namespace ncpp {

    namespace cbjs {

        struct job;
        class coroutine;



        /**
         *  Manages things working on a thread.
         *  Its contain a fiber, a coroutine pool, coroutine pointer queues and job pointer queues.
         */
        class NCPP_DEFAULT_ALIGN worker_thread final
        {

        public:
            using job_p_queue_type = typename containers::fixed_vector_queue_t<job*>;
            using job_p_queue_array_type = typename std::array<job_p_queue_type, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;
            using job_p_queue_lock_array_type = typename std::array<pac::spinlock, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;
            using coroutine_p_queue_type = typename containers::fixed_vector_queue_t<coroutine*>;
            using coroutine_p_queue_array_type = typename std::array<coroutine_p_queue_type, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;



        private:
            /**
             *  The worker thread index.
             *  0 is the main worker thread.
             */
            uint32_t index_;

            /**
             *  The thread from the C++ STL.
             */
            std::thread std_thread_;

            /**
             *  Each job_p_queue has a priority.
             *  The capacity of job_p_queue_array_ is the priority count.
             */
            job_p_queue_array_type job_p_queue_array_;
            /**
             *  Each job_p_queue_lock has a priority.
             *  The capacity of job_p_queue_lock_array_ is the priority count.
             */
            job_p_queue_lock_array_type job_p_queue_lock_array_;

            /**
             *  Each coroutine_p_queue has a priority.
             *  The capacity of coroutine_p_queue_array_ is the priority count.
             */
            coroutine_p_queue_array_type coroutine_p_queue_array_;

            /**
             *  This thread's fiber.
             */
            std::unique_ptr<pac::fiber> fiber_p_;

            /**
             *  This thread's coroutine pool pointer.
             */
            std::unique_ptr<coroutine_pool> coroutine_pool_p_;



        public:
            inline uint32_t index() const { return index_; }

            inline std::thread& std_thread() { return std_thread_; }
            inline const std::thread& std_thread() const { return std_thread_; }

            inline pac::fiber& fiber() { return *fiber_p_; }
            inline const pac::fiber& fiber() const { return *fiber_p_; }

            inline coroutine_pool& get_coroutine_pool() { return *coroutine_pool_p_; }
            inline const coroutine_pool& get_coroutine_pool() const { return *coroutine_pool_p_; }



        public:
            worker_thread(uint32_t index);
            ~worker_thread();



        public:
            /**
             *  Starting the worker thread.
             *  Automatically creating a new thread if not main worker thread.
             */
            void start();
            /**
             *  Joining the C++ STL thread.
             */
            void join();
            /**
             *  The main worker loop.
             */
            void loop();

            /**
             *  Scheduling a job to be run on this thread.
             */
            void schedule(job& j);

        };

    }

}