
#include <ncpp/.hpp>

using namespace ncpp;



class B {

	NCPP_ROBJECT(

		B,

		NCPP_ENABLE_VIRTUAL();

		NCPP_PUBLIC_V(i32, a);
		NCPP_PUBLIC_V(i32, b);

	);



public:
	B() {

		a = 3;
		b = 4;

	}
	~B() {



	}

};



class A : public B {
	
	NCPP_ROBJECT(

		A,

		NCPP_ENABLE_VIRTUAL();

		NCPP_BASE(B);
		
		NCPP_PUBLIC_V(i32, c);
		NCPP_PUBLIC_V(i32, d);
		NCPP_PUBLIC_V(eastl::string, f);
		NCPP_PUBLIC_V(B, b);

		NCPP_PUBLIC_F(i32(i32), e);

	);



public:
	A() : B() {

		c = 1;
		d = 2;
		f = "Hello World";

	}
	~A() {



	}

};



i32 A::e(i32 d) {
	
	return d + c;
}



int main() {
	
	{

		A a;
		B b;

		std::cout << a << std::endl;
		std::cout << b << std::endl;



		B* a_p = &a;
		B* b_p = &b;

		std::cout << *a_p << std::endl;
		std::cout << *b_p << std::endl;



		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}