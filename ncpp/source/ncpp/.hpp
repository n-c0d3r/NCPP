#pragma once

namespace ncpp { }

#include <ncpp/prerequisites.hpp>

#include <ncpp/mem.hpp>
#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>



namespace ncpp {

	struct NCPP_DEFAULT_ALIGN application_settings {



	};



	class NCPP_DEFAULT_ALIGN application :
		utilities::singleton_t<application>
	{

	private:
		const application_settings settings_;



	private:
		NCPP_CONSTEXPR const application_settings& settings() const { return settings_; }



	public:
		application(const application_settings& settings);
		~application();



	public:
		void start();

	};

}