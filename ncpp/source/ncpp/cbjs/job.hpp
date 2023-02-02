#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>



namespace ncpp {

    namespace cbjs {

        class coroutine;
        class worker_thread;
        class system;



        struct NCPP_DEFAULT_ALIGN job {

        public:
            friend class system;
            friend class worker_thread;
            friend class coroutine;



        public:
            using functor_type = std::function<void(job& j, coroutine& c)>;



        public:
            functor_type functor;
            uint16_t priority = 0;

            bool is_done = 0;



        public:
            inline void reset() {

                is_done = false;
            }

        };

    }

}