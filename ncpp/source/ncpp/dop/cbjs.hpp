#pragma once

/**
 *  @file ncpp/dop/cbjs.hpp
 *  @brief Implements coroutine based job system.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>

#include <ncpp/dop/job.hpp>
#include <ncpp/dop/coroutine.hpp>
#include <ncpp/dop/worker_thread.hpp>



namespace ncpp {

	namespace dop {

        struct NCPP_DEFAULT_ALIGNAS coroutine;
        struct NCPP_DEFAULT_ALIGNAS job;
        class NCPP_DEFAULT_ALIGNAS cbjs;
        class NCPP_DEFAULT_ALIGNAS worker_thread;



        /**
         *  Specifies cbjs settings.
         */
        struct NCPP_DEFAULT_ALIGNAS cbjs_settings {

            job& entry_job = null_reference_t<job>();
            u8 worker_thread_count = pac::hardware_concurrency();
            u32 tagged_heap_capacity = 32;

        };

        

        /**
         *  The main class of cbjs (Coroutine based job system)
         */
        class NCPP_DEFAULT_ALIGNAS cbjs :
            public utilities::singleton_t<cbjs>
        {

        public:
            friend class worker_thread;



#pragma region Properties
        private:
            cbjs_settings settings_;
            std::atomic_bool is_running_;

            /**
             *  The main tagged heap of cbjs.
             *  Queues, Vectors,... will be stored in this object.
             */
            tagged_heap_t<> tagged_heap_;
            /**
             *  The id of the tagged heap category that is only deallocated when cbjs released. 
             */
            tagged_heap_t<>::category_id_type tgh_forever_cid_;

            std::array<std::unique_ptr<worker_thread>, 64> worker_threads_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline const cbjs_settings& settings() const { return settings_; }
            inline bool is_running() const { return is_running_; }

            inline tagged_heap_t<>& tagged_heap() { return tagged_heap_; }
            inline const tagged_heap_t<>& tagged_heap() const { return tagged_heap_; }

            inline tagged_heap_t<>::category_id_type tgh_forever_cid() const { return tgh_forever_cid_; }

            inline worker_thread& get_worker_thread(u8 i) { return *worker_threads_[i]; }
            inline const worker_thread& get_worker_thread(u8 i) const { return *worker_threads_[i]; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline cbjs(const cbjs_settings& settings) :
                settings_(settings),
                is_running_(0),
                tagged_heap_(settings.tagged_heap_capacity),
                tgh_forever_cid_(tagged_heap_.create_category())
            {

                start();
                join();

            }
            /**
             *  Destructor
             */
            ~cbjs() {



            }

            inline cbjs(const cbjs&) = delete;
            inline cbjs& operator = (const cbjs&) = delete;
            inline cbjs(cbjs&&) = delete;
            inline cbjs& operator = (cbjs&&) = delete;
#pragma endregion



#pragma region Methods
        private:
            /**
             *  Starts the job system
             */
            inline void start() {

                is_running_.store(1, std::memory_order_release);

                for (u8 i = 1; i < settings_.worker_thread_count; ++i) {

                    worker_threads_[i] = std::make_unique<worker_thread>(i);

                }
                worker_threads_[0] = std::make_unique<worker_thread>(0);

                for (u8 i = 1; i < settings_.worker_thread_count; ++i) {

                    worker_threads_[i]->start();

                }
                worker_threads_[0]->start();

            }
            /**
             *  Waits all worker threads done
             */
            inline void join() {

                for (u8 i = 1; i < settings_.worker_thread_count; ++i) {

                    worker_threads_[i]->join();

                }

            }

            /**
             *  Requests the job system to stop
             */
            inline void request_stop() {

                is_running_.store(0, std::memory_order_release);
            }
#pragma endregion

        };

	}

}