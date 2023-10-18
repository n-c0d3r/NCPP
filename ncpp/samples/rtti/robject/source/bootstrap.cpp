
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

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer);

	pause_console();

	return 0;
}
