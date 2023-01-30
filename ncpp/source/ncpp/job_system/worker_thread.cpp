#include <ncpp/ncpp.hpp>



namespace ncpp {

    namespace job_system {

        worker_thread::worker_thread(uint32_t index) :
            index_(index)
        {

            if (index_ != 0) {

                std::thread std_thread = std::thread(
                    [](worker_thread* worker_thread) {

                        worker_thread->loop();

                    },
                    this
                );

                std_thread.swap(std_thread_);

            }

        }
        worker_thread::~worker_thread() {



        }

        void worker_thread::loop() {

            while (!system::instance_p()->is_running());

            while (system::instance_p()->is_running()) {

                std::cout << (uint64_t)mem::instance_p()->memory_usage() << std::endl;

            }

        }
        void worker_thread::join() {

            std_thread_.join();

        }

    }

}