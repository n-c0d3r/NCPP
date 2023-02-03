#include <ncpp/.hpp>

using namespace ncpp;



struct transform {



};



int main() {

	{

		cbjs::job entry_job = {

			[](cbjs::job& job, cbjs::coroutine& coroutine) {

				containers::handle_multimap<int> multimap(4, 16);

				auto map0 = multimap.insert_new();
				auto map1 = multimap.insert_new();
				auto map2 = multimap.insert_new();

				multimap[0].insert(0);
				multimap[0].insert(1);
				multimap[0].insert(2);

				std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;

			}

		};

		cbjs::system job_system({

			entry_job,
			1

		});

		job_system.start();

	}

	std::cout << "unreleased memory: " << memory_usage() << "(bytes)" << std::endl;

	return 0;
}