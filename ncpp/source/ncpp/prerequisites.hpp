#pragma once

/** @file ncpp/prerequisites.hpp
*   @brief The file that is always included on the top.
*
*   Includes stl headers, platform api headers, and defines some macros,...
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



namespace ncpp {}



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Prerequisite Macros

#define NCPP_PRIVATE_KEYWORD private:
#define NCPP_PROTECTED_KEYWORD protected:
#define NCPP_PUBLIC_KEYWORD public:

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#define NCPP_EXPAND(X) X
#define NCPP_GLUE_HELPER(x, y) x##y
#define NCPP_GLUE(x, y) NCPP_GLUE_HELPER(x, y)

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#define NCPP_COMPUTE_VERSION_VALUE(major, minor, patch, max_version_component_value) (major * (max_version_component_value + 1) * (max_version_component_value + 1) + minor * (max_version_component_value + 1) + patch)

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include "ncpp/prerequisite_macros.h"

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



#pragma region Includes

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/version.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/config.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Platform Specific Instruction Extension Headers

#ifdef NCPP_ENABLE_SSE
#include <xmmintrin.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#ifdef NCPP_ENABLE_SSE2
#include <emmintrin.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#ifdef NCPP_ENABLE_SSE3
#include <pmmintrin.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#ifdef NCPP_ENABLE_SSE4
#include <smmintrin.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#if defined(NCPP_ENABLE_AVX) || defined(NCPP_ENABLE_AVX2) || defined(NCPP_ENABLE_FMA3)
#include <immintrin.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#ifdef NCPP_ENABLE_ARM_NEON
#include <arm_neon.h>
#ifndef NCPP_ENABLE_SIMD
    #define NCPP_ENABLE_SIMD
#endif
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region C++ STL Headers
#include <iostream>
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <thread>
#include <atomic>
#include <mutex>
#include <sstream>
#include <functional>
#include <random>
#include <cmath>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <condition_variable>
#include <chrono>
#include <limits>

#include <string.h>

#if _HAS_CXX20
#include <coroutine>
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region EA Headers

#include <ncpp/eastl_headers.hpp>
#include <ncpp/eathread_headers.hpp>

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region C Headers

#include <string.h>

#pragma endregion

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



#pragma region Macros

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region C++ Utilities
#define NCPP_CONSTEXPR NCPP_FORCE_INLINE constexpr
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Alignment utility macros

#if defined(__GNUC__) || defined(__clang__)
#  define NCPP_ALIGN(x) __attribute__ ((aligned(x)))
#elif defined(_MSC_VER)
#  define NCPP_ALIGN(x) __declspec(align(x))
#else
#  error "Unknown compiler; can't define NCPP_ALIGN"
#endif

#if defined(__GNUC__) || defined(__clang__)
#    define NCPP_ALIGNOF(X) __alignof__(X)
#elif defined(_MSC_VER)
#    define NCPP_ALIGNOF(X) __alignof(X)
#else
#  error "Unknown compiler; can't define NCPP_ALIGNOF"
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Implements warning macros

////////////////////////////////////////////////////////////////////////////////////
//  Implement static warning
////////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__)
#define DEPRECATE(foo, msg) foo __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define DEPRECATE(foo, msg) __declspec(deprecated(msg)) foo
#else
#error This compiler is not supported
#endif

#define NCPP_PP_CAT(x,y) NCPP_PP_CAT1(x,y)
#define NCPP_PP_CAT1(x,y) x##y

namespace ncpp {

    namespace NCPP_STATIC_WARNING_helper
    {
        struct true_type {};
        struct false_type {};
        template <int test> struct converter : public true_type {};
        template <> struct converter<0> : public false_type {};
    }

}

#define NCPP_STATIC_WARNING(cond, msg) \
struct NCPP_PP_CAT(NCPP_STATIC_WARNING,__LINE__) { \
  DEPRECATE(void _(::ncpp::NCPP_STATIC_WARNING_helper::false_type const& ),msg) {}; \
  void _(::ncpp::NCPP_STATIC_WARNING_helper::true_type const& ) {}; \
  NCPP_PP_CAT(NCPP_STATIC_WARNING,__LINE__)() {_(ncpp::NCPP_STATIC_WARNING_helper::converter<(cond)>());} \
}

#define NCPP_STATIC_WARNING_template(token, cond, msg) \
    NCPP_STATIC_WARNING(cond, msg) NCPP_PP_CAT(NCPP_PP_CAT(_localvar_, token),__LINE__)

////////////////////////////////////////////////////////////////////////////////////
//  Implement dynamic warning
////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG 
#define NCPP_DEBUG
#define NCPP_WARNING(cond,...) if(!(cond)) {\
        std::cout << "Warning (" << __FILE__ << " at line " << __LINE__ << "):" << std::endl;\
        std::cout << __VA_ARGS__ << std::endl;\
    }
#else
#define NCPP_WARNING(cond,...) ;
#endif

////////////////////////////////////////////////////////////////////////////////////
//  Implement NCPP_TEXT
////////////////////////////////////////////////////////////////////////////////////
#define NCPP_TEXT(CStr) NCPP_GLUE(L, CStr)

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#define NCPP_MP_GROUP(...) __VA_ARGS__

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#ifdef NCPP_ENABLE_SIMD

#if defined(__GNUC__) 
#define NCPP_VECTOR_CALL 
#elif defined(__clang__)
#define NCPP_VECTOR_CALL __vectorcall
#elif defined(_MSC_VER)
#define NCPP_VECTOR_CALL __vectorcall
#endif

#else

#define NCPP_VECTOR_CALL

#endif

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__) || defined(__clang__)
#define NCPP_FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define NCPP_FORCE_INLINE __forceinline
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Primitive type limits

#define NCPP_U64_MAX 0xFFFFFFFFFFFFFFFF
#define NCPP_U64_MIN 0
#define NCPP_U32_MAX 0xFFFFFFFF
#define NCPP_U32_MIN 0
#define NCPP_U16_MAX 0xFFFF
#define NCPP_U16_MIN 0
#define NCPP_U8_MAX 0xFF
#define NCPP_U8_MIN 0

#define NCPP_I64_MAX 0x7FFFFFFFFFFFFFFF
#define NCPP_I64_MIN -0x8000000000000000
#define NCPP_I32_MAX 0x7FFFFFFF
#define NCPP_I32_MIN -0x80000000
#define NCPP_I16_MAX 0x7FFF
#define NCPP_I16_MIN -0x8000
#define NCPP_I8_MAX 0x7F
#define NCPP_I8_MIN -0x80

#define NCPP_F32_MAX eastl::numeric_limits<float>::max();
#define NCPP_F32_MIN eastl::numeric_limits<float>::min();
#define NCPP_F64_MAX eastl::numeric_limits<double>::max();
#define NCPP_F64_MIN eastl::numeric_limits<float>::max();

#pragma endregion

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



#pragma region Typedefs

namespace ncpp {

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    
#pragma region Primitive data types
    /** 8bit unsigned integer. */
    using u8 = uint8_t; 
    /** 16bit unsigned integer. */
    using u16 = uint16_t; 
    /** 32bit unsigned integer. */
    using u32 = uint32_t; 
    /** 64bit unsigned integer. */
    using u64 = uint64_t; 

    /** 8bit signed integer. */
    using i8 = int8_t; 
    /** 16bit signed integer. */
    using i16 = int16_t; 
    /** 32bit signed integer. */
    using i32 = int32_t; 
    /** 64bit signed integer. */
    using i64 = int64_t; 

    /** 32bit floating-point type. */
    using f32 = float_t; 
    /** 64bit floating-point type. */
    using f64 = double_t; 
    
    /** 8bit boolean. */
    using b8 = bool; 

    /** the same as size_t. */
    using sz = size_t;

    /** the same as ptrdiff_t. */
    using ptrd = ptrdiff_t;



    /** 8bit atomic unsigned integer. */
    using au8 = eastl::atomic<u8>;
    /** 16bit atomic unsigned integer. */
    using au16 = eastl::atomic<u16>;
    /** 32bit atomic unsigned integer. */
    using au32 = eastl::atomic<u32>;
    /** 64bit atomic unsigned integer. */
    using au64 = eastl::atomic<u64>;

    /** 8bit atomic signed integer. */
    using ai8 = eastl::atomic<i8>;
    /** 16bit atomic signed integer. */
    using ai16 = eastl::atomic<i16>;
    /** 32bit atomic signed integer. */
    using ai32 = eastl::atomic<i32>;
    /** 64bit atomic signed integer. */
    using ai64 = eastl::atomic<i64>;

    /** 32bit atomic floating-point type. */
    using af32 = eastl::atomic<float_t>;
    /** 64bit atomic floating-point type. */
    using af64 = eastl::atomic<double_t>;

    /** 8bit atomic boolean. */
    using ab8 = eastl::atomic<b8>;

    /** 8bit atomic flag. */
    using aflag = eastl::atomic_flag;

    /** the same as size_t but is atomic. */
    using asz = eastl::atomic<sz>;

    /** the same as ptrdiff_t but is atomic. */
    using aptrd = eastl::atomic<ptrd>;



    // \cond INTERNAL
    template<sz bits__>
    struct TF_uint_internal {
        using type = void;
    };
    template<>
    struct TF_uint_internal<8> {
        using type = u8;
    };
    template<>
    struct TF_uint_internal<16> {
        using type = u16;
    };
    template<>
    struct TF_uint_internal<32> {
        using type = u32;
    };
    template<>
    struct TF_uint_internal<64> {
        using type = u64;
    };
    // \endcond
    template<sz bits>
    using TF_uint = typename TF_uint_internal<bits>::type;

    // \cond INTERNAL
    template<sz bits__>
    struct TF_int_internal {
        using type = void;
    };
    template<>
    struct TF_int_internal<8> {
        using type = i8;
    };
    template<>
    struct TF_int_internal<16> {
        using type = i16;
    };
    template<>
    struct TF_int_internal<32> {
        using type = i32;
    };
    template<>
    struct TF_int_internal<64> {
        using type = i64;
    };
    // \endcond
    template<sz bits>
    using TF_int = typename TF_int_internal<bits>::type;



    // \cond INTERNAL
    template<sz bits__>
    struct TF_atomic_uint_internal {
        using type = void;
    };
    template<>
    struct TF_atomic_uint_internal<8> {
        using type = u8;
    };
    template<>
    struct TF_atomic_uint_internal<16> {
        using type = u16;
    };
    template<>
    struct TF_atomic_uint_internal<32> {
        using type = u32;
    };
    template<>
    struct TF_atomic_uint_internal<64> {
        using type = u64;
    };
    // \endcond
    template<sz bits>
    using TF_atomic_uint = typename TF_atomic_uint_internal<bits>::type;

    // \cond INTERNAL
    template<sz bits__>
    struct TF_atomic_int_internal {
        using type = void;
    };
    template<>
    struct TF_atomic_int_internal<8> {
        using type = i8;
    };
    template<>
    struct TF_atomic_int_internal<16> {
        using type = i16;
    };
    template<>
    struct TF_atomic_int_internal<32> {
        using type = i32;
    };
    template<>
    struct TF_atomic_int_internal<64> {
        using type = i64;
    };
    // \endcond
    template<sz bits>
    using TF_atomic_int = typename TF_atomic_int_internal<bits>::type;

#pragma endregion

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    template<typename F__>
    NCPP_FORCE_INLINE F__& T_null_reference() { return *reinterpret_cast<F__*>(0); }

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    template<typename F__>
    NCPP_FORCE_INLINE b8 T_is_valid(F__ const* ptr) {
        
        return ptr != 0;
    }
    template<typename F__>
    NCPP_FORCE_INLINE b8 T_is_valid(F__&& ptr) {

        return &ptr != 0;
    }

    template<typename F__>
    NCPP_FORCE_INLINE b8 T_is_null(F__ const* ptr) {

        return ptr == 0;
    }
    template<typename F__>
    NCPP_FORCE_INLINE b8 T_is_null(F__&& ptr) {

        return &ptr == 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    NCPP_FORCE_INLINE void pause_console() {

        std::cout << "Press any key to continue..." << std::endl;
        std::cin.get();

    }

}

#pragma endregion
