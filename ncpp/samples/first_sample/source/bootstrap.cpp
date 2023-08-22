
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		eastl::vector<i32> v = { 1, 2, 3 };

		std::cout << v << std::endl;

		log_memory_stats();

	}



	system("pause");

	return 0;
}