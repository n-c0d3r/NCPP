
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

		a = 3;
		b = 9;

	}
	~metadata() {



	}

};



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

		NCPP_META(metadata.a = 4; metadata.b = 16;);

		NCPP_PUBLIC(i32, i, metadata.a = 2; metadata.b = 8;);
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

	system("pause");

	return 0;
}