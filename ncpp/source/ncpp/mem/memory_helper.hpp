#pragma once

/** @file ncpp/mem/memory_helper.hpp
*	@brief Implements memory helper.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/mem/memory_counting.hpp>

#pragma endregion



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

    namespace mem {

        inline constexpr sz aligned_size(sz size, size_t align = EASTL_ALLOCATOR_MIN_ALIGNMENT)
        {
            const size_t mask = align - 1;

            return (size + mask) & ~mask;
        }

        inline uintptr_t align_address(uintptr_t addr, size_t align = EASTL_ALLOCATOR_MIN_ALIGNMENT)
        {
            const size_t mask = align - 1;
            assert((align & mask) == 0); // pwr of 2
            return (addr + mask) & ~mask;
        }



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
        *  A class template providing functionalities for memory management with the capabilities of choosing the size for both non-aligned, aligned allocation, and the pointer for deallocation.
        *  To use this feature, look at the implement of default_memory_helper.
        * 
        *  @param <memory_helper> the class that implements memory_helper_t.
        *  @param <is_all_usable__> if enabled, all the allocated memory size will be added into total allocated memory count when memory counting enabled.
        *  @param <F_additional_args__...> types of additional arguments need to pass into when allocating or deallocating.
        */
        template<class F_memory_helper__, b8 is_all_usable__, typename... F_additional_args__>
        class TF_memory_helper {

    #if !defined(NDEBUG) || defined(NCPP_ENABLE_MEMORY_COUNTING)
    #define HAS_DATA_OFFSET 1
    #else
    #define HAS_DATA_OFFSET 0
    #endif



        public:
            static inline sz predict_actual_size(size_t size) {

                sz actual_size = size + 1;

    #ifndef NDEBUG
                actual_size += sizeof(const char*);
    #endif
    #ifdef NCPP_ENABLE_MEMORY_COUNTING
                if(is_all_usable__)
                    actual_size += sizeof(sz);
    #endif

                return actual_size;
            }
            static inline sz predict_actual_size(size_t size, sz alignment) {

                sz actual_size = size + 1 + alignment;

    #ifndef NDEBUG
                actual_size += sizeof(const char*);
    #endif
    #ifdef NCPP_ENABLE_MEMORY_COUNTING
                if(is_all_usable__)
                    actual_size += sizeof(sz);
    #endif

                return actual_size;
            }

            static inline void* allocate(size_t size, const char* pName, int flags, F_additional_args__... additional_args)
            {

                return allocate(size, EASTL_ALLOCATOR_MIN_ALIGNMENT, 0, pName, flags, std::forward<F_additional_args__>(additional_args)...);
            }

            static void* allocate(size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, F_additional_args__... additional_args)
            {

                //  Memory Layout:
                //  
                //  [shifted bytes] 
                //  const char* name //debug only
                //  sz size //if memory counting enabled
                //  [data]
                //

                // setup offsets
    #if HAS_DATA_OFFSET == 1
                sz data_offset = 0;
    #endif



    #ifndef NDEBUG
                data_offset += sizeof(const char*);
                sz name_p_offset = data_offset + 1;
    #endif
    #ifdef NCPP_ENABLE_MEMORY_COUNTING
                if(is_all_usable__)
                    data_offset += sizeof(sz);

                sz size_offset = data_offset + 1;
    #endif



    #if HAS_DATA_OFFSET == 1
                sz actual_size = alignment + alignmentOffset + data_offset + size;
    #else
                sz actual_size = alignment + alignmentOffset + size;
    #endif



                // malloc memory
                u8* raw_p = reinterpret_cast<u8*>(F_memory_helper__::new_mem(actual_size, std::forward<F_additional_args__>(additional_args)...));



    #if HAS_DATA_OFFSET == 1
                // align pointer
                sz actual_alignment_offset = alignmentOffset + data_offset;

                u8* result_p = reinterpret_cast<u8*>(
                    align_address(
                        reinterpret_cast<uintptr_t>(reinterpret_cast<u8*>(raw_p) + actual_alignment_offset),
                        alignment
                    )
                ) - actual_alignment_offset;
    #else
                // align pointer
                u8* result_p = reinterpret_cast<u8*>(
                    align_address(
                        reinterpret_cast<uintptr_t>(reinterpret_cast<u8*>(raw_p) + alignmentOffset),
                        alignment
                    )
                    ) - alignmentOffset;
    #endif

                if (result_p == raw_p)
                    result_p += alignment;



                // save shifted bytes info
                u8 shift = (result_p - raw_p - 1) & 0xFF;



    #if HAS_DATA_OFFSET == 1
                // goto data pointer
                result_p += data_offset;
    #endif



                // save the shift value
                *(result_p - 1) = shift;



    #ifndef NDEBUG
                *reinterpret_cast<const char**>(result_p - name_p_offset) = pName;
    #endif
    #ifdef NCPP_ENABLE_MEMORY_COUNTING
                if(is_all_usable__){

                    *reinterpret_cast<sz*>(result_p - size_offset) = actual_size;

                    NCPP_INCREASE_TOTAL_ALLOCATED_MEMORY(actual_size);

                }
    #endif



                return result_p;
            }



            static void deallocate(void* ptr, F_additional_args__... additional_args)
            {

    #if HAS_DATA_OFFSET == 1
                sz data_offset = 0;
    #endif

    #ifndef NDEBUG
                data_offset += sizeof(const char*);
                sz name_p_offset = data_offset + 1;
    #endif
    #ifdef NCPP_ENABLE_MEMORY_COUNTING
                if(is_all_usable__)
                    data_offset += sizeof(sz);

                sz size_offset = data_offset + 1;

                if (is_all_usable__)
                    NCPP_DECREASE_TOTAL_ALLOCATED_MEMORY(*reinterpret_cast<sz*>(reinterpret_cast<u8*>(ptr) - size_offset));
    #endif

                u8 shift = *(reinterpret_cast<u8*>(ptr) - 1);

    #if HAS_DATA_OFFSET == 1
                F_memory_helper__::delete_mem(reinterpret_cast<u8*>(ptr) - data_offset - shift - 1, std::forward<F_additional_args__>(additional_args)...);
    #else
                F_memory_helper__::delete_mem(reinterpret_cast<u8*>(ptr) - shift - 1, std::forward<F_additional_args__>(additional_args)...);
    #endif

            }



    #undef HAS_DATA_OFFSET

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
        *  A memory helper that implements new_mem(sz) with malloc(sz) and delete_mem(void*) with free(void*); 
        */
        class F_default_memory_helper :
            public TF_memory_helper<F_default_memory_helper, true>
        {

        public:
            static inline void* new_mem(sz size) {

                return malloc(size);
            }

            static inline void delete_mem(void* ptr) {

                free(ptr);
            }

        };

    }

}

