#pragma once

/** @file ncpp/profiler.hpp
*	@brief Contains the memory management utilities.
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/unique_lock.hpp>
#include <ncpp/log.hpp>
#include <ncpp/iostream.hpp>

#pragma endregion



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

	class F_profiler_sample {

	public:
		using F_output_function = void(const eastl::string& name, u64 nanoseconds);



	private:
		eastl::string content_;
		F_output_function* output_function_p_ = 0;
		eastl::chrono::system_clock::time_point start_;



	public:
		NCPP_FORCE_INLINE const eastl::string& content() const { return content_; }
		NCPP_FORCE_INLINE F_output_function* output_function_p() const { return output_function_p_; }



	public:
		NCPP_FORCE_INLINE F_profiler_sample(
			const eastl::string& content = "",
			F_output_function* output_function_p = [](const eastl::string& content, u64 nanoseconds) {

                cout << content.c_str() << F_cout_nanoseconds{nanoseconds} << F_cout_lowlight{" (nanoseconds)"} << std::endl;

			}
		) :
			content_(content),
			output_function_p_(output_function_p)
		{

			start_ = eastl::chrono::high_resolution_clock::now();

		}
		NCPP_FORCE_INLINE F_profiler_sample(
			eastl::string&& content = "",
			F_output_function* output_function_p = [](const eastl::string& content, u64 nanoseconds) {

                cout << content.c_str() << F_cout_nanoseconds{nanoseconds} << F_cout_lowlight{" (nanoseconds)"} << std::endl;

			}
		) :
			content_(std::move(content)),
			output_function_p_(output_function_p)
		{

			start_ = eastl::chrono::high_resolution_clock::now();

		}
		~F_profiler_sample() {

			output_function_p_(
				content_, 
				eastl::chrono::duration_cast<eastl::chrono::nanoseconds>(
					eastl::chrono::high_resolution_clock::now() - start_
				).count()
			);

		}

	};



#ifdef NCPP_ENABLE_SCOPED_PROFILER_SAMPLE
#define NCPP_SCOPED_PROFILER_SAMPLE(Content) ncpp::F_profiler_sample NCPP_GLUE(___ncpp_profiler_sample___, __LINE__)(Content);
#else
#define NCPP_SCOPED_PROFILER_SAMPLE(Content) ;
#endif

}

