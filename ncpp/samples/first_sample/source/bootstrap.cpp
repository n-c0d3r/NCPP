
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		eastl::vector<eastl::string> v = { 
			"Hello World",
			"ABCDEF"
		};

		std::cout << v << std::endl;

		log_memory_stats();

	}



	system("pause");

	return 0;
}