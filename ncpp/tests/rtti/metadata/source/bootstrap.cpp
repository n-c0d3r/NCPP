
#include <ncpp/.hpp>

using namespace ncpp;



class metadata {

	NCPP_RCLASS(
		rtti::default_traits,
		metadata,

		NCPP_PUBLIC(i32, a);
		NCPP_PUBLIC(i32, b);

	);



public:
	metadata() {

		a = 0;
		b = 0;

	}
	~metadata() {



	}

};



#define METADATA_ENABLE_A metadata.a=1;
#define METADATA_DISABLE_A metadata.a=0;
#define METADATA_ENABLE_B metadata.b=1;
#define METADATA_DISABLE_B metadata.b=0;



class rtti_traits {

public:
	using metadata = ::metadata;

	using context_metadata = metadata;
	using member_metadata = metadata;

};



class A {

	NCPP_RCLASS(
		rtti_traits,
		A,

		NCPP_META(
			METADATA_ENABLE_A;
		);

		NCPP_PUBLIC(i32, i,
			METADATA_ENABLE_B;
		);
		NCPP_PUBLIC(eastl::string, str);

	);



public:
	A() {

		i = 3;
		str = "Hello World";

	}
	~A() {



	}

};



int main() {

	A a;
	std::cout << a << std::endl;



#ifdef NCPP_ENABLE_METADATA
	A::rcontext_type ctx;
	ctx.reflect_t(a);

	std::cout << ctx.metadata << std::endl;
	std::cout << ctx.member("i").metadata << std::endl;
#endif



	system("pause");

	return 0;
}