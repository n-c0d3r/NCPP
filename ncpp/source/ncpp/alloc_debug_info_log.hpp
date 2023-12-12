#pragma once

/** @file ncpp/eastl_container_log.hpp
*	@brief Implement eastl container logging functionalities.
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

#include <ncpp/mem/allocator.hpp>
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/string_utilities.hpp>
#include <ncpp/utilities/type_info.hpp>
#include <ncpp/utilities/is_streamable.hpp>
#include <ncpp/iostream.hpp>
#include <ncpp/log_colors.hpp>
#include <ncpp/colorized_log.hpp>

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



#pragma region Alloc Debug Info
#ifdef NCPP_HAS_ALLOC_DEBUG_INFO
inline ncpp::F_ostream& operator << (ncpp::F_ostream& os, const ncpp::TF_ostream_input<ncpp::mem::F_alloc_debug_info>& input){

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW << "alloc_debug_info"
       << " ";

    os << ncpp::T_cout_lowlight("{");

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("allocator_address");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_address);
        os << ncpp::T_cout_lowlight(", ");

    }

#ifdef NCPP_ENABLE_ALLOCATOR_NAME
    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("allocator_name");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_name);
        os << ncpp::T_cout_lowlight(", ");

    }
#endif

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("allocator_type_name");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_type_name);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("allocator_type_hash_code");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_type_hash_code);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("actual_size");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.actual_size);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("payload_size");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.payload_size);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("alignment");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.alignment);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("alignment_offset");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.alignment_offset);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << " ";

        }
        os << ncpp::T_cout_field_name("is_default_alloc");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.is_default_alloc);

    }

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << " ";

    }

    os << ncpp::T_cout_lowlight("}");

    return os;
}

inline ncpp::F_ostream& operator << (ncpp::F_ostream& os, const ncpp::mem::F_alloc_debug_info& debug_info){

    os << ncpp::TF_ostream_input<ncpp::mem::F_alloc_debug_info>{debug_info, 0};

    return os;
}

inline ncpp::F_wostream& operator << (ncpp::F_wostream& os, const ncpp::TF_ostream_input<ncpp::mem::F_alloc_debug_info>& input){

    if (input.second > (ncpp::u32)NCPP_MAX_TAB_COUNT) {

        os << ncpp::T_cout_lowlight("...");

        return os;
    }

    os << NCPP_FOREGROUND_YELLOW_TEXT << L"alloc_debug_info"
       << L" ";

    os << ncpp::T_cout_lowlight("{");

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("allocator_address");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_address);
        os << ncpp::T_cout_lowlight(", ");

    }

#ifdef NCPP_ENABLE_ALLOCATOR_NAME
    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("allocator_name");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_name);
        os << ncpp::T_cout_lowlight(", ");

    }
#endif

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("allocator_type_name");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_type_name);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("allocator_type_hash_code");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.allocator_type_hash_code);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("actual_size");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.actual_size);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("payload_size");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.payload_size);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("alignment");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.alignment);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("alignment_offset");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.alignment_offset);
        os << ncpp::T_cout_lowlight(", ");

    }

    {

        os << std::endl;

        for (ncpp::u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

            os << L" ";

        }
        os << ncpp::T_cout_field_name("is_default_alloc");
        os << ncpp::T_cout_lowlight(" -> ");
        os << ncpp::T_cout_value(input.first.is_default_alloc);

    }

    os << std::endl;

    for (ncpp::u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

        os << L" ";

    }

    os << ncpp::T_cout_lowlight("}");

    return os;
}

inline ncpp::F_wostream& operator << (ncpp::F_wostream& os, const ncpp::mem::F_alloc_debug_info& debug_info){

    os << ncpp::TF_ostream_input<ncpp::mem::F_alloc_debug_info>{debug_info, 0};

    return os;
}
#endif
#pragma endregion