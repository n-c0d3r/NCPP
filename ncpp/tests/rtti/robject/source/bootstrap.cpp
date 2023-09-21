
#include <ncpp/.hpp>
#include <ncpp/rtti/robject.hpp>

using namespace ncpp;



class B {

	NCPP_RCLASS(
		rtti::default_options,
		B,

		PUBLIC(i32, i)
	);

};



class A {

	NCPP_RCLASS(
		rtti::default_options,
		A,

		BASE(B),

		PUBLIC(i32, i),
		PUBLIC_CONST(void(), foo)
	);

};

void A::foo() {



}



int main() {

	A a;

	A::rcontainer_type rcontainer;

	A::rtti_traits::safe_reflect_t<A>(&rcontainer);

	system("pause");

	return 0;
}