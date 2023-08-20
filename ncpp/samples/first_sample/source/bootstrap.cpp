#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		i32 d = 9;

		auto foo2 = [](i32 a) {

			std::cout << a << std::endl;

		};

		native_function_t<void(i32)> f = foo2;
		f(8);

		native_function_t<void(i32)> f2 = std::move(f);
		f2(2);

		native_function_t<void(i32)> f3 = f2;
		f3(5);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}