#include <ncpp/.hpp>

using namespace ncpp;



class aobject :
	public rtti::robject_i
{

	NCPP_RCLASS(aobject);



public:
	NCPP_RCVARIABLE(
		i32, ivar
	);



public:
	aobject() :
		rtti::robject_i(),

		ivar(0)
	{

		NCPP_REFLECT_CLASS(aobject);

	}
	~aobject() {



	}



public:
	NCPP_RCFUNCTION(
		void(i32, b8), foo
	);

};



void aobject::foo(i32 a, b8 b) {

	std::cout << a << " " << b << std::endl;

}



class bobject :
	public rtti::robject_i
{

	NCPP_RCLASS(bobject);



public:
	bobject() :
		rtti::robject_i()
	{

		NCPP_REFLECT_CLASS(bobject);

	}
	~bobject() {



	}



public:
	NCPP_RCFUNCTION(
		void(i32, b8), foo
	);

};



void bobject::foo(i32 a, b8 b) {

	std::cout << a << " " << b << std::endl;

}



int main() {

	{

		rtti::rclass_t<aobject> aclass;

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}