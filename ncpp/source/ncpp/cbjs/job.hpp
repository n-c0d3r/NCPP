#pragma once

/** @file ncpp/cbjs/job.hpp
*	@brief Implements cbjs job.
*/



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
         *  Usually allocated in the stack and owned by a coroutine after scheduling.
         */
        struct NCPP_DEFAULT_SET_ALIGN job {

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
             *  Stores the priority of the job when scheduling.
             *  The strongest value is 0 (the highest priority). 
             */
            u8 priority = 0;

            b8 is_done = 0;



        public:
            /**
             *  Resets the states to be kicked again.
             */
            inline void reset() {

                is_done = false;
            }

        };

    }

}