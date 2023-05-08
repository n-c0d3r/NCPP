#include <ncpp/.hpp>

using namespace ncpp;



class bobject :
	public rtti::robject_i
{

	NCPP_RCLASS(bobject)



public:
	NCPP_RCVARIABLE(
		i32, i1
	);
	NCPP_RCVARIABLE(
		i32, i2
	);



public:
	bobject() :
		i1(1),
		i2(2)
	{

		NCPP_RCSCOPE(bobject);

	}
	~bobject() {



	}

	NCPP_RCCOPY(const bobject&, other) {

		i1 = (other.i1);
		i2 = (other.i2);

	}

};



class cobject :
	public rtti::robject_i
{

	NCPP_RCLASS(cobject)



public:
	NCPP_RCVARIABLE(
		i32, i3
	);
	NCPP_RCVARIABLE(
		i32, i4
	);



public:
	cobject() :
		i3(3),
		i4(4)
	{

		NCPP_RCSCOPE(cobject);

	}
	~cobject() {



	}
	
	NCPP_RCCOPY(const cobject&, other) {

		i3 = (other.i3);
		i4 = (other.i4);

	}

};



class aobject :
	public cobject
{

	NCPP_RCLASS(aobject)



public:
	NCPP_RCVARIABLE(
		i32, i1
	);
	NCPP_RCVARIABLE(
		i32, i2
	);
	NCPP_RCVARIABLE(
		bobject, b
	);



public:
	aobject() :
		i1(1),
		i2(2)
	{

		NCPP_RCSCOPE(aobject);

	}
	~aobject() {



	}
	
	NCPP_RCCOPY(const aobject&, other) {

		i1 = (other.i1);
		i2 = (other.i2);
		b = (other.b);

		cobject::copy_from(other);

	}

};



int main() {

	{

		aobject a1;
		a1.i1 = 5;
		a1.i3 = 19;
		aobject a2 = a1;

		std::cout << a1 << std::endl;
		std::cout << a2 << std::endl;

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}