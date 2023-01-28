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



#ifndef NCPP_DEFAULT_ALIGNMENT
#define NCPP_DEFAULT_ALIGNMENT 16
#endif



#if defined(_MSC_VER)
#define NCPP_ALIGN(N) __declspec(align(N))

#elif defined( __GNUC__ ) || defined(__MINGW64__)
#define NCPP_ALIGN(N) __attribute__((__align(N)))
#endif



#define NCPP_CLASS class NCPP_ALIGN(NCPP_DEFAULT_ALIGNMENT) 
#define NCPP_STRUCT struct NCPP_ALIGN(NCPP_DEFAULT_ALIGNMENT) 



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

	template<class TA_Class>
	NCPP_CLASS
	T_C_Singleton {

	private:
		static TA_Class * s_p_Instance;



	public:
		static NCPP_GETTER(TA_Class* P_Instance()) { return s_p_Instance; }
		static NCPP_GETTER(TA_Class& Instance()) { return *s_p_Instance; }



	public:
		NCPP_CONSTEXPR T_C_Singleton() { s_p_Instance = (TA_Class*)this; }

		template<typename... TA_Args>
		static NCPP_CONSTEXPR TA_Class* CreateInstance(const TA_Args&... args) {

			return new TA_Class(args...);
		}

	};

	template<class TA_Class>
	TA_Class* T_C_Singleton<TA_Class>::s_p_Instance = 0;



	using Id = size_t;

}

#pragma endregion