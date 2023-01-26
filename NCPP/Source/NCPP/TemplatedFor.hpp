#pragma once

#include <NCPP/Utilities.hpp>



namespace NCPP {

	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End, size_t TA_Index,
		typename... TA_Args
	>
	NCPP_CONSTEXPR void T_TemplatedFor_Step(TA_Args&&... args);

	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End, size_t TA_Index, bool TA_IsEnd
	>
	struct T_S_TemplatedFor_Step {

		template<typename... TA_Args>
		static NCPP_CONSTEXPR void Invoke(TA_Args&&... args) {



		};

	};
	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End, size_t TA_Index
	>
	struct T_S_TemplatedFor_Step<
		TA_FunctionType,
		TA_Begin, TA_End, TA_Index, true
	> {

		template<typename... TA_Args>
		static NCPP_CONSTEXPR void Invoke(TA_Args&&... args) {



		};

	};
	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End, size_t TA_Index
	>
	struct T_S_TemplatedFor_Step<
		TA_FunctionType,
		TA_Begin, TA_End, TA_Index, false
	> {

		template<typename... TA_Args>
		static NCPP_CONSTEXPR void Invoke(TA_Args&&... args) {

			TA_FunctionType<TA_Index>::Invoke(std::forward<TA_Args>(args)...);

			T_TemplatedFor_Step<
				TA_FunctionType,
				TA_Begin, TA_End, TA_Index + 1
			>(std::forward<TA_Args>(args)...);

		};

	};

	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End, size_t TA_Index,
		typename... TA_Args
	>
	NCPP_CONSTEXPR void T_TemplatedFor_Step(TA_Args&&... args) {

		T_S_TemplatedFor_Step<
			TA_FunctionType,
			TA_Begin, TA_End, TA_Index, TA_Index == TA_End
		>::Invoke(std::forward<TA_Args>(args)...);

	};

	template<
		template<size_t TA_Index> typename TA_FunctionType,
		size_t TA_Begin, size_t TA_End,
		typename... TA_Args
	>
	NCPP_CONSTEXPR void T_TemplatedFor(TA_Args&&... args) {

		T_TemplatedFor_Step<
			TA_FunctionType,
			TA_Begin, TA_End, TA_Begin
		>(std::forward<TA_Args>(args)...);

	};

}