#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	while (true) {

		{
			dop::job entry_job = dop::job(
				[&entry_job](u32 index, dop::job_coroutine& coroutine) {

					//std::cout << index << " " << pac::current_thread_index() << std::endl;

				},
				9000,
				512
			);



			dop::cbjs({

				entry_job,
				12,
				4000

			});

		}

		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	return 0;
}