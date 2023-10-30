#pragma once

/** @file ncpp/iostream.hpp
*	@brief Implement iostream with custom allocators,...
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

#ifdef NCPP_ENABLE_MEMORY_COUNTING
#include <ncpp/mem/memory_counting.hpp>
#endif

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/is_streamable.hpp>

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



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	/**
	 *	Wraps the input data reference inside and also stores the tab count for with-tabs out streaming operation. 
	 */
	template<typename F__>
	using TF_ostream_input = typename std::pair<const F__&, u32>;



	// \cond INTERNAL
	template<typename F_stream__, typename F__, b8 is_streamable__>
	struct TF_safe_ostream_forwarder {

	};

	template<typename F_stream__, typename F__>
	struct TF_safe_ostream_forwarder<F_stream__, F__, true> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, F__&& data) {

			stream << data;

			return stream;
		}
	};

	template<typename F_stream__, typename F__>
	struct TF_safe_ostream_forwarder<F_stream__, F__, false> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, F__&& data) {



			return stream;
		}
	};
	// \endcond



	/**
	 *	Performs the out streaming operation safely.
	 *	If data is out streamable, stream out the data.
	 *	Otherwise, do nothing and wont cause any error.
	 */
	template<typename F_stream__, typename F__>
	NCPP_FORCE_INLINE F_stream__& T_safe_ostream(F_stream__& stream, F__&& data) {

		using safe_ostream_forward_type = TF_safe_ostream_forwarder<
			F_stream__,
			F__,
			utilities::TF_is_ostreamable<
				F_stream__,
				F__
			>::value
		>;
			
		return safe_ostream_forward_type::forward(stream, std::forward<F__>(data));
	}



	// \cond INTERNAL
	template<typename F_stream__, typename input_type__, b8 is_streamable__>
	struct TF_safe_ostream_with_tab_forwarder {

	};

	template<typename F_stream__, typename input_type__>
	struct TF_safe_ostream_with_tab_forwarder<F_stream__, input_type__, true> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, input_type__&& input) {

			stream << input;

			return stream;
		}
	};

	template<typename F_stream__, typename input_type__>
	struct TF_safe_ostream_with_tab_forwarder<F_stream__, input_type__, false> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, input_type__&& input) {

			T_safe_ostream(stream, input.first);

			return stream;
		}
	};
	// \endcond



	/**
	 *	Performs the out streaming operation safely with tabs.
	 *	If data is out streamable, stream out the data with tabs.
	 *	Otherwise, do nothing and wont cause any error.
	 */
	template<typename F_stream__, typename F__, typename input_type__ = TF_ostream_input<F__>>
	NCPP_FORCE_INLINE F_stream__& T_safe_ostream_with_tab(F_stream__& stream, input_type__&& input) {

		using safe_ostream_with_tab_forward_type = TF_safe_ostream_with_tab_forwarder<
			F_stream__,
			input_type__,
			utilities::TF_is_ostreamable<
				F_stream__,
				input_type__
			>::value
		>;

		return safe_ostream_with_tab_forward_type::forward(stream, std::forward<input_type__>(input));
	}



	// \cond INTERNAL
	template<typename F_stream__, typename F__, b8 is_streamable__>
	struct TF_safe_istream_forwarder {

	};

	template<typename F_stream__, typename F__>
	struct TF_safe_istream_forwarder<F_stream__, F__, true> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, F__&& data) {

			stream >> data;

			return stream;
		}
	};

	template<typename F_stream__, typename F__>
	struct TF_safe_istream_forwarder<F_stream__, F__, false> {

		static NCPP_FORCE_INLINE F_stream__& forward(F_stream__& stream, F__&& data) {



			return stream;
		}
	};
	// \endcond



	/**
	 *	Performs the in streaming operation safely.
	 *	If data is in streamable, stream in the data.
	 *	Otherwise, do nothing and wont cause any error.
	 */
	template<typename F_stream__, typename F__>
	NCPP_FORCE_INLINE F_stream__& T_safe_istream(F_stream__& stream, F__&& data) {

		using safe_istream_forward_type = TF_safe_istream_forwarder<
			F_stream__,
			F__,
			utilities::TF_is_istreamable<
				F_stream__,
				F__
			>::value
		>;

		return safe_istream_forward_type::forward(stream, std::forward<F__>(data));
	}

}

