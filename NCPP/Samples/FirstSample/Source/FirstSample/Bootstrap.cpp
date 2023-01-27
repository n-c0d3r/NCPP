#include <NCPP/NCPP.hpp>



class A {

public:
	A() {



	}

	int F(bool c, float b) {

		std::cout << c << " " << b << std::endl;

		return 5;
	}

};



int F(bool c, float b) {

	std::cout << c << " " << b << std::endl;

	return 5;
}



int main() {

	A a;

	NCPP::RTTR::T_C_Function<int(bool, float)> f(F);

	f(1, 2.5f);

	return 0;
}