
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		containers::TF_concurrent_ring_buffer<i32> concurrent_ring_buffer(128);

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
