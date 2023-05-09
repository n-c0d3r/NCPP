#include <ncpp/.hpp>

using namespace ncpp;



class bobject :
	public rtti::robject_i
{

	NCPP_RCLASS(bobject);



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

};



class aobject :
	public rtti::robject_i
{

	NCPP_RCLASS(aobject);

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

	aobject() :
		i1(1),
		i2(2)
	{

		NCPP_RCSCOPE(aobject);

	}
	~aobject() {



	}

};

int main() {
	containers::native_vector_t<aobject> v = {
		aobject(),
		aobject()
	};
	std::cout << v << std::endl;
	log_memory_stats();

	system("pause");

	return 0;
}