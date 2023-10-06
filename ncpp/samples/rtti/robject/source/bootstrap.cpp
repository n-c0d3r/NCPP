
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

	A::F_rcontainer rcontainer;

	A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer);

	system("pause");

	return 0;
}
