#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>



namespace ncpp {

    namespace parallelism_and_concurrency {

        class spin_lock {

        private:
            std::atomic_flag m;



        public:
            spin_lock()
            {



            }
            ~spin_lock() {



            }

            void lock() {

                while (!m.test_and_set(std::memory_order_acquire));

            }
            void unlock() {

                m.clear(std::memory_order_release);

            }

        };

    }

}