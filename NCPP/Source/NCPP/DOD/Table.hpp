#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/TemplatedFor.hpp>



namespace NCPP {

	namespace DOD {
				
		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			typename... TA_ColumnTypes
		>
		NCPP_CLASS T_C_Table final {

		public:
			using ColumnVectorsTupleType = typename std::tuple<std::vector<TA_ColumnTypes, TA_T_C_Allocator<TA_ColumnTypes>>...>;
			using RowTupleType = typename std::tuple<TA_ColumnTypes...>;

			static const size_t ColumnCount = std::tuple_size_v<ColumnVectorsTupleType>;

			template<size_t TA_Index>
			using T_ColumnType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>::value_type;

			template<size_t TA_Index>
			using T_ColumnAllocatorType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>::allocator_type;

			template<size_t TA_Index>
			using T_ColumnVectorType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>;

			template<typename TA_ColumnType>
			using T_ColumnVectorTypeFromColumnType = typename std::vector<TA_ColumnType, TA_T_C_Allocator<TA_ColumnType>>;



		private:
			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, ClearColumnVectors, (ColumnVectorsTupleType& tuple),
				{

					typename T_ColumnVectorType<TA_Index>& vector = std::get<typename T_ColumnVectorType<TA_Index>>(tuple);

					vector.clear();

				}
			)

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, ResizeColumnVectors, (ColumnVectorsTupleType& tuple, size_t newRowCount),
				{

					typename T_ColumnVectorType<TA_Index>& vector = std::get<typename T_ColumnVectorType<TA_Index>>(tuple);

					vector.resize(newRowCount);

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, CopyColumnVectors, (ColumnVectorsTupleType& tupleDst, ColumnVectorsTupleType& tupleSrc),
				{

					typename T_ColumnVectorType<TA_Index>& vector1 = std::get<typename T_ColumnVectorType<TA_Index>>(tupleDst);
					typename T_ColumnVectorType<TA_Index>& vector2 = std::get<typename T_ColumnVectorType<TA_Index>>(tupleSrc);

					vector1 = vector2;

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, MoveColumnVectors, (ColumnVectorsTupleType& tupleDst, ColumnVectorsTupleType& tupleSrc),
				{

					typename T_ColumnVectorType<TA_Index>& vector1 = std::get<typename T_ColumnVectorType<TA_Index>>(tupleDst);
					typename T_ColumnVectorType<TA_Index>& vector2 = std::get<typename T_ColumnVectorType<TA_Index>>(tupleSrc);

					vector1 = std::move(vector2);
					vector2.clear();

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, SetRowTuple, (ColumnVectorsTupleType& tuple, size_t rowIndex, const RowTupleType& rowTuple),
				{

					std::get<typename T_ColumnVectorType<TA_Index>>(tuple)[rowIndex] = std::get<TA_Index>(rowTuple);

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				void, GetRowTuple, (ColumnVectorsTupleType& tuple, size_t rowIndex, RowTupleType& rowTuple),
				{

					std::get<TA_Index>(rowTuple) = std::get<typename T_ColumnVectorType<TA_Index>>(tuple)[rowIndex];

				}
			);



		private:
			ColumnVectorsTupleType m_ColumnVectorsTuple;

			size_t m_RowCount;



		public:
			NCPP_GETTER(size_t RowCount()) const { return m_RowCount; }

			template<typename TA_ColumnType>
			NCPP_GETTER(T_ColumnVectorTypeFromColumnType<TA_ColumnType>& T_Column()) {
				
				return std::get<T_ColumnVectorTypeFromColumnType<TA_ColumnType>>(m_ColumnVectorsTuple);
			}

			template<typename TA_ColumnType>
			NCPP_GETTER(const T_ColumnVectorTypeFromColumnType<TA_ColumnType>& T_Column()) const {

				return std::get<T_ColumnVectorTypeFromColumnType<TA_ColumnType>>(m_ColumnVectorsTuple);
			}

			template<size_t TA_Index>
			NCPP_GETTER(T_ColumnVectorType<TA_Index>& T_Column()) {

				return std::get<T_ColumnVectorType<TA_Index>>(m_ColumnVectorsTuple);
			}

			template<size_t TA_Index>
			NCPP_GETTER(const T_ColumnVectorType<TA_Index>& T_Column()) const {

				return std::get<T_ColumnVectorType<TA_Index>>(m_ColumnVectorsTuple);
			}

			NCPP_GETTER(const RowTupleType Row(size_t index)) const {

				RowTupleType rowTuple;

				T_TemplatedFor<GetRowTuple, 0, ColumnCount>((ColumnVectorsTupleType&)m_ColumnVectorsTuple, index, rowTuple);

				return std::move(rowTuple);
			}

			NCPP_SETTER(void SetRow(size_t index, const RowTupleType& rowTuple)) {

				T_TemplatedFor<SetRowTuple, 0, ColumnCount>((ColumnVectorsTupleType&)m_ColumnVectorsTuple, index, rowTuple);

			}



		public:
			NCPP_CONSTEXPR T_C_Table() :
				m_RowCount(0)
			{



			}
			NCPP_CONSTEXPR T_C_Table(size_t rowCount) :
				m_RowCount(rowCount)
			{

				Resize(m_RowCount);

			}
			~T_C_Table() {

				Clear();

			}

			NCPP_CONSTEXPR T_C_Table(const T_C_Table& other) {

				CopyFrom(other);

			}
			NCPP_CONSTEXPR T_C_Table& operator = (const T_C_Table& other) {

				CopyFrom(other);

				return *this;
			}

			NCPP_CONSTEXPR T_C_Table(T_C_Table&& other) {

				MoveFrom(std::forward<T_C_Table>(other));

			}
			NCPP_CONSTEXPR T_C_Table& operator = (T_C_Table&& other) {

				MoveFrom(std::forward<T_C_Table>(other));

				return *this;
			}



		public:
			NCPP_CONSTEXPR void Resize(size_t rowCount) {

				m_RowCount = rowCount;

				T_TemplatedFor<ResizeColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, rowCount);

			}
			NCPP_CONSTEXPR void Clear() {

				m_RowCount = 0;

				T_TemplatedFor<ClearColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple);

			}

			NCPP_CONSTEXPR size_t EmplaceBack(TA_ColumnTypes&&... datas) {

				return EmplaceBack(std::make_tuple(std::forward<TA_ColumnTypes>(datas)...));
			}
			NCPP_CONSTEXPR size_t EmplaceBack(const RowTupleType& rowTuple) {

				Resize(m_RowCount + 1);

				T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, m_RowCount - 1, rowTuple);

				return m_RowCount - 1;
			}
			NCPP_CONSTEXPR void Erase(size_t index) {

				if (m_RowCount != 0) {

					RowTupleType rowTuple;

					T_TemplatedFor<GetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, m_RowCount - 1, rowTuple);

					T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

				}

				Resize(m_RowCount - 1);
			}


			
		private:
			NCPP_CONSTEXPR void CopyFrom(const T_C_Table& other) {

				m_RowCount = other.m_RowCount;

				T_TemplatedFor<CopyColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, (ColumnVectorsTupleType&)other.m_ColumnVectorsTuple);

			}
			NCPP_CONSTEXPR void MoveFrom(T_C_Table&& other) {

				m_RowCount = other.m_RowCount;

				T_TemplatedFor<MoveColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, other.m_ColumnVectorsTuple);

				other.m_RowCount = 0;

			}

		};




		template<typename... TA_ColumnTypes>
		using T_C_DefaultTable = T_C_Table<std::allocator, TA_ColumnTypes...>;

	}

}