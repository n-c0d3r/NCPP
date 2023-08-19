#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		containers::fixed_buffer_t<4> buffer;

		buffer.set_t<i32>(0, 5);

		std::cout << buffer.get_t<i32>(0) << std::endl;

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}