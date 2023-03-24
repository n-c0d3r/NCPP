#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	/// while(true)
	{

		dop::job entry_job = dop::job(
			[&](dop::job_instance& instance) {

				std::cout << "Hello World" << std::endl;

			}
		);



		dop::job_system system(
			entry_job
		);

		system.run();
		system.wait();



		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}