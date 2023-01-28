#pragma once

#include <NCPP/Utilities.hpp>
#include <NCPP/RTTR/Object.hpp>



namespace NCPP {

	namespace RTTR {

		template<
			class TA_C_Object,
			template<typename TA_Type> class TA_T_C_Allocator
		>
		NCPP_CLASS T_C_Class;


		NCPP_CLASS IC_Class {

#pragma region Constructors, Destructor, and Operators
		public:
			NCPP_CONSTEXPR IC_Class()
			{



			}
			~IC_Class() {



			}
#pragma endregion



#pragma region Methods
		public:
			virtual IC_Object* CreateInstance() {

				return 0;
			}

			template<
				class TA_C_Object,
				template<typename TA_Type> class TA_T_C_Allocator
			>
			void T_SetupObject(
				TA_C_Object* p_Object,
				T_C_Class<TA_C_Object, TA_T_C_Allocator>* p_Class
			);
#pragma endregion

		};



		template<
			class TA_C_Object,
			template<typename TA_Type> class TA_T_C_Allocator
		>
		NCPP_CLASS T_C_Class :
			public IC_Class
		{

#pragma region Typedefs
		public:
			using C_Object = TA_C_Object;
			using C_Allocator = TA_T_C_Allocator<C_Object>;
#pragma endregion



#pragma region Properties
		private:
			C_Allocator m_Allocator;
#pragma endregion



#pragma region Getters and Setters
		public:
			NCPP_GETTER(C_Allocator& Allocator()) { return m_Allocator; }
			NCPP_GETTER(const C_Allocator& Allocator()) const { return m_Allocator; }
#pragma endregion



#pragma region Constructors, Destructor, and Operators
		public:
			NCPP_CONSTEXPR T_C_Class() :
				IC_Class()
			{



			}
			~T_C_Class() {



			}

			NCPP_CONSTEXPR T_C_Class(const T_C_Class& other)
			{



			}
			NCPP_CONSTEXPR T_C_Class& operator = (const T_C_Class& other) {



				return *this;
			}

			NCPP_CONSTEXPR T_C_Class(T_C_Class&& other)
			{



			}
			NCPP_CONSTEXPR T_C_Class& operator = (T_C_Class&& other) {



				return *this;
			}
#pragma endregion



#pragma region Methods
		public:
			IC_Object* CreateInstance() {

				C_Object* ptr = m_Allocator.allocate(1);
			
				new(ptr) C_Object();

				T_SetupObject<TA_C_Object, TA_T_C_Allocator>(ptr, this);

				return ptr;
			}
#pragma endregion

		};



		template<
			class TA_C_Object,
			template<typename TA_Type> class TA_T_C_Allocator
		>
		void IC_Class::T_SetupObject(
			TA_C_Object* p_Object, 
			T_C_Class<TA_C_Object, TA_T_C_Allocator>* p_Class
		) {

			p_Object->m_DeletionFunction = [p_Class, p_Object]() {

				p_Object->~TA_C_Object();

				p_Class->Allocator().deallocate(p_Object, 1);
			
			};

		}



		template<
			class TA_C_Object
		>
		using T_C_StandardClass = class T_C_Class<TA_C_Object, std::allocator>;


	}

}