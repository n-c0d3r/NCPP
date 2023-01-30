#include <ncpp/ncpp.hpp>



namespace ncpp {

    namespace job_system {

        system::system(const system_settings& settings) :
            settings_(settings),
            is_running_(false)
        {

            assert(settings_.worker_thread_count > 0 && "worker thread count must be greater than 0.");

            create_worker_threads();

            start_worker_threads();

        }
        system::~system() {

            join_worker_threads();

        }



        void system::create_worker_threads() {

            worker_thread_p_vector_.resize(settings_.worker_thread_count);

            for (uint32_t i = 0; i < settings_.worker_thread_count; ++i) {

                worker_thread_p_vector_[i] = std::make_shared<worker_thread>(i);

                worker_thread_id_to_index_map_[worker_thread_p_vector_[i]->std_thread().get_id()] = i;
                worker_thread_index_to_id_map_[i] = worker_thread_p_vector_[i]->std_thread().get_id();

            }

        }
        void system::start_worker_threads() {

            is_running_.store(true, std::memory_order_release);

            worker_thread_p_vector_[0]->loop();

            join_worker_threads();

        }
        void system::join_worker_threads() {

            for (uint32_t i = 1; i < settings_.worker_thread_count; ++i) {

                worker_thread_p_vector_[i]->join();

            }

        }

        void system::internal_request_stop() {

            is_running_.store(false, std::memory_order_release);

        }



        void system::init_and_start(const system_settings& settings) {

            system::create_instance_t(settings);
            system::release_instance();

        }
        void system::request_stop() {

            instance_p()->internal_request_stop();

        }

    }

}