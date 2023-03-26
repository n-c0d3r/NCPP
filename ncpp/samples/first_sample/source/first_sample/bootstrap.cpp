#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	/// while(true)
	{

		dop::job entry_job(
			[&](dop::job_instance& instance) {

				std::cout << instance.instance_index() << std::endl;

			},
			2048
		);



		dop::job_system system(entry_job);

		system.run();
		system.wait();



		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}