#include <ncpp/.hpp>

using namespace ncpp;



class A :
	public rtti::robject_i
{

	NCPP_RCLASS(A);



public:
	A()
	{

		NCPP_RCSCOPE(A);

	}
	~A() {



	}

	NCPP_RCFUNCTION(
		i32(f32 f), foo
	);

};

i32 A::foo(f32 f) {

	std::cout << "A " << f << std::endl;

	return 3;
}



int main() {

	{

		A a;    

		std::cout << sizeof(a) << std::endl;

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}