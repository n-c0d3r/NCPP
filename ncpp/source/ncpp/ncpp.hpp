#pragma once

namespace ncpp {



}



#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/mem.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>
#include <ncpp/job_system/job_system.hpp>
#include <ncpp/ecs/ecs.hpp>
#include <ncpp/rttr/rttr.hpp>



namespace ncpp {

    struct application_settings {

        job_system::system_settings job_system_settings;
        ::ncpp::mem_settings mem_settings;

    };



    class application :
        public protected_singleton_t<application>
    {

#pragma region Friend Classes
    public:
        friend class protected_singleton_t<application>;
#pragma endregion



#pragma region Properties
    public:
        const application_settings settings_;
#pragma endregion



#pragma region Getters and Setters
    public:
        NCPP_GETTER(const application_settings& settings()) const { return settings_; }
#pragma endregion



#pragma region Constructors and Destructor
    private:
        application(const application_settings& settings);
        ~application();
#pragma endregion



#pragma region Methods
    public:
        static void init_and_start(const application_settings& settings);
        static void release();
#pragma endregion

    };

}