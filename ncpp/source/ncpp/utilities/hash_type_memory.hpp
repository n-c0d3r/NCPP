#pragma once

/**
 *  @file ncpp/utilities/hash_type_memory.hpp
 *  @brief Implements hash_type_memory.
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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/murmur_hash.hpp>

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

	namespace utilities {

		template<typename F__>
		struct TF_hash_type_memory {

			NCPP_FORCE_INLINE sz operator()(const F__& x) const noexcept {

				const u32 e_count = sizeof(F__) / sizeof(u32);

				u32 hash = 0;

#define NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM(...) \
					u32 element = ((const u32*)&x)[__VA_ARGS__];\
\
					element *= 0xcc9e2d51;\
					element = ( element << 15 ) | ( element >> (32 - 15) );\
					element *= 0x1b873593;\
\
					hash ^= element;\
					hash = ( hash << 13 ) | ( hash >> (32 - 13) );\
					hash = hash * 5 + 0xe6546b64;

#define NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(...) \
				if constexpr (e_count > __VA_ARGS__)\
				{\
					NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM(__VA_ARGS__);\
				}

				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(0);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(1);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(2);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(3);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(4);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(5);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(6);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(7);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(8);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(9);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(10);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(11);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(12);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(13);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(14);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(15);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(16);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(17);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(18);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(19);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(20);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(21);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(22);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(23);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(24);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(25);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(26);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(27);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(28);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(29);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(30);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(31);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(32);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(33);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(34);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(35);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(36);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(37);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(38);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(39);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(40);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(41);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(42);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(43);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(44);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(45);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(46);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(47);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(48);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(49);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(50);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(51);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(52);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(53);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(54);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(55);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(56);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(57);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(58);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(59);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(60);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(61);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(62);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(63);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(64);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(65);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(66);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(67);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(68);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(69);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(70);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(71);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(72);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(73);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(74);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(75);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(76);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(77);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(78);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(79);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(80);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(81);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(82);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(83);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(84);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(85);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(86);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(87);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(88);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(89);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(90);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(91);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(92);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(93);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(94);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(95);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(96);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(97);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(98);
				NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM_LOOP_STEP(99);

				if constexpr (sizeof(F__) % sizeof(u32)) {

					NCPP_INTERNAL_UPDATE_HASH_TYPE_MEM(e_count);
				}

				return murmur_finalize_32(hash);
			}

		};

	}

}