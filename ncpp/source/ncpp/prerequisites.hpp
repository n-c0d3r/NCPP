#pragma once

/** @file ncpp/prerequisites.hpp
*   @brief The file that is always included on the top.
*
*   Includes stl headers, platform api headers, and defines some macros,...
*/



namespace ncpp {}






#pragma region Includes

#include <ncpp/config.hpp>



#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <variant>
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
#include <semaphore>



#if defined(_WIN64) || defined(_WIN32)
#define NCPP_WINDOWS_PLATFORM
#include <Windows.h>
#include <DirectXMath.h>
#endif

#pragma endregion






#pragma region Macros

#if defined(_WIN64) || defined(_WIN32)
#define NCPP_WINDOWS_PLATFORM
#endif



#define NCPP_CONSTEXPR inline constexpr



// alignment macros
#if defined(_MSC_VER)
#define NCPP_ALIGN(N) __declspec(align(N))
#elif defined( __GNUC__ ) || defined(__MINGW64__)
#define NCPP_ALIGN(N) __attribute__((__align(N)))
#endif

#define NCPP_DEFAULT_ALIGN NCPP_ALIGN(NCPP_DEFAULT_ALIGNMENT)



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

#pragma endregion



#pragma region Typedefs

namespace ncpp {
    
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

}

#pragma endregion