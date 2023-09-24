
#include <ncpp/rtti/.hpp>

using namespace ncpp;



class A {

	NCPP_BASIC_RCLASS(
		A,

		PUBLIC(i32, i),
		PUBLIC_CONST(void(), foo)
	);

};

void A::foo() {



}



int main() {

	A a;

	A::rcontainer_type rcontainer;

	A::rtti_traits::template safe_reflect_t<A>(&rcontainer);

	system("pause");

	return 0;
}