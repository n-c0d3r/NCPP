#pragma once

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



#if defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
#include <DirectXMath.h>
#endif

#pragma endregion







#pragma region Macros

#define NCPP_CONSTEXPR inline constexpr
#define NCPP_GETTER(Getter) inline Getter
#define NCPP_SETTER(Setter) inline Setter 



#if defined(_MSC_VER)
#define NCPP_ALIGN(N) __declspec(align(N))
#elif defined( __GNUC__ ) || defined(__MINGW64__)
#define NCPP_ALIGN(N) __attribute__((__align(N)))
#endif

#define NCPP_DEFAULT_ALIGN NCPP_ALIGN(NCPP_DEFAULT_ALIGNMENT)



// Not allow use of directive inside function body
#define NCPP_LOOP_FUNCTION_T(Name, Params, Body) \
template<size_t index>\
struct Name {\
\
	static inline void invoke Params { Body; }; \
\
};



#if defined(__GNUC__)
#define DEPRECATE(foo, msg) foo __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define DEPRECATE(foo, msg) __declspec(deprecated(msg)) foo
#else
#error This compiler is not supported
#endif

#define PP_CAT(x,y) PP_CAT1(x,y)
#define PP_CAT1(x,y) x##y

namespace detail
{
    struct true_type {};
    struct false_type {};
    template <int test> struct converter : public true_type {};
    template <> struct converter<0> : public false_type {};
}

#define static_warning(cond, msg) \
struct PP_CAT(static_warning,__LINE__) { \
  DEPRECATE(void _(::detail::false_type const& ),msg) {}; \
  void _(::detail::true_type const& ) {}; \
  PP_CAT(static_warning,__LINE__)() {_(::detail::converter<(cond)>());} \
}

// Note: using static_warning_template changes the meaning of a program in a small way.
// It introduces a member/variable declaration.  This means at least one byte of space
// in each structure/class instantiation.  static_warning should be preferred in any 
// non-template situation.
//  'token' must be a program-wide unique identifier.
#define static_warning_template(token, cond, msg) \
    static_warning(cond, msg) PP_CAT(PP_CAT(_localvar_, token),__LINE__)

#pragma endregion







#pragma region Utility Items

#include <ncpp/singleton.hpp>
#include <ncpp/lock_guard.hpp>

namespace ncpp {

    

}

#pragma endregion


