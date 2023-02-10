#pragma once

/**
 *  @file ncpp/dop/job.hpp
 *  @brief Implements job.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

	namespace dop {

        struct NCPP_DEFAULT_ALIGNAS coroutine;
        struct NCPP_DEFAULT_ALIGNAS job;
        class NCPP_DEFAULT_ALIGNAS cbjs;
        class NCPP_DEFAULT_ALIGNAS worker_thread;



        /**
         *  Indicate the priority of job.
         */
        enum class job_priority {

            HIGH = 0,
            NORMAL = 1,
            LOW = 2

        };



        /**
         *  A job is a section of program that can be scheduled to run in a worker thread.
         */
        struct NCPP_DEFAULT_ALIGNAS job {

#pragma region Typedefs
        public:
            using functor_type = std::function<void(coroutine&)>;
#pragma endregion



#pragma region Properties
        private:
            std::atomic_bool is_done_;
            functor_type functor_;
            job_priority priority_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline b8 is_done() const { return is_done_.load(std::memory_order_acquire); }
            inline job_priority priority() const { return priority_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Initialization constructor
             */
            inline job(functor_type&& functor, job_priority priority = job_priority::HIGH) :
                functor_(std::move(functor)),
                is_done_(0),
                priority_(priority)
            {



            }
            /**
             *  Default constructor.
             *  This constructor will construct an empty job.
             */
            inline job() :
                functor_(),
                is_done_(0),
                priority_(job_priority::HIGH)
            {



            }
            /**
             *  Destructor
             */
            ~job() {



            }
#pragma endregion



#pragma region Methods
        public:
            /**
             *  Executes the job to run inside a coroutine
             */
            inline void execute(coroutine& c) {

                reset();

                functor_(c);

                is_done_.store(1, std::memory_order_release);

            }
            /**
             *  Resets the job to be able to run again.
             */
            inline void reset() {

                is_done_.store(0, std::memory_order_release);
            }
#pragma endregion

        };

	}

}