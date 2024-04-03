#include <ncpp/object.hpp>



namespace ncpp::internal {

    TF_default_object_manager<false> default_object_manager;
    TF_default_object_manager<true> default_object_manager_thread_safe(std::thread::hardware_concurrency());

}