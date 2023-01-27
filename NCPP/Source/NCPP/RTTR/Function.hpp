#pragma once

#include <NCPP/Utilities.hpp>



namespace NCPP {

	namespace RTTR {

		template<typename TA_FunctionType>
		class T_C_Function;



		template<typename TA_ReturnType, typename... TA_ArgTypes>
		class T_C_Function<TA_ReturnType(TA_ArgTypes...)> {

		public:
			using FunctionType = typename TA_ReturnType(TA_ArgTypes...);
			using FunctorType = std::function<FunctionType>;
			using ReturnType = typename TA_ReturnType;



		private:
			FunctorType m_Functor;



		public:
			NCPP_CONSTEXPR T_C_Function(FunctorType&& functor) :
				m_Functor(std::move(functor))
			{



			}
			template<class TA_C_Object>
			NCPP_CONSTEXPR T_C_Function(
				TA_ReturnType (TA_C_Object::*functor)(TA_ArgTypes...),
				TA_C_Object* p_Object
			):
				m_Functor([functor, p_Object](TA_ArgTypes&&... args)->ReturnType{ return (p_Object->*functor)(std::forward<TA_ArgTypes>(args)...); })
			{



			}
			~T_C_Function() {



			}

			NCPP_CONSTEXPR T_C_Function(const T_C_Function& other) :
				m_Functor(other.m_Functor)
			{



			}
			NCPP_CONSTEXPR T_C_Function& operator = (const T_C_Function& other) {

				m_Functor = other.m_Functor;

				return *this;
			}

			NCPP_CONSTEXPR T_C_Function(T_C_Function&& other) :
				m_Functor(std::move(other.m_Functor))
			{



			}
			NCPP_CONSTEXPR T_C_Function& operator = (T_C_Function&& other) {

				m_Functor = std::move(other.m_Functor);

				return *this;
			}

			NCPP_CONSTEXPR ReturnType operator () (TA_ArgTypes&&... args) {

				return m_Functor(std::forward<TA_ArgTypes>(args)...);
			}

		};

	}

}