#pragma once

#include <NCPP/Utilities.hpp>



namespace NCPP {

	namespace DOD {

		template<class TA_C_System>
		NCPP_CLASS T_IC_System : public T_C_Singleton<TA_C_System>
		{

#pragma region Constructors, Destructor, and Operators
		protected:
			NCPP_CONSTEXPR T_IC_System() {

				
			
			}
			virtual ~T_IC_System() {



			}
#pragma endregion

		};

	}

}