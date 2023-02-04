#include <ncpp/.hpp>

using namespace ncpp;



struct transform {



};



int main() {

	{

		cbjs::job entry_job = {

			[](cbjs::job& job, cbjs::coroutine& coroutine) {

				{

					containers::handle_multimap_t<int> multimap1(4, 16);

					multimap1[0].insert(0);
					multimap1[0].insert(1);
					multimap1[0].insert(2);
					multimap1[1].insert(3);
					multimap1[1].insert(4);

					containers::handle_multimap_t<int> multimap2 = std::move(multimap1);

				}

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