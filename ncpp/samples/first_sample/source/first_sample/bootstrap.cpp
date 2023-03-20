#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	while (true) {

		{
			dop::job entry_job = dop::job(
				[&entry_job](u32 index, dop::job_coroutine& coroutine) {

					std::cout << pac::current_thread_index() << std::endl;

				},
				1
			);



			dop::cbjs({

				entry_job,
				2,
				2

			});

		}

		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	return 0;
}