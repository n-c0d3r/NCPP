#include <NCPP/NCPP.hpp>



template<typename... TA_Args>
void T_Foo() {

	std::cout << NCPP::T_TemplateArgCount<TA_Args...>() << std::endl;

}



int main() {

	T_Foo<int, bool, float, double>();

	return 0;
}