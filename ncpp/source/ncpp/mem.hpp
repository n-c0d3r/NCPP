#pragma once

#include <ncpp/utilities.hpp>
#include <ncpp/parallelism_and_concurrency/spin_lock.hpp>


namespace ncpp {

#define NCPP_ALLOCATION_FLAG 0x1F4354C65D0L

    struct NCPP_DEFAULT_ALIGN allocation_desc {

        size_t size = sizeof(allocation_desc);
        size_t flag;

    };



    struct mem_settings {



    };



    class mem :
        public protected_singleton_t<mem>
    {
    
#pragma region Friend Classes
    public:
        friend class protected_singleton_t<mem>;
#pragma endregion



#pragma region Properties
    private:
        const mem_settings settings_;

#ifdef NCPP_MEM_ANALYZE
        static std::atomic_uint64_t memory_usage_;
#endif
#pragma endregion



#pragma region Getters and Setters
    public:
        NCPP_GETTER(const mem_settings& settings()) const { return settings_; }

#ifdef NCPP_MEM_ANALYZE
        static NCPP_GETTER(uint64_t memory_usage()) { return memory_usage_.load(std::memory_order_acquire); }
#endif
#pragma endregion



#pragma region Constructors and Destructor
    private:
        mem(const mem_settings& settings);
        ~mem();
#pragma endregion



#pragma region Methods
    public:
        static void init(const mem_settings& settings);
        static void release();

    private:
#ifdef NCPP_MEM_ANALYZE
        static inline void increase_memory_usage(size_t size);
        static inline void decrease_memory_usage(size_t size);
#endif



    public:
        static inline constexpr uintptr_t aligned_address(uintptr_t addr, size_t align)
        {
            const size_t mask = align - 1;
            assert((align & mask) == 0); // pwr of 2
            return (addr + mask) & ~mask;
        }
        template<typename data_type>
        static inline data_type* aligned_pointer_t(data_type* ptr, size_t align) {

            const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
            const uintptr_t addrAligned = aligned_address(addr, align);
            return reinterpret_cast<data_type*>(addrAligned);
        }
        static inline void* aligned_alloc(size_t align, size_t bytes) {

            size_t actualBytes = bytes + 256 + align;

            unsigned char* pRawMem = (unsigned char*)malloc(actualBytes);

            unsigned char* pAlignedMem = aligned_pointer_t(pRawMem, align);
            if (pAlignedMem == pRawMem)
                pAlignedMem += align;

            ptrdiff_t shift = pAlignedMem - pRawMem;
            assert(shift > 0 && shift <= 256);

            pAlignedMem[-1] = static_cast<unsigned char>(shift & 0xFF);



            pAlignedMem += 256;



            allocation_desc* alloc_desc_p = (allocation_desc*)pAlignedMem - 1;

            alloc_desc_p->flag = NCPP_ALLOCATION_FLAG;
            alloc_desc_p->size = actualBytes;

#ifdef NCPP_MEM_ANALYZE
            increase_memory_usage(alloc_desc_p->size);
#endif



            return pAlignedMem;
        }
        static inline void aligned_free(void* pMem)
        {


            unsigned char* pAlignedMem = reinterpret_cast<unsigned char*>(pMem);



            allocation_desc* alloc_desc_p = (allocation_desc*)pAlignedMem - 1;

            assert(alloc_desc_p->flag == NCPP_ALLOCATION_FLAG && "invalid allocation");

#ifdef NCPP_MEM_ANALYZE
            decrease_memory_usage(alloc_desc_p->size);
#endif



            pAlignedMem -= 256;



            ptrdiff_t shift = pAlignedMem[-1];
            if (shift == 0)
                shift = 256;

            unsigned char* pRawMem = pAlignedMem - shift;
            free(pRawMem);
        }

#pragma endregion
    
    };

}




inline void* operator new (size_t size) {

    return ncpp::mem::aligned_alloc(NCPP_DEFAULT_ALIGNMENT, size);
}
inline void operator delete (void* ptr) {

    ncpp::allocation_desc* real_ptr = (ncpp::allocation_desc*)ptr - 1;

    if (real_ptr->flag == NCPP_ALLOCATION_FLAG) {

        ncpp::mem::aligned_free(ptr);

    }
    else {

        free(ptr);

    }

}
