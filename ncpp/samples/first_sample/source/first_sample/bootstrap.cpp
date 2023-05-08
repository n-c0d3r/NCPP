#include <ncpp/.hpp>

using namespace ncpp;



class aobject :
	public rtti::robject_i
{

	NCPP_RCLASS(aobject);



public:
	NCPP_RCVARIABLE(
		i32, a
	);
	NCPP_RCVARIABLE(
		i32, b
	);



public:
	aobject() :
		a(1),
		b(2)
	{

		NCPP_RCSCOPE(aobject);

	}
	~aobject() {



	}

	NCPP_RCFUNCTION(
		i32(b8), foo
	);

};

i32 aobject::foo(b8 b) {

	std::cout << b << std::endl;

	return 3;
}



int main() {

	{

		aobject aobj;

		aobj["a"] = 5;
		aobj["b"] = 6;
		aobj["foo"].to_t<i32(b8)>()(1);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}