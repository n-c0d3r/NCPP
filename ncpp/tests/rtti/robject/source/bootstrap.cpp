
#include <ncpp/.hpp>
#include <ncpp/rtti/robject.hpp>

using namespace ncpp;



struct A {
	
	NCPP_ROBJECT(

		A,

		NCPP_PUBLIC(i32, a);
		NCPP_PUBLIC(i32, b);

	);

};



int main() {
	
	{
		
		rtti::rcontext ctx;

		ctx.reflect_t<A>();

		std::cout << sizeof(A) << std::endl;



		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}