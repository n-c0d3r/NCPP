
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{
		containers::TF_owf_stack<i32> owf_stack(8);

		owf_stack.push(5);
		owf_stack.push(6);
		owf_stack.push(7);
		owf_stack.push(8);

        NCPP_INFO() << owf_stack;
	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}