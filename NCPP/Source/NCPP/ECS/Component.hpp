#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/DOD/DOD.hpp>
#include <NCPP/ECS/Entity.hpp>



namespace NCPP {

	namespace ECS {

		using ComponentId = size_t;



		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IteratorHash,
			template<typename TA_ColumnType> typename TA_T_IteratorEqualTo
		>
		NCPP_CLASS T_C_EntitySystem;



		template<
			class TA_C_ComponentSystem,
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IteratorHash,
			template<typename TA_ColumnType> typename TA_T_IteratorEqualTo,
			typename TA_ComponentType
		>
		NCPP_CLASS T_IC_ComponentSystem :
			public DOD::T_IC_System<TA_C_ComponentSystem>
		{

		public:
			using DataType = typename DOD::T_C_Data<TA_T_C_Allocator, TA_T_IteratorHash, TA_T_IteratorEqualTo, TA_ComponentType>;
			using EntitySystemType = typename T_C_EntitySystem<TA_T_C_Allocator, TA_T_IteratorHash, TA_T_IteratorEqualTo>;
			using EntityId2ComponentIdMapType = typename std::unordered_map<
				EntityId, ComponentId, 
				TA_T_IteratorHash<EntityId>, 
				TA_T_IteratorEqualTo<EntityId>, 
				TA_T_C_Allocator<std::pair<const EntityId, ComponentId>>
			>;
			using ComponentId2EntityIdMapType = typename std::unordered_map<
				ComponentId, EntityId,
				TA_T_IteratorHash<ComponentId>,
				TA_T_IteratorEqualTo<ComponentId>,
				TA_T_C_Allocator<std::pair<const ComponentId, EntityId>>
			>;



		protected:
			DataType m_Data;
			EntitySystemType* m_p_EntitySystem;
			EntityId2ComponentIdMapType m_EntityId2ComponentIdMap;
			ComponentId2EntityIdMapType m_ComponentId2EntityIdMap;



		public:
			NCPP_GETTER(EntitySystemType* P_EntitySystem()) const { return m_p_EntitySystem; }



		protected:
			NCPP_CONSTEXPR T_IC_ComponentSystem(EntitySystemType* p_EntitySystem) :
				m_Data(),
				m_p_EntitySystem(p_EntitySystem)
			{

				
			
			}
			virtual ~T_IC_ComponentSystem() {

				m_EntityId2ComponentIdMap.clear();
				m_ComponentId2EntityIdMap.clear();

			}



		public:
			ComponentId AddComponent(EntityId entityId, const TA_ComponentType& component) {

				ComponentId id = m_Data.EmplaceBack(component);

				m_EntityId2ComponentIdMap[entityId] = id;
				m_ComponentId2EntityIdMap[id] = entityId;

				return id;
			}
			void RemoveComponent(EntityId entityId) {

				ComponentId id = m_EntityId2ComponentIdMap[entityId];

				m_EntityId2ComponentIdMap.erase(entityId);
				m_ComponentId2EntityIdMap.erase(id);

				m_Data.Erase(id);

			}

		};
			


		template<class TA_C_ComponentSystem, typename... TA_ComponentTypes>
		using T_IC_BasicComponentSystem = T_IC_ComponentSystem<TA_C_ComponentSystem, std::allocator, std::hash, std::equal_to, TA_ComponentTypes...>;


	}

}