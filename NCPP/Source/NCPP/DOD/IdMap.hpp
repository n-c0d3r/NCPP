#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/TemplatedFor.hpp>



namespace NCPP {

	namespace DOD {

		template<template<
			typename TA_Type> class TA_T_C_Allocator,
			typename TA_S_Hash = std::hash<Id>
		>
		using T_C_IdMap = std::unordered_map<
			Id, 
			Id,
			TA_S_Hash, 
			std::equal_to<Id>,
			TA_T_C_Allocator<std::pair<const Id, Id>>
		>;

		template<template<
			typename TA_Type> class TA_T_C_Allocator,
			typename TA_S_Hash
		>
		static NCPP_CONSTEXPR Id T_CreateId(
			T_C_IdMap<TA_T_C_Allocator, TA_S_Hash>& map,
			Id data
		) 
		{

			size_t id;

			if (sizeof(size_t) == sizeof(std::uint64_t))
				id = static_cast<std::uint64_t>(rand()) * static_cast<std::uint64_t>(rand());
			if (sizeof(size_t) == sizeof(std::uint32_t))
				id = rand();

			if (map.find(id) == map.end())
			{
				map[id] = data;
				return id;
			}
			
			return T_CreateId<TA_T_C_Allocator, TA_S_Hash>(map, data);
		}

		template<template<
			typename TA_Type> class TA_T_C_Allocator,
			typename TA_S_Hash
		>
		static NCPP_CONSTEXPR void T_DeleteId(
			T_C_IdMap<TA_T_C_Allocator, TA_S_Hash>& map,
			Id id
		)
		{

			map.erase(id);
		}

	}

}