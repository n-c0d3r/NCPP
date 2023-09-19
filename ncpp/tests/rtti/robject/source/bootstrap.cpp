
#include <ncpp/.hpp>
#include <ncpp/rtti/robject.hpp>

using namespace ncpp;



class A {

	NCPP_RCLASS(
		rtti::default_options,
		A,
		PUBLIC(
			i32,
			i
		)
	);

};



int main() {

	A a;

	A::rcontainer_type rcontainer;

	A::static_reflect(rcontainer);



	system("pause");

	return 0;
}