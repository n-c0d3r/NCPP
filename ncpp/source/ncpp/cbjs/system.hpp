#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/cbjs/coroutine.hpp>



namespace ncpp {

    namespace cbjs {

        class worker_thread;
        struct job;



        /**
         *  Storing the settings to create job system.  
         */
        struct NCPP_DEFAULT_ALIGN system_settings {

            /**
             *  The job to be kicked first.
             *  The job system will stop when the entry job done.
             */
            job& entry_job;
            uint32_t worker_thread_count = std::thread::hardware_concurrency();
            uint32_t job_queue_capacity = NCPP_DEFAULT_JOB_QUEUE_CAPACITY;
            uint32_t coroutine_count_per_worker_thread = NCPP_DEFAULT_COROUTINE_COUNT_PER_WORKER_THREAD;

        };



        /**
         *  Managing worker threads and overall states.
         *  To initialize cbjs, we need to create the job system and run it. 
         */
        class NCPP_DEFAULT_ALIGN system final :
            public utilities::singleton_t<system>
        {

        public:
            friend class worker_thread;



        private:
            const system_settings settings_;

            std::vector<std::unique_ptr<cbjs::worker_thread>> worker_thread_vector_;

            std::atomic_bool is_running_;

            pac::semaphore ready_semaphore_;



        public:
            inline const system_settings& settings() const { return settings_; }

            inline cbjs::worker_thread& worker_thread(uint32_t index) { return *(worker_thread_vector_.at(index)); }
            inline const cbjs::worker_thread& worker_thread(uint32_t index) const { return *(worker_thread_vector_.at(index)); }

            inline bool is_running() const { return is_running_.load(std::memory_order_acquire); };

            inline pac::semaphore& ready_semaphore() { return ready_semaphore_; }
            inline const pac::semaphore& ready_semaphore() const { return ready_semaphore_; }



        public:
            system(const system_settings& settings);
            ~system();



        public:
            /**
             *  Starting the job system
             */
            void start();

        private:
            /**
             *  Requesting job system to stop, can be used by the main worker thread.
             */
            void request_stop();
            /**
             *  Waiting worker threads done.
             */
            void join();

        };

    }

}