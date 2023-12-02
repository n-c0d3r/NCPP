
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		TF_concurrent_ring_buffer<i32> concurrent_ring_buffer(128);

        for(i32 i = 0; i < 5; ++i) {

            concurrent_ring_buffer.push(i);

        }

        for(i32 i = 0; i < 5; ++i) {

            i32 value;
            concurrent_ring_buffer.try_pop(value);

            cout << T_cout_value(value) << std::endl;

        }

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
