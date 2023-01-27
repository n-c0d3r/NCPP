#include <NCPP/NCPP.hpp>



template<typename... TA_Args>
void T_Foo() {

	using Type = typename NCPP::T_S_LastTemplateArg<TA_Args...>::Type;

	std::cout << typeid(Type).name() << std::endl;

}



int main() {

	T_Foo<int, bool, float, double>();

	return 0;
}