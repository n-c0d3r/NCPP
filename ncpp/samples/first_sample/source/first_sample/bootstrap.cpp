#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

#ifdef NCPP_ENABLE_NATIVE_MEMORY_COUNTING
		std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
		std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
#endif
		std::cout << std::endl;

	}

#ifdef NCPP_ENABLE_NATIVE_MEMORY_COUNTING
	std::cout << "native allocated memory: " << native_allocated_memory() << "(bytes)" << std::endl;
	std::cout << "native used heap memory: " << native_used_heap_memory() << "(bytes)" << std::endl;
#endif
	std::cout << std::endl;

	system("pause");

	return 0;
}