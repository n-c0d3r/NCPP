#include <ncpp/.hpp>

using namespace ncpp;



struct ddata {



};



class bobject :
	public rtti::robject_i
{

	NCPP_RCLASS(bobject);



public:
	NCPP_RCVARIABLE(
		i32, a
	);
	NCPP_RCVARIABLE(
		i32, b
	);
	NCPP_RCVARIABLE(
		ddata, c
	);



public:
	bobject() :
		a(4),
		b(5)
	{

		NCPP_RCSCOPE(bobject);

	}
	~bobject() {



	}

};



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
	NCPP_RCVARIABLE(
		bobject, c
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

		std::cout << aobj << std::endl;

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}