#include <ncpp/.hpp>

using namespace ncpp;



class aobject :
	public rtti::robject_i
{

	NCPP_RCLASS(aobject);



public:
	NCPP_RCVARIABLE(i32, a);
	NCPP_RCVARIABLE(i32, b);
	NCPP_RCVARIABLE(b8, c);



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
		void, 
		foo, 
		NCPP_MP_GROUP(i32, b8)
	);

};



void aobject::foo(i32 a, b8 b) {

	std::cout << a << " " << b << std::endl;

}



int main() {

	{

		aobject aobj;

		aobj.get_rfunction<void(i32, b8)>("foo")(3, true);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}