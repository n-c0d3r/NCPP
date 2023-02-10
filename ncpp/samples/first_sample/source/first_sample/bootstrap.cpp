#include <ncpp/.hpp>

using namespace ncpp;



void foo() {




	pac::thread wt([&]() {

		while (true);

		});

	pac::fiber f([&](pac::fiber& f) {

		std::cout << "ok" << std::endl;

		});

	f.switch_to_this();

	while (true);


}



int main() {

	{

		dop::cbjs({

			dop::job(

				[](dop::coroutine& coroutine) {

					std::cout << "hello world" << std::endl;

					std::cout << "hello world" << std::endl;

				}

			),

			2

		});
		
	}

	std::cout << "memory usage: " << memory_usage() << " (bytes)" << std::endl;

	return 0;
}