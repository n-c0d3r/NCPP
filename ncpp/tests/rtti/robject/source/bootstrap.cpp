
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

		NCPP_PUBLIC_VIRTUAL(i32(b8), foo);
		NCPP_PUBLIC_CONST(i32(b8), foo2);

	);



public:
	A() {

		i = 3;
		str = "Hello World";

	}
	~A() {



	}

};

NCPP_DEFINE_VIRTUAL(A, foo, i32, b8) { 

	std::cout << "Hello A" << std::endl;
	
	return 0; 
}
i32 A::foo2(b8) {

	std::cout << "Hello A 2" << std::endl;

	return 0;
}



int main() {

	A a;

	std::cout << a << std::endl;

	const A& ar = a;
	ar.foo2(true);

#ifdef NCPP_ENABLE_RTTI
	A::rcontext_type ctx;
	ctx.reflect_t(a);
	ctx.member("foo").invoke_t<i32(b8)>(&a, true);
	std::cout << ctx.member("i").cast_to_t<i32>(&a) << std::endl;
	std::cout << ctx.member("i").is_type_t<i32>() << std::endl;
#endif

	system("pause");

	return 0;
}