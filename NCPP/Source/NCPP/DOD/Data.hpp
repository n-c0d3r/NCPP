#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/TemplatedFor.hpp>
#include <NCPP/FirstTemplateArg.hpp>



namespace NCPP {

	namespace DOD {
				
		template<
			template<typename TA_ColumnType> class TA_T_C_Allocator,
			template<typename TA_ColumnType> typename TA_T_IdHash,
			template<typename TA_ColumnType> typename TA_T_IdEqualTo,
			typename... TA_ColumnTypes
		>
		NCPP_CLASS
		T_C_Data final {

#pragma region Typedefs
		public:
			using ColumnVectorsTupleType = typename std::tuple<std::vector<TA_ColumnTypes, TA_T_C_Allocator<TA_ColumnTypes>>...>;
			using RowTupleType = typename std::tuple<TA_ColumnTypes...>;
			using IteratorMapType = typename std::unordered_map<size_t, size_t, TA_T_IdHash<size_t>, TA_T_IdEqualTo<size_t>, TA_T_C_Allocator<std::pair<const size_t, size_t>>>;

			using FirstColumnType = typename T_S_FirstTemplateArg<TA_ColumnTypes...>::Type;

			static const size_t ColumnCount = std::tuple_size_v<ColumnVectorsTupleType>;

			template<size_t TA_Index>
			using T_ColumnType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>::value_type;

			template<size_t TA_Index>
			using T_ColumnAllocatorType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>::allocator_type;

			template<size_t TA_Index>
			using T_ColumnVectorType = typename std::tuple_element_t<TA_Index, ColumnVectorsTupleType>;

			template<typename TA_ColumnType>
			using T_ColumnVectorTypeFromColumnType = typename std::vector<TA_ColumnType, TA_T_C_Allocator<TA_ColumnType>>;
#pragma endregion



#pragma region Properties
		private:
			ColumnVectorsTupleType m_ColumnVectorsTuple;

			size_t m_RowCount;

			IteratorMapType m_Id2IndexMap;
			IteratorMapType m_Index2IdMap;
#pragma endregion



#pragma region Getters and Setters
		public:
			NCPP_GETTER(size_t RowCount()) const { return m_RowCount; }

			// Note: only travel first column!
			NCPP_GETTER(typename T_ColumnVectorType<0>::iterator begin()) { return T_Column<FirstColumnType>().begin(); }
			NCPP_GETTER(typename T_ColumnVectorType<0>::iterator end()) { return T_Column<FirstColumnType>().end(); }
			NCPP_GETTER(typename T_ColumnVectorType<0>::const_iterator begin()) const { return T_Column<FirstColumnType>().begin(); }
			NCPP_GETTER(typename T_ColumnVectorType<0>::const_iterator end()) const { return T_Column<FirstColumnType>().end(); }

			NCPP_GETTER(size_t Id2Index(size_t id)) const { return m_Id2IndexMap.find(id)->second; }
			NCPP_GETTER(size_t Index2Id(size_t index)) const { return m_Index2IdMap.find(index)->second; }

			NCPP_GETTER(bool IsHasRow(size_t id)) const { return m_Id2IndexMap.find(id) != m_Id2IndexMap.end(); }

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

				T_TemplatedFor<GetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

				return std::move(rowTuple);
			}

			NCPP_SETTER(void SetRow(size_t index, const RowTupleType& rowTuple)) {

				T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

			}
#pragma endregion



#pragma region Constructors, Destructor, and Operators
		public:
			NCPP_CONSTEXPR T_C_Data() :
				m_RowCount(0)
			{



			}
			NCPP_CONSTEXPR T_C_Data(size_t rowCount) :
				m_RowCount(rowCount)
			{

				Resize(m_RowCount);

			}
			~T_C_Data() {

				Clear();

			}

			NCPP_CONSTEXPR T_C_Data(const T_C_Data& other) {

				CopyFrom(other);

			}
			NCPP_CONSTEXPR T_C_Data& operator = (const T_C_Data& other) {

				CopyFrom(other);

				return *this;
			}

