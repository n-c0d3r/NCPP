#include <ncpp/ncpp.hpp>



namespace ncpp {

    application::application(const application_settings& settings) :
        settings_(settings)
    {

        mem::init(settings.mem_settings);

        job_system::system::init_and_start(settings.job_system_settings);

    }
    application::~application() {



    }



    void application::init_and_start(const application_settings& settings) {

        create_instance_t(settings);

    }
    void application::release() {

        release_instance();

    }

}