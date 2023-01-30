#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>



namespace ncpp {

    namespace job_system {

        class job_system :
            singleton_t<job_system>
        {

#pragma region Nested Types
        public:
            struct settings_type {

                uint32_t worker_thread_count = std::thread::hardware_concurrency();

                uint32_t coroutine_per_worker_thread = 128;

            };
#pragma endregion



#pragma region Properties
        public:
            const settings_type settings_;
#pragma endregion



#pragma region Getters and Setters
        public:
            NCPP_GETTER(const settings_type& settings()) const { return settings_; };
#pragma endregion



#pragma region Constructors and Destructor
        public:
            job_system(const settings_type& settings);
            ~job_system();
#pragma endregion

        };

    }

}



#include <ncpp/job_system/coroutine.hpp>
#include <ncpp/job_system/job.hpp>



namespace ncpp {

    namespace job_system {



    }

}