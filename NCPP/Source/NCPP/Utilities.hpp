#pragma once

#pragma region Includes

#include <NCPP/Config.hpp>



#include <iostream>
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



#if defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
#include <DirectXMath.h>
#endif



#pragma endregion







#pragma region Common Macros

#define NCPP_CONSTEXPR inline constexpr
#define NCPP_GETTER(Getter) NCPP_CONSTEXPR Getter
#define NCPP_SETTER(Setter) NCPP_CONSTEXPR Setter 



#if defined(_MSC_VER)
#define NCPP_ALIGN(N) __declspec(align(N))

#elif defined( __GNUC__ ) || defined(__MINGW64__)
#define NCPP_ALIGN(N) __attribute__((__align(N)))
#endif



//Use to create the function which is nested inside a struct
#define NCPP_SFUNCTION(ReturnType, Name, Params, Content) \
struct Name final {\
\
	static ReturnType Invoke Params { Content; }\
\
};

#pragma endregion







#pragma region Utility Classes, Structs and Types

namespace NCPP {



}

#pragma endregion