#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>



namespace ncpp {

    namespace cbjs {

        class coroutine;
        class worker_thread;
        class system;



        /**
         *  Be a function, and also storing job's informations (priority, is_done,...).
         *  Can be allocated in the stack and owned by a coroutine after scheduled.
         */
        struct NCPP_DEFAULT_ALIGN job {

        public:
            friend class system;
            friend class worker_thread;
            friend class coroutine;



        public:
            /**
             *  The main function type.
             *  @param job 
             *  @param coroutine
             *  @return void
             */
            using functor_type = std::function<void(job& j, coroutine& c)>;



        public:
            /**
             *  The main function of the job.
             */
            functor_type functor;
            /**
             *  Storing the priority of the job when scheduling.
             *  The strongest value is 0 (the highest priority). 
             */
            uint16_t priority = 0;

            bool is_done = 0;



        public:
            /**
             *  Resetting the states to be kicked again.
             */
            inline void reset() {

                is_done = false;
            }

        };

    }

}