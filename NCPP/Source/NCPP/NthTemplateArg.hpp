#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/FirstTemplateArg.hpp>



namespace NCPP {

	template<
		size_t TA_N,
		typename... TA_FullArgs
	>
	struct T_S_NthTemplateArg {

	private:
		template<
			size_t TA_NRemains,
			bool TA_IsLast,
			typename... TA_Args
		>
		struct T_S_Minus1 
		{



		};

		template<
			typename... TA_Args
		>
		struct T_S_Minus1<
			0,
			true,
			TA_Args...
		>
		{

			using Type = typename T_S_FirstTemplateArg<TA_Args...>::Type;

		};

		template<
			size_t TA_NRemains,
			typename TA_Arg,
			typename... TA_Rest
		>
		struct T_S_Minus1<
			TA_NRemains,
			false,
			TA_Arg, TA_Rest...
		>
		{

			using Type = typename T_S_Minus1<TA_NRemains - 1, TA_NRemains == 1, TA_Rest...>::Type;

		};



	public:
		static_assert(TA_N < sizeof...(TA_FullArgs), "TA_N argument using in T_S_NthTemplateArg<...> is not valid!");
		using Type = typename T_S_Minus1<TA_N, TA_N == 0, TA_FullArgs...>::Type;

	};

}