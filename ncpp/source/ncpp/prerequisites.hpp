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

#include <ncpp/config.hpp>

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

#include <string.h>

#if _HAS_CXX20
#include <coroutine>
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region EASTL Headers

#include <ncpp/eastl_headers.hpp>

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region C Headers

#include <string.h>

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Windows Platform 
#if defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
#include <DirectXMath.h>
#endif
#pragma endregion

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Unix Platform 

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#include <unistd.h>
#include <pthread.h>

#endif

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

#pragma region Platform 

#if defined(_WIN64) || defined(_WIN32)
#define NCPP_WINDOWS_PLATFORM
#endif

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#define NCPP_UNIX_PLATFORM
#endif

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region C++ Utilities
#define NCPP_CONSTEXPR inline constexpr
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Alignment utility macros
// alignment macros
#if defined(_MSC_VER)
#define NCPP_ALIGNAS(N) __declspec(align(N))
#elif defined( __GNUC__ ) || defined(__MINGW64__)
#define NCPP_ALIGNAS(N) alignas(N)
#endif
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region Implements warning macros
// Implements static warning
#if defined(__GNUC__)
#define DEPRECATE(foo, msg) foo __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define DEPRECATE(foo, msg) __declspec(deprecated(msg)) foo
#else
#error This compiler is not supported
#endif

#define NCPP_PP_CAT(x,y) NCPP_PP_CAT1(x,y)
#define NCPP_PP_CAT1(x,y) x##y

namespace ncpp {

    namespace static_warning_helper
    {
        struct true_type {};
        struct false_type {};
        template <int test> struct converter : public true_type {};
        template <> struct converter<0> : public false_type {};
    }

}

#define static_warning(cond, msg) \
struct NCPP_PP_CAT(static_warning,__LINE__) { \
  DEPRECATE(void _(::ncpp::static_warning_helper::false_type const& ),msg) {}; \
  void _(::ncpp::static_warning_helper::true_type const& ) {}; \
  NCPP_PP_CAT(static_warning,__LINE__)() {_(ncpp::static_warning_helper::converter<(cond)>());} \
}

// Note: using static_warning_template changes the meaning of a program in a small way.
// It introduces a member/variable declaration.  This means at least one byte of space
// in each structure/class instantiation.  static_warning should be preferred in any 
// non-template situation.
//  'token' must be a program-wide unique identifier.
#define static_warning_template(token, cond, msg) \
    static_warning(cond, msg) NCPP_PP_CAT(NCPP_PP_CAT(_localvar_, token),__LINE__)

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG 
#define NCPP_DEBUG
#define warning(cond, msg) if(!(cond)) std::cout << "Warning: " << msg << std::endl;
#else
#define warning(cond, msg) ;
#endif

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#define NCPP_MP_GROUP(...) __VA_ARGS__

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
    using f32 = float; 
    /** 64bit floating-point type. */
    using f64 = double; 
    
    /** 8bit boolean. */
    using b8 = bool; 

    /** the same as size_t. */
    using sz = size_t;



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

    /** 8bit atomic boolean. */
    using ab8 = eastl::atomic<b8>;

    /** 8bit atomic flag. */
    using aflag = eastl::atomic_flag;

    /** the same as size_t but is atomic. */
    using asz = eastl::atomic<sz>;



    // \cond INTERNAL
    template<sz bits__>
    struct uint_internal_t {
        using type = void;
    };
    template<>
    struct uint_internal_t<8> {
        using type = u8;
    };
    template<>
    struct uint_internal_t<16> {
        using type = u16;
    };
    template<>
    struct uint_internal_t<32> {
        using type = u32;
    };
    template<>
    struct uint_internal_t<64> {
        using type = u64;
    };
    // \endcond
    template<sz bits>
    using uint_t = typename uint_internal_t<bits>::type;

    // \cond INTERNAL
    template<sz bits__>
    struct int_internal_t {
        using type = void;
    };
    template<>
    struct int_internal_t<8> {
        using type = i8;
    };
    template<>
    struct int_internal_t<16> {
        using type = i16;
    };
    template<>
    struct int_internal_t<32> {
        using type = i32;
    };
    template<>
    struct int_internal_t<64> {
        using type = i64;
    };
    // \endcond
    template<sz bits>
    using int_t = typename int_internal_t<bits>::type;



    // \cond INTERNAL
    template<sz bits__>
    struct atomic_uint_internal_t {
        using type = void;
    };
    template<>
    struct atomic_uint_internal_t<8> {
        using type = u8;
    };
    template<>
    struct atomic_uint_internal_t<16> {
        using type = u16;
    };
    template<>
    struct atomic_uint_internal_t<32> {
        using type = u32;
    };
    template<>
    struct atomic_uint_internal_t<64> {
        using type = u64;
    };
    // \endcond
    template<sz bits>
    using atomic_uint_t = typename atomic_uint_internal_t<bits>::type;

    // \cond INTERNAL
    template<sz bits__>
    struct atomic_int_internal_t {
        using type = void;
    };
    template<>
    struct atomic_int_internal_t<8> {
        using type = i8;
    };
    template<>
    struct atomic_int_internal_t<16> {
        using type = i16;
    };
    template<>
    struct atomic_int_internal_t<32> {
        using type = i32;
    };
    template<>
    struct atomic_int_internal_t<64> {
        using type = i64;
    };
    // \endcond
    template<sz bits>
    using atomic_int_t = typename atomic_int_internal_t<bits>::type;

#pragma endregion

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    template<typename type__>
    inline type__& null_reference_t() { return *reinterpret_cast<type__*>(0); }

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    template<typename type__>
    inline b8 is_valid_t(const type__* ptr) {
        
        return ptr != 0;
    }
    template<typename type__>
    inline b8 is_valid_t(type__&& ptr) {

        return &ptr != 0;
    }

    template<typename type__>
    inline b8 is_null_t(const type__* ptr) {

        return ptr == 0;
    }
    template<typename type__>
    inline b8 is_null_t(type__&& ptr) {

        return &ptr == 0;
    }

}

#pragma endregion