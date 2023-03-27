#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	while(true)
	{

		asz a = 0;

		pac::spinlock lock;

		dop::job entry_job = dop::job(
			[&](dop::job_instance& instance) {

				a.fetch_add(1);

				if (a.load() > 2048) {

					system("pause");

				}

			},
			2048//, 2048
		);



		dop::job_system system(entry_job, 12, 4000, 4000);

		system.run();
		system.wait();



		std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
		std::cout << std::endl;

	}

	std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;
	std::cout << std::endl;

	return 0;
}