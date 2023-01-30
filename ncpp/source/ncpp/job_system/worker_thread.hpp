#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>



namespace ncpp {

    namespace job_system {

        class worker_thread
        {

#pragma region Typedefs
        public:
            static constexpr const uint32_t coroutine_count_per_worker_thread = NCPP_JOB_SYSTEM_COROUTINE_COUNT_PER_WORKER_THREAD;
#pragma endregion



#pragma region Properties
        private:
            uint32_t coroutine_count_;
            uint32_t index_;
            std::thread std_thread_;
            
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_GETTER(uint32_t coroutine_count()) const { return coroutine_count_; };
            NCPP_GETTER(uint32_t index()) const { return index_; };
            NCPP_GETTER(std::thread& std_thread()) { return std_thread_; };
            NCPP_GETTER(const std::thread& std_thread()) const { return std_thread_; };
#pragma endregion



#pragma region Constructors and Destructor
        public:
            worker_thread(uint32_t index);
            ~worker_thread();
#pragma endregion



#pragma region Methods
        public:
            void loop();
            void join();
#pragma endregion

        };

    }

}