#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/DOD/DOD.hpp>
#include <NCPP/ECS/Entity.hpp>



namespace NCPP {

	namespace ECS {

		using ComponentId = size_t;



		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IdHash,
			template<typename TA_ColumnType> typename TA_T_IdEqualTo
		>
		NCPP_CLASS T_C_EntitySystem;



		template<
			class TA_C_ComponentSystem,
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IdHash,
			template<typename TA_ColumnType> typename TA_T_IdEqualTo,
			typename TA_ComponentType
		>
		NCPP_CLASS T_IC_ComponentSystem :
			public DOD::T_IC_System<TA_C_ComponentSystem>
		{

#pragma region Typedefs
		public:
			using DataType = typename DOD::T_C_Data<TA_T_C_Allocator, TA_T_IdHash, TA_T_IdEqualTo, TA_ComponentType>;
			using EntitySystemType = typename T_C_EntitySystem<TA_T_C_Allocator, TA_T_IdHash, TA_T_IdEqualTo>;
			using EntityId2ComponentIdMapType = typename std::unordered_map<
				EntityId, ComponentId, 
				TA_T_IdHash<EntityId>, 
				TA_T_IdEqualTo<EntityId>, 
				TA_T_C_Allocator<std::pair<const EntityId, ComponentId>>
			>;
			using ComponentId2EntityIdMapType = typename std::unordered_map<
				ComponentId, EntityId,
				TA_T_IdHash<ComponentId>,
				TA_T_IdEqualTo<ComponentId>,
				TA_T_C_Allocator<std::pair<const ComponentId, EntityId>>
			>;
#pragma endregion



#pragma region Nested Types
		public:
			struct S_Iterator;
			friend struct S_Iterator;

			struct S_Iterator {

			public:
				size_t index = 0;



			public:
				NCPP_CONSTEXPR TA_ComponentType& operator * () {

					return TA_C_ComponentSystem::P_Instance()->m_EnabledData.T_Column<TA_ComponentType>()[index];
				}
				NCPP_CONSTEXPR TA_ComponentType* operator -> () {

					return *(TA_C_ComponentSystem::P_Instance()->m_EnabledData.T_Column<TA_ComponentType>()[index]);
				}
				NCPP_CONSTEXPR const TA_ComponentType& operator * () const {

					return TA_C_ComponentSystem::P_Instance()->m_EnabledData.T_Column<TA_ComponentType>()[index];
				}
				NCPP_CONSTEXPR const TA_ComponentType* operator -> () const {

					return *(TA_C_ComponentSystem::P_Instance()->m_EnabledData.T_Column<TA_ComponentType>()[index]);
				}
				NCPP_CONSTEXPR S_Iterator operator + (size_t offset) const {

					return { index + offset; };
				}
				NCPP_CONSTEXPR S_Iterator operator - (size_t offset) const {

					return { index - offset; };
				}
				NCPP_CONSTEXPR S_Iterator& operator ++ () {

					++index;

					return *this;
				}
				NCPP_CONSTEXPR S_Iterator& operator -- () {

					--index;

					return *this;
				}
				NCPP_CONSTEXPR S_Iterator& operator += (size_t offset) {

					index += offset;

					return *this;
				}
				NCPP_CONSTEXPR S_Iterator& operator -= (size_t offset) {

					index -= offset;

					return *this;
				}
				NCPP_CONSTEXPR bool operator != (const S_Iterator& other) {

					return index != other.index;
				}

			};
#pragma endregion



#pragma region Properties
		protected:
			DataType m_EnabledData;
			DataType m_DisabledData;
			EntitySystemType& m_p_EntitySystem;
			EntityId2ComponentIdMapType m_EntityId2ComponentIdMap;
			ComponentId2EntityIdMapType m_ComponentId2EntityIdMap;
#pragma endregion



#pragma region Getters and Setters
		public:
			NCPP_GETTER(EntitySystemType* P_EntitySystem()) const { return m_p_EntitySystem; }

			NCPP_GETTER(DataType& EnabledData()) { return m_EnabledData; }
			NCPP_GETTER(const DataType& EnabledData()) const { return m_EnabledData; }

			NCPP_GETTER(DataType& DisabledData()) { return m_DisabledData; }
			NCPP_GETTER(const DataType& DisabledData()) const { return m_DisabledData; }

			NCPP_GETTER(S_Iterator begin()) { return { 0 }; }
			NCPP_GETTER(S_Iterator end()) { return { m_EnabledData.RowCount() }; }
			NCPP_GETTER(const S_Iterator begin()) const { return { 0 }; }
			NCPP_GETTER(const S_Iterator end()) const { return { m_EnabledData.RowCount() }; }
#pragma endregion



#pragma region Constructors, Destructor, and Operators
		protected:
			NCPP_CONSTEXPR T_IC_ComponentSystem() :
				m_EnabledData(),
				m_DisabledData(),
				m_p_EntitySystem(EntitySystemType::Instance())
			{

				
			
			}
			virtual ~T_IC_ComponentSystem() {

				m_EnabledData.Clear();
				m_DisabledData.Clear();
				m_EntityId2ComponentIdMap.clear();
				m_ComponentId2EntityIdMap.clear();

			}
#pragma endregion



#pragma region Methods
		public:
			ComponentId AddComponent(EntityId entityId, const TA_ComponentType& component) {

				ComponentId id = m_EnabledData.EmplaceBack(component);

				m_EntityId2ComponentIdMap[entityId] = id;
				m_ComponentId2EntityIdMap[id] = entityId;

				return id;
			}
			void RemoveComponent(EntityId entityId) {

				ComponentId id = m_EntityId2ComponentIdMap[entityId];

				m_EntityId2ComponentIdMap.erase(entityId);
				m_ComponentId2EntityIdMap.erase(id);

				m_EnabledData.Erase(id);

			}
			void Enable(ComponentId id) {

				if (m_DisabledData.IsHasRow(id)) {

					//TA_ComponentType component = std::move(std::get<TA_ComponentType>(m_DisabledData.GetRow(id)));

				}

			}
			void Disable(ComponentId id) {

				if (m_EnabledData.IsHasRow(id)) {

					size_t index = m_EnabledData.Id2Index(id);

					TA_ComponentType component = std::move(m_EnabledData.T_Column<TA_ComponentType>()[index]);

					m_EnabledData.Erase(id);

					m_DisabledData.EmplaceBackWithId(id, component);

				}

			}
#pragma endregion

		};
			


		template<class TA_C_ComponentSystem, typename TA_ComponentType>
		using T_IC_StandardComponentSystem = T_IC_ComponentSystem<TA_C_ComponentSystem, std::allocator, std::hash, std::equal_to, TA_ComponentType>;


	}

}