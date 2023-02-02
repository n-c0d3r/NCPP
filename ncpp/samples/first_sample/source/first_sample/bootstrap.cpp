#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		cbjs::job entry_job = {

			[](cbjs::job& job, cbjs::coroutine& coroutine) {

				std::vector<cbjs::job> job_vector;
							
				for (int i = 0; i < 2048; ++i) {

					job_vector.push_back(std::move(cbjs::job{

						[](cbjs::job& job, cbjs::coroutine& coroutine) {
							
							std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;

						}

					}));

				}

				for (int i = 0; i < job_vector.size(); ++i) {

					cbjs::system::instance().worker_thread(i % 12).schedule(job_vector[i]);

				}

				for (int i = 0; i < job_vector.size(); ++i) {

					coroutine.yield_t<cbjs::wait_job_done>(job_vector[i]);

				}

			}

		};

		cbjs::system job_system({

			entry_job

		});

		job_system.start();

	}

	std::cout << "memory remain: " << memory_usage() << "(bytes)" << std::endl;

	return 0;
}