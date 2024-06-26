#pragma once

/** @file ncpp/containers/string_utilities.hpp
*	@brief Implements string utilities.
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

#include <ncpp/utilities/no_deduct.hpp>
#include <ncpp/containers/eastl_bindings.hpp>
#include <ncpp/containers/eastl_views.hpp>

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

    namespace containers {

        template<typename F_string__ = F_string>
        inline F_string__ T_replace(
            const F_string__& source,
			utilities::TF_no_deduct<const F_string__&> from,
			utilities::TF_no_deduct<const F_string__&> to
        ) {

            F_string__ result = source;

            size_t start_pos = result.find(from);

            if(start_pos == std::string::npos)
                return std::move(result);

            result.replace(start_pos, from.length(), to);

            return std::move(result);
        }
        NCPP_FORCE_INLINE F_string replace(const F_string& source, const F_string& from, const F_string& to) {

            return T_replace<F_string>(source, from, to);
        }
        NCPP_FORCE_INLINE G_string G_replace(const G_string& source, const G_string& from, const G_string& to) {

            return T_replace<G_string>(source, from, to);
        }

        template<typename F_string__ = F_string>
        inline F_string__ T_replace_all(
            const F_string__& source,
			utilities::TF_no_deduct<const F_string__&> from,
			utilities::TF_no_deduct<const F_string__&> to
        ) {

            if(from.empty())
                return source;

            F_string__ result = source;

            size_t start_pos = 0;

            while((start_pos = result.find(from, start_pos)) != std::string::npos) {

                result.replace(start_pos, from.length(), to);

                start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'

            }

            return std::move(result);
        }
        NCPP_FORCE_INLINE F_string replace_all(const F_string& source, const F_string& from, const F_string& to) {

            return T_replace_all<F_string>(source, from, to);
        }
        NCPP_FORCE_INLINE G_string G_replace_all(const G_string& source, const G_string& from, const G_string& to) {

            return T_replace_all<G_string>(source, from, to);
        }

        template<typename F_string__ = F_string>
        inline F_string__ T_decimal_to_hex(i64 decimal_in) {

            std::basic_stringstream<typename F_string__::value_type> stream;
            stream << std::hex << decimal_in;

            return stream.str().c_str();
        }
        NCPP_FORCE_INLINE F_string decimal_to_hex(i64 decimal_in) {

            return T_decimal_to_hex<F_string>(decimal_in);
        }
        NCPP_FORCE_INLINE G_string G_decimal_to_hex(i64 decimal_in) {

            return T_decimal_to_hex<G_string>(decimal_in);
        }

    }

}