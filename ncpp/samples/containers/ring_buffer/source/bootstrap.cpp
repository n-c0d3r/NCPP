
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		containers::TF_ring_buffer<i32> ring_buffer(8);

		ring_buffer.push(5);
		ring_buffer.push(6);
		ring_buffer.push(7);
		ring_buffer.push(8);

        cout << ring_buffer << ncpp::endl;

		std::cout << ring_buffer.pop() << ncpp::endl;
		std::cout << ring_buffer.pop() << ncpp::endl;
		std::cout << ring_buffer.pop() << ncpp::endl;
		std::cout << ring_buffer.pop() << ncpp::endl;
		std::cout << ring_buffer.try_pop(T_null_reference<i32>()) << ncpp::endl;

        cout << ring_buffer << ncpp::endl;

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}