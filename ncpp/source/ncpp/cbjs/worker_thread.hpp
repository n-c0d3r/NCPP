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



        class NCPP_DEFAULT_ALIGN worker_thread final
        {

        public:
            using job_p_queue_type = typename containers::fixed_vector_queue_t<job*>;
            using job_p_queue_array_type = typename std::array<job_p_queue_type, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;
            using job_p_queue_lock_array_type = typename std::array<pac::spinlock, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;
            using coroutine_p_queue_type = typename containers::fixed_vector_queue_t<coroutine*>;
            using coroutine_p_queue_array_type = typename std::array<coroutine_p_queue_type, NCPP_DEFAULT_JOB_PRIORITY_COUNT>;



        private:
            uint32_t index_;

            std::thread std_thread_;

            job_p_queue_array_type job_p_queue_array_;
            job_p_queue_lock_array_type job_p_queue_lock_array_;

            coroutine_p_queue_array_type coroutine_p_queue_array_;

            std::unique_ptr<pac::fiber> fiber_p_;

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
            void start();
            void join();
            void loop();

            void schedule(job& j);

        };

    }

}