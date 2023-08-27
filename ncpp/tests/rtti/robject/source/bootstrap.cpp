
#include <ncpp/.hpp>
#include <ncpp/rtti/robject.hpp>

using namespace ncpp;



class B {

	NCPP_RCLASS(
		rtti::default_traits,
		B,

		NCPP_PUBLIC(i32, i2);

	);



public:
	B() {

		i2 = 9;

	}
	~B() {



	}

};



class A : public B {

	NCPP_RCLASS(
		rtti::default_traits,
		A,

		NCPP_BASE(B);

		NCPP_PUBLIC(i32, i);
		NCPP_PUBLIC(eastl::string, str);

		NCPP_PUBLIC(i32(b8), foo);

	);



public:
	A() {

		i = 3;
		str = "Hello World";

	}
	~A() {



	}

};

i32 A::foo(b8) { return 0; }



int main() {

	A a;

	std::cout << a << std::endl;

	system("pause");

	return 0;
}