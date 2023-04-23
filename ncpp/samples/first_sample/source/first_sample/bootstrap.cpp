#include <ncpp/.hpp>

using namespace ncpp;



class A {

	int a[4000];

};



int main() {

	{



		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}