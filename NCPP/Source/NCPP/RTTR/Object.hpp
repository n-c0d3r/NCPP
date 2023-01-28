#pragma once

#include <NCPP/Utilities.hpp>



namespace NCPP {

	namespace RTTR {

		class IC_Class;



		NCPP_CLASS IC_Object {

		public:
			friend class IC_Class;



#pragma region Properties
		private:
			std::function<void()> m_DeletionFunction;
#pragma endregion



#pragma region Getters and Setters
		public:
			NCPP_GETTER(std::function<void()>& DeletionFunction()) { return m_DeletionFunction; }
#pragma endregion



#pragma region Constructors, Destructor, and Operators
		public:
			IC_Object() :
				m_DeletionFunction([this]() {

					delete this;

				})
			{



			}
			virtual ~IC_Object() {



			}

			inline void Release() {

				m_DeletionFunction();
			}
#pragma endregion

		};



		
		template<class TA_C_Object>
		struct T_S_ObjectDelete {

#pragma region Constructors, Destructor, and Operators
			constexpr T_S_ObjectDelete() noexcept = default;

			T_S_ObjectDelete(const T_S_ObjectDelete<TA_C_Object>& d) noexcept {



			}

			void operator()(TA_C_Object* p_Object) const {

				p_Object->Release();

			}
#pragma endregion

		};



		template<class TA_C_Object>
		using T_C_UniqueObjectPtr = std::unique_ptr<TA_C_Object, T_S_ObjectDelete<TA_C_Object>>;

		template<class TA_C_Object>
		using T_C_SharedObjectPtr = std::shared_ptr<TA_C_Object>;

		template<class TA_C_Object>
		using T_C_WeakObjectPtr = std::weak_ptr<TA_C_Object>;

		template<class TA_C_Object, typename... TA_ArgTypes>
		NCPP_CONSTEXPR T_C_UniqueObjectPtr<TA_C_Object> T_MakeUnique(TA_ArgTypes&&... args) {

			return T_C_UniqueObjectPtr<TA_C_Object>(std::forward<TA_ArgTypes>(args)...);
		}

		template<class TA_C_Object, typename... TA_ArgTypes>
		NCPP_CONSTEXPR T_C_SharedObjectPtr<TA_C_Object> T_MakeShared(TA_ArgTypes&&... args) {

			return T_C_SharedObjectPtr<TA_C_Object>(std::forward<TA_ArgTypes>(args)..., T_S_ObjectDelete<TA_C_Object>());
		}

		template<class TA_C_Object, typename... TA_ArgTypes>
		NCPP_CONSTEXPR T_C_WeakObjectPtr<TA_C_Object> T_MakeWeak(TA_ArgTypes&&... args) {

			return T_C_WeakObjectPtr<TA_C_Object>(std::forward<TA_ArgTypes>(args)..., T_S_ObjectDelete<TA_C_Object>());
		}
		
	}

}