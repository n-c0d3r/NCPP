#include <ncpp/.hpp>

using namespace ncpp;



class aobject :
	public rtti::robject_i
{

	NCPP_RCLASS(aobject)



public:
	NCPP_RCVARIABLE(
		i32, a,
		1, 
		2
	)



public:
	aobject() :
		rtti::robject_i(),

		a(0)
	{

		NCPP_REFLECT_CLASS()

	}
	~aobject() {



	}

};



int main() {

	{

		rtti::rclass aclass = aobject::get_static_rclass();

		utilities::native_shared_ptr_t<aobject> aobj1 = utilities::native_shared_ptr_cast_t<aobject>(aclass.create_shared_instance());

		aobj1->get_rvariable_t<i32>("a") = 3;

		for (sz var_arg : aobj1->get_rvariable_handle("a").args_array) {

			std::cout << var_arg << std::endl;

		}

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}