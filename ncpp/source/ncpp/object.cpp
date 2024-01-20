#include <ncpp/object.hpp>



NCPP_DEFINE_SINGLETON(ncpp::TF_default_object_manager<true>);
NCPP_DEFINE_SINGLETON(ncpp::TF_default_object_manager<false>);



namespace ncpp::internal {

    TF_default_object_manager<true> default_object_manager(std::thread::hardware_concurrency());
    TF_default_object_manager<false> default_object_manager_thread_safe;

}