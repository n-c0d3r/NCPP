#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/NthTemplateArg.hpp>



namespace NCPP {

	template<
        typename... TA_Types
	>
	struct T_S_LastTemplateArg {

		using Type = typename T_S_NthTemplateArg<sizeof...(TA_Types) - 1, TA_Types...>::Type;

	};

}