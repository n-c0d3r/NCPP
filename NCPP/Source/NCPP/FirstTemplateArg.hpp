#pragma once

#include <NCPP/Utilities.hpp>



namespace NCPP {

	template<
        typename... TA_Types
	>
	struct T_S_FirstTemplateArg {

		template<bool TA_IsSingleCase, typename... TA_Types>
		struct T_S_ArgsCase {

			using Type = void;

		};
		template<typename TA_Type>
		struct T_S_ArgsCase<true, TA_Type> {

			using Type = TA_Type;

		};
		template<typename TA_Type, typename... TA_Rest>
		struct T_S_ArgsCase<false, TA_Type, TA_Rest...> {

			using Type = TA_Type;

		};



		using Type = typename T_S_ArgsCase<sizeof...(TA_Types) == 1, TA_Types...>::Type;

	};

}