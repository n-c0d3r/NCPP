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

				ecs::component_system_t<int> system(4, 128);

				for (u32 i = 0; i < 4; ++i) {

					system.insert(i);
					
				}

				system.process_data(
					job,
					coroutine,
					0,
					[&system](cbjs::job& job, cbjs::coroutine& coroutine, u32 begin, u32 end) {

						if(begin == 0)
							system.thread_safe_erase(begin);

					}
				);

				system.recorrect_data(job, coroutine, 0);

				std::cout << "memory usage: " << memory_usage() << "(bytes)" << std::endl;

			}

		};

		cbjs::system job_system({

			entry_job

		});

		job_system.start();

	}

	std::cout << "unreleased memory: " << memory_usage() << "(bytes)" << std::endl;

	return 0;
}