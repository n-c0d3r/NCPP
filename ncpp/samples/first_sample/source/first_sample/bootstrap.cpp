#include <ncpp/.hpp>

using namespace ncpp;



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

	aobject a;

	a["i1"] = 3;

	aobject a2 = a;

	std::cout << a2 << std::endl;

	log_memory_stats();

	system("pause");

	return 0;
}