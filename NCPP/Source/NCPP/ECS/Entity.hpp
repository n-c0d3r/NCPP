#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/DOD/DOD.hpp>



namespace NCPP {

	namespace ECS {

		using EntityId = size_t;



#ifndef ECS_SIGNATURE_BIT_COUNT 
#define ECS_SIGNATURE_BIT_COUNT 32
#endif



		NCPP_STRUCT S_EntitySignature final {

#pragma region Properties
		private:
			std::bitset<ECS_SIGNATURE_BIT_COUNT> m_Value;
#pragma endregion



#pragma region Constructors and Destructor
		public:
			S_EntitySignature() :
				m_Value(0)
			{



			}
			S_EntitySignature(std::bitset<ECS_SIGNATURE_BIT_COUNT> value) :
				m_Value(value)
			{



			}
			~S_EntitySignature() {



			}
#pragma endregion

		}
		;



		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IdHash,
			template<typename TA_ColumnType> typename TA_T_IdEqualTo
		>
		NCPP_CLASS T_C_EntitySystem final :
			public DOD::T_IC_System<T_C_EntitySystem<TA_T_C_Allocator, TA_T_IdHash, TA_T_IdEqualTo>>
		{

#pragma region Typedefs
		public:
			using DataType = typename DOD::T_C_Data<TA_T_C_Allocator, TA_T_IdHash, TA_T_IdEqualTo, S_EntitySignature>;
#pragma endregion



#pragma region Properties
		protected:
			DataType m_Data;
#pragma endregion



#pragma region Constructors, Destructor, and Operators
		public:
			NCPP_CONSTEXPR T_C_EntitySystem() :
				m_Data()
			{



			}
			~T_C_EntitySystem() {



			}
#pragma endregion



#pragma region Methods
		public:
			EntityId CreateEntity() {

				return m_Data.EmplaceBack(S_EntitySignature());
			}
			void DestroyEntity(EntityId id) {

				m_Data.Erase(id);

			}
#pragma endregion

		};



		using C_StandardEntitySystem = T_C_EntitySystem<std::allocator, std::hash, std::equal_to>;

	}

}