			NCPP_CONSTEXPR T_C_Data(T_C_Data&& other) {

				MoveFrom(std::forward<T_C_Data>(other));

			}
			NCPP_CONSTEXPR T_C_Data& operator = (T_C_Data&& other) {

				MoveFrom(std::forward<T_C_Data>(other));

				return *this;
			}
#pragma endregion



#pragma region Methods
		public:
			NCPP_CONSTEXPR void Resize(size_t rowCount) {

				m_RowCount = rowCount;

				T_TemplatedFor<ResizeColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, rowCount);

			}
			NCPP_CONSTEXPR void Clear() {

				m_RowCount = 0;
				m_Id2IndexMap.clear();
				m_Index2IdMap.clear();

				T_TemplatedFor<ClearColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple);

			}

			NCPP_CONSTEXPR size_t EmplaceBack(const TA_ColumnTypes&... datas) {

				return EmplaceBack(std::make_tuple(datas...));
			}
			NCPP_CONSTEXPR size_t EmplaceBack(const RowTupleType& rowTuple) {

				Resize(m_RowCount + 1);

				size_t index = m_RowCount - 1;

				T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

				size_t id = CreateId(m_Id2IndexMap, index);

				m_Index2IdMap[id] = index;

				return id;
			}
			NCPP_CONSTEXPR size_t EmplaceBackWithId(size_t id, const TA_ColumnTypes&... datas) {

				return EmplaceBackWithId(id, std::make_tuple(datas...));
			}
			NCPP_CONSTEXPR size_t EmplaceBackWithId(size_t id, const RowTupleType& rowTuple) {

				Resize(m_RowCount + 1);

				size_t index = m_RowCount - 1;

				T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

				m_Index2IdMap[id] = index;

				return id;
			}
			NCPP_CONSTEXPR void Erase(size_t id) {

				size_t index = m_Id2IndexMap[id];

				if (m_RowCount != 1) {

					size_t lastIndex = m_RowCount - 1;

					RowTupleType rowTuple;

					T_TemplatedFor<GetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, lastIndex, rowTuple);

					T_TemplatedFor<SetRowTuple, 0, ColumnCount>(m_ColumnVectorsTuple, index, rowTuple);

					size_t lastId = m_Index2IdMap[lastIndex];
					m_Id2IndexMap[lastId] = index;

					m_Index2IdMap.erase(lastIndex);

				}

				DeleteId(m_Id2IndexMap, id);

				Resize(m_RowCount - 1);
			}


				
		private:
			NCPP_CONSTEXPR void CopyFrom(const T_C_Data& other) {

				m_RowCount = other.m_RowCount;

				T_TemplatedFor<CopyColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, (ColumnVectorsTupleType&)other.m_ColumnVectorsTuple);

			}
			NCPP_CONSTEXPR void MoveFrom(T_C_Data&& other) {

				m_RowCount = other.m_RowCount;

				T_TemplatedFor<MoveColumnVectors, 0, ColumnCount>(m_ColumnVectorsTuple, other.m_ColumnVectorsTuple);

				other.m_RowCount = 0;

			}



		private:
			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, ClearColumnVectors, (ColumnVectorsTupleType& tuple),
				{

					typename T_C_Data::T_ColumnVectorType<TA_Index>&vector = std::get<TA_Index>(tuple);

					vector.clear();

				}
			)

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, ResizeColumnVectors, (ColumnVectorsTupleType& tuple, size_t newRowCount),
				{

					typename T_C_Data::T_ColumnVectorType<TA_Index>&vector = std::get<TA_Index>(tuple);

					vector.resize(newRowCount);

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, CopyColumnVectors, (ColumnVectorsTupleType& tupleDst, ColumnVectorsTupleType& tupleSrc),
				{

					typename T_C_Data::T_ColumnVectorType<TA_Index>&vector1 = std::get<TA_Index>(tupleDst);
					typename T_C_Data::T_ColumnVectorType<TA_Index>& vector2 = std::get<TA_Index>(tupleSrc);

					vector1 = vector2;

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, MoveColumnVectors, (ColumnVectorsTupleType& tupleDst, ColumnVectorsTupleType& tupleSrc),
				{

					typename T_C_Data::T_ColumnVectorType<TA_Index>&vector1 = std::get<TA_Index>(tupleDst);
					typename T_C_Data::T_ColumnVectorType<TA_Index>& vector2 = std::get<TA_Index>(tupleSrc);

					vector1 = std::move(vector2);
					vector2.clear();

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, SetRowTuple, (ColumnVectorsTupleType& tuple, size_t rowIndex, const RowTupleType& rowTuple),
				{

					std::get<typename T_C_Data::T_ColumnVectorType<TA_Index>>(tuple)[rowIndex] = std::get<TA_Index>(rowTuple);

				}
			);

			template<size_t TA_Index>
			NCPP_SFUNCTION(
				NCPP_CONSTEXPR void, GetRowTuple, (const ColumnVectorsTupleType& tuple, size_t rowIndex, RowTupleType& rowTuple),
				{

					std::get<TA_Index>(rowTuple) = std::get<TA_Index>(tuple)[rowIndex];

				}
			);

			static NCPP_CONSTEXPR Id CreateId(
				IteratorMapType& map,
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

				return CreateId(map, data);
			}

			static NCPP_CONSTEXPR void DeleteId(
				IteratorMapType& map,
				Id id
			)
			{

				map.erase(id);
			}
#pragma endregion

		};



		template<typename... TA_ColumnTypes>
		using T_C_StandardData = T_C_Data<std::allocator, std::hash, std::equal_to, TA_ColumnTypes...>;



#define NCPP_DOD_DATA_TRAVEL(Iterator, Data, ColumnIndex) \
		for(auto Iterator = Data.T_Column<typename std::remove_reference_t<decltype(Data)>::T_ColumnType<0>>().begin(); Iterator != Data.T_Column<typename std::remove_reference_t<decltype(Data)>::T_ColumnType<0>>().end(); ++Iterator)
		

	}

}