#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/DOD/DOD.hpp>



namespace NCPP {

	namespace ECS {

		using EntityId = size_t;



#ifndef ECS_SIGNATURE_BIT_COUNT 
#define ECS_SIGNATURE_BIT_COUNT 32
#endif



		struct S_EntitySignature final {

		private:
			std::bitset<ECS_SIGNATURE_BIT_COUNT> m_Value;



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

		};



		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IteratorHash,
			template<typename TA_ColumnType> typename TA_T_IteratorEqualTo
		>
		NCPP_CLASS T_C_EntitySystem final :
			public DOD::T_IC_System<T_C_EntitySystem<TA_T_C_Allocator, TA_T_IteratorHash, TA_T_IteratorEqualTo>>
		{

		public:
			using DataType = typename DOD::T_C_Data<TA_T_C_Allocator, TA_T_IteratorHash, TA_T_IteratorEqualTo, S_EntitySignature>;



		protected:
			DataType m_Data;



		public:
			NCPP_CONSTEXPR T_C_EntitySystem() :
				m_Data()
			{



			}
			~T_C_EntitySystem() {



			}



		public:
			EntityId CreateEntity() {

				return m_Data.EmplaceBack(S_EntitySignature());
			}
			void DestroyEntity(EntityId id) {

				m_Data.Erase(id);

			}

		};



		using C_BasicEntitySystem = T_C_EntitySystem<std::allocator, std::hash, std::equal_to>;

	}

}