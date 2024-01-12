
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		TG_concurrent_ring_buffer<i32> concurrent_ring_buffer(8);

        for(i32 i = 0; i < 5; ++i) {

            concurrent_ring_buffer.push(i);

        }

        NCPP_INFO() << concurrent_ring_buffer;

        for(i32 i = 0; i < 5; ++i) {

            i32 value;
            concurrent_ring_buffer.try_pop(value);

            NCPP_INFO() << T_cout_value(value);

        }

        NCPP_INFO() << concurrent_ring_buffer;

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
