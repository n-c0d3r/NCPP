#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

		containers::static_bqueue_t<1024> bqueue;

		bqueue.push_t<i32>(5);
		bqueue.push_t<f64>(7.2);
		bqueue.push_t<std::string>("Hello World");

		i32 a1 = 0;
		bqueue.try_pop(a1);

		f64 a2 = 0;
		bqueue.try_pop(a2);

		std::string a3;
		bqueue.try_pop(a3);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}