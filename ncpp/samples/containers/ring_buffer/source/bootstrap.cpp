
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		containers::TF_ring_buffer<i32> ring_buffer(8);

		ring_buffer.push(5);
		ring_buffer.push(6);
		ring_buffer.push(7);
		ring_buffer.push(8);

        NCPP_INFO() << ring_buffer;

		NCPP_INFO() << ring_buffer.pop();
		NCPP_INFO() << ring_buffer.pop();
		NCPP_INFO() << ring_buffer.pop();
		NCPP_INFO() << ring_buffer.pop();
		NCPP_INFO() << ring_buffer.try_pop(T_null_reference<i32>());

        NCPP_INFO() << ring_buffer;

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}