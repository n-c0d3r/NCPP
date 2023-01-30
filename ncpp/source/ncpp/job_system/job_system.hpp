#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>
#include <ncpp/parallelism_and_concurrency/parallelism_and_concurrency.hpp>

#include <ncpp/job_system/worker_thread.hpp>



namespace ncpp {

    namespace job_system {

        struct system_settings {

            uint32_t worker_thread_count = std::thread::hardware_concurrency();

        };



        class system :
            public protected_singleton_t<system>
        {

#pragma region Friend Classes
        public:
            friend class protected_singleton_t<system>;
#pragma endregion



#pragma region Properties
        private:
            const system_settings settings_;
            std::vector<std::shared_ptr<worker_thread>> worker_thread_p_vector_;
            std::atomic_bool is_running_;
            std::unordered_map<std::thread::id, uint32_t> worker_thread_id_to_index_map_;
            std::unordered_map<uint32_t, std::thread::id> worker_thread_index_to_id_map_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_GETTER(const system_settings& settings()) const { return settings_; }
            NCPP_GETTER(std::vector<std::shared_ptr<worker_thread>>& worker_thread_p_vector()) { return worker_thread_p_vector_; }
            NCPP_GETTER(bool is_running()) { return is_running_.load(std::memory_order_acquire); }
            NCPP_GETTER(uint32_t worker_thread_index(std::thread::id id)) const { return worker_thread_id_to_index_map_.find(id)->second; }
            NCPP_GETTER(std::thread::id worker_thread_id(uint32_t index)) const { return worker_thread_index_to_id_map_.find(index)->second; }
            NCPP_GETTER(std::shared_ptr<worker_thread> get_worker_thread_p(std::thread::id id)) { return worker_thread_p_vector_.at(worker_thread_index(id)); }
            NCPP_GETTER(std::shared_ptr<worker_thread> get_worker_thread_p(std::thread::id id)) const { return worker_thread_p_vector_.at(worker_thread_index(id)); }
            NCPP_GETTER(std::shared_ptr<worker_thread> get_worker_thread_p(uint32_t index)) { return worker_thread_p_vector_.at(index); }
            NCPP_GETTER(std::shared_ptr<worker_thread> get_worker_thread_p(uint32_t index)) const { return worker_thread_p_vector_.at(index); }
#pragma endregion



#pragma region Constructors and Destructor
        private:
            system(const system_settings& settings);
            ~system();
#pragma endregion



#pragma region Methods
        private:
            void create_worker_threads();
            void start_worker_threads();
            void join_worker_threads();

            inline void internal_request_stop();



        public:
            static void init_and_start(const system_settings& settings);
            static void request_stop();
#pragma endregion

        };

    }

}



#include <ncpp/job_system/coroutine.hpp>
#include <ncpp/job_system/job.hpp>
#include <ncpp/job_system/worker_thread.hpp>



namespace ncpp {

    namespace job_system {



    }

}