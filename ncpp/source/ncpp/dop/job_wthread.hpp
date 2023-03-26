#pragma once

/**
 *  @file ncpp/dop/job.hpp
 *  @brief Implements job.
 */



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/dop/tgh.hpp>

#pragma endregion



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

        class job_system;
        class job_wthread;
        class job_wthread_scheduler;
        class job_instance;
        class job_instance_pool;
        struct job;
        struct job_handle;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        extern job_wthread& current_wthread();
        extern stack_heap_t<>& current_stack_heap_LARGE();
        extern stack_heap_t<>& current_stack_heap_NORMAL();
        extern stack_heap_t<>& current_stack_heap_SMALL();



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        class job_wthread final {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            friend class job_system;
            friend class job_wthread;
            friend class job_wthread_scheduler;
            friend class job_instance;
            friend class job_instance_pool;
            friend struct job;
            friend struct job_handle;
            friend job_handle& dop::schedule_job(job& j);

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using job_instance_ref_queue_type = tgh_fv_queue_t<utilities::lref_t<job_instance>>;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            u8 index_;
            u32 job_handle_queue_capacity_;
            u32 job_instance_pool_capacity_;

            utilities::lref_t<pac::thread> pac_thread_ref_;

            utilities::lref_t<job_instance_pool> job_instance_pool_ref_;

            utilities::lref_t<job_wthread_scheduler> scheduler_ref_;

            job_instance_ref_queue_type job_instance_ref_queue_;

            sz stack_heap_LARGE_stack_capacity_;
            sz stack_heap_LARGE_stack_count_;
            sz stack_heap_NORMAL_stack_capacity_;
            sz stack_heap_NORMAL_stack_count_;
            sz stack_heap_SMALL_stack_capacity_;
            sz stack_heap_SMALL_stack_count_;

            stack_heap_t<> stack_heap_LARGE_;
            stack_heap_t<> stack_heap_NORMAL_;
            stack_heap_t<> stack_heap_SMALL_;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline u8 index() const { return index_; }
            inline u32 job_handle_queue_capacity() const { return job_handle_queue_capacity_; }
            inline u32 job_instance_pool_capacity() const { return job_instance_pool_capacity_; }

            inline sz stack_heap_LARGE_stack_capacity() { return stack_heap_LARGE_stack_capacity_; }
            inline sz stack_heap_LARGE_stack_count() { return stack_heap_LARGE_stack_count_; }
            inline sz stack_heap_NORMAL_stack_capacity() { return stack_heap_NORMAL_stack_capacity_; }
            inline sz stack_heap_NORMAL_stack_count() { return stack_heap_NORMAL_stack_count_; }
            inline sz stack_heap_SMALL_stack_capacity() { return stack_heap_SMALL_stack_capacity_; }
            inline sz stack_heap_SMALL_stack_count() { return stack_heap_SMALL_stack_count_; }

            inline stack_heap_t<>& stack_heap_LARGE() { return stack_heap_LARGE_; }
            inline stack_heap_t<>& stack_heap_NORMAL() { return stack_heap_NORMAL_; }
            inline stack_heap_t<>& stack_heap_SMALL() { return stack_heap_SMALL_; }

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            job_wthread(
                u8 index,
                u32 job_handle_queue_capacity = NCPP_DEFAULT_JOB_HANDLE_QUEUE_CAPACITY,
                u32 job_instance_pool_capacity = NCPP_DEFAULT_JOB_INSTANCE_POOL_CAPACITY,

                sz stack_heap_LARGE_stack_capacity = NCPP_DEFAULT_STACK_HEAP_STACK_CAPACITY_LARGE,
                sz stack_heap_LARGE_stack_count = NCPP_DEFAULT_STACK_COUNT_PER_CHUNK_LARGE,
                sz stack_heap_NORMAL_stack_capacity = NCPP_DEFAULT_STACK_HEAP_STACK_CAPACITY_NORMAL,
                sz stack_heap_NORMAL_stack_count = NCPP_DEFAULT_STACK_COUNT_PER_CHUNK_NORMAL,
                sz stack_heap_SMALL_stack_capacity = NCPP_DEFAULT_STACK_HEAP_STACK_CAPACITY_SMALL,
                sz stack_heap_SMALL_stack_count = NCPP_DEFAULT_STACK_COUNT_PER_CHUNK_SMALL
            );
            ~job_wthread();

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            void worker_loop();

            void init();

            bool try_make_job_instance(job_handle& handle);

            void process_job_handles();
            void process_job_instances();

            job_handle& schedule(job& j);



        public:
            void run();
            void wait();

        };

    }

}