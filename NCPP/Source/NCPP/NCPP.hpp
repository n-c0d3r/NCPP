#pragma once

namespace NCPP {



}



#include <NCPP/Utilities.hpp>
#include <NCPP/TemplatedFor.hpp>
#include <NCPP/FirstTemplateArg.hpp>
#include <NCPP/LastTemplateArg.hpp>
#include <NCPP/NthTemplateArg.hpp>
#include <NCPP/DOD/DOD.hpp>
#include <NCPP/ECS/ECS.hpp>



namespace NCPP {

	NCPP_CLASS C_NCPP final : 
		public T_C_Singleton<C_NCPP>
	{

	public:
		NCPP_STRUCT S_Settings final {

			bool enableJobSystem = false;

		};



	private:
		S_Settings m_Settings;
		NCPP_GETTER(S_Settings Settings()) { return m_Settings; }



	public:
		C_NCPP(const S_Settings& settings);
		~C_NCPP();

	};

}