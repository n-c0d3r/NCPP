#include <ncpp/ncpp.hpp>



namespace ncpp {

#ifdef NCPP_MEM_ANALYZE
    std::atomic_uint64_t mem::memory_usage_ = 0;
#endif



    mem::mem(const mem_settings& settings) :
        settings_(settings)
    {



    }
    mem::~mem() {



    }



    void mem::init(const mem_settings& settings) {

        create_instance_t(settings);

    }
    void mem::release() {

        release_instance();

    }

#ifdef NCPP_MEM_ANALYZE
    inline void mem::increase_memory_usage(size_t size) {

        memory_usage_.fetch_add(size, std::memory_order_release);

    }
    inline void mem::decrease_memory_usage(size_t size) {

        memory_usage_.fetch_add(-size, std::memory_order_release);

    }
#endif

}