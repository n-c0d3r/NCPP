#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/TemplatedFor.hpp>

#include <NCPP/DOD/Table.hpp>
#include <NCPP/DOD/IdMap.hpp>



namespace NCPP {

	namespace DOD {

		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			typename... TA_ColumnTypes
		>
		NCPP_CLASS T_C_Data final {

		public:
			using TableType = typename T_C_Table<TA_T_C_Allocator, TA_ColumnTypes... >;
			using RowTupleType = typename TableType::RowTupleType;
			using IdMapType = typename T_C_IdMap<TA_T_C_Allocator>;

			template<size_t TA_Index>
			using T_ColumnType = typename TableType::T_ColumnType<TA_Index>;

			template<size_t TA_Index>
			using T_ColumnAllocatorType = typename TableType::T_ColumnAllocatorType<TA_Index>;

			template<size_t TA_Index>
			using T_ColumnVectorType = typename TableType::T_ColumnVectorType<TA_Index>;

			template<typename TA_ColumnType>
			using T_ColumnVectorTypeFromColumnType = typename TableType::T_ColumnVectorTypeFromColumnType<TA_ColumnType>;



		private:



		private:
			TableType m_Table;

			IdMapType m_IdMap;
			IdMapType m_IndexMap;



		public:
			NCPP_GETTER(TableType& Table()) { return m_Table; }
			NCPP_GETTER(const TableType& Table()) const { return m_Table; }

			NCPP_GETTER(IdMapType& IdMap()) { return m_IdMap; }
			NCPP_GETTER(const IdMapType& IdMap()) const { return m_IdMap; }

			NCPP_GETTER(Id Index2Id(size_t index)) const { return m_IndexMap.find(index)->second; }
			NCPP_GETTER(Id Id2Index(Id id)) const { return m_IdMap.find(id)->second; }

			NCPP_GETTER(const RowTupleType Row(Id id)) const {

				Id index = m_IdMap.find(id)->second;

				return m_Table.Row(index);
			}

			NCPP_SETTER(void SetRow(Id id, const RowTupleType& rowTuple)) {

				Id index = m_IdMap.find(id)->second;

				m_Table.SetRow(index, rowTuple);
			}

			template<typename TA_ColumnType>
			NCPP_GETTER(typename TableType::T_ColumnVectorTypeFromColumnType<TA_ColumnType>& T_Column()) {

				return m_Table.T_Column<TA_ColumnType>();
			}

			template<typename TA_ColumnType>
			NCPP_GETTER(const typename TableType::T_ColumnVectorTypeFromColumnType<TA_ColumnType>& T_Column()) const {

				return m_Table.T_Column<TA_ColumnType>();
			}



		public:
			NCPP_CONSTEXPR T_C_Data() :
				m_Table(0)
			{



			}
			~T_C_Data() {

				m_Table.Clear();
				m_IdMap.clear();
				m_IndexMap.clear();

			}



		public:
			NCPP_CONSTEXPR Id EmplaceBack(const RowTupleType& rowTuple) {

				Id index = m_Table.RowCount();
				Id id = T_CreateId(m_IdMap, index);
				m_IndexMap[index] = id;

				m_Table.EmplaceBack(rowTuple);

				return id;
			}
			NCPP_CONSTEXPR Id EmplaceBack(TA_ColumnTypes&&... datas) {

				return EmplaceBack(std::make_tuple(std::forward<TA_ColumnTypes>(datas)...));
			}
			NCPP_CONSTEXPR void Erase(Id id) {

				Id index = m_IdMap[id];
				Id lastIndex = m_Table.RowCount() - 1;

				m_IndexMap[index] = m_IndexMap[lastIndex];
				m_IndexMap.erase(lastIndex);

				m_IdMap[m_IndexMap[index]] = index;

				T_DeleteId(m_IdMap, id);

				m_Table.Erase(index);

			}

		};



		template<typename... TA_ColumnTypes>
		using T_C_DefaultData = typename T_C_Data<std::allocator, TA_ColumnTypes...>;
	}

}