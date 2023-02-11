#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	dop::cbjs({

		dop::job {

			[](dop::job_coroutine& coroutine) {

				

			}

		}

	});

	std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl;

	return 0;
}