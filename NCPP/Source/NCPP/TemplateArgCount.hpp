#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/NthTemplateArg.hpp>



namespace NCPP {

	template<
		typename... TA_Types
	>
	NCPP_CONSTEXPR size_t T_TemplateArgCount() {

		return sizeof...(TA_Types);
	};

}