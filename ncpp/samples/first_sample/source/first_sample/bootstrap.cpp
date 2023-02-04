#include <ncpp/.hpp>

using namespace ncpp;



struct NCPP_SET_ALIGN(16) position {

	f32 x;
	f32 y;
	f32 z;

};
struct NCPP_SET_ALIGN(16) rotation {

	f32 x;
	f32 y;
	f32 z;
	f32 w;

};

struct NCPP_SET_ALIGN(16) transform {

	position pos;
	rotation rot;

};



int main() {

	{

		cbjs::job entry_job = {

			[](cbjs::job& job, cbjs::coroutine& coroutine) {

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