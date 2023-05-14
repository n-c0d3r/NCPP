#include <ncpp/.hpp>

using namespace ncpp;



class A :
	public rtti::robject_i
{

	NCPP_RCLASS(A);



public:
	NCPP_RCVARIABLE(
		i32, i
	);



public:
	A() :
		i(1)
	{

		NCPP_RCSCOPE(A);

	}
	~A() {



	}

	NCPP_RCFUNCTION(
		i32(f32), foo
	);

};

i32 A::foo(f32 f) {

	std::cout << f << std::endl;

	return 3;
}



int main() {

	auto aclass = A::get_static_class();

	auto a_p = aclass.create_unique_instance();

	auto foo_executer = a_p->func_t<i32(f32)>("foo");

	foo_executer.to_functor()(3.5f);

	log_memory_stats();

	system("pause");

	return 0;
}