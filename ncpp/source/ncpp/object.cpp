#include <ncpp/object.hpp>



NCPP_DEFINE_SINGLETON(ncpp::TF_default_object_storage<true>);
NCPP_DEFINE_SINGLETON(ncpp::TF_default_object_storage<false>);



namespace ncpp {

    TF_default_object_storage<true> default_object_storage(std::thread::hardware_concurrency());
    TF_default_object_storage<false> default_object_storage_no_thread_safe;

}