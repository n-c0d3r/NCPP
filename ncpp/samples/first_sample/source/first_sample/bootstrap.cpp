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
		rtti::robject_i()
	{

		NCPP_REFLECT_CLASS(aobject);

	}
	~aobject() {



	}



public:
	NCPP_RCFUNCTION(
		void(i32, b8), foo,
		1,
		4,
		8
	);

};



void aobject::foo(i32 a, b8 b) {

	std::cout << a << " " << b << std::endl;

}



int main() {

	{

		aobject aobj;

		for (sz arg : aobj.get_rfunction_handle("foo").args_array) {

			std::cout << arg << std::endl;

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}