#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	//white(1)
	{

		containers::cfv_queue_t<i32> queue;

		queue.push(1);

		i32 a;

		utilities::lref_t<i32> ar = a;

		queue.try_pop(*ar);

		log_memory_stats();

	}

	log_memory_stats();

	system("pause");

	return 0;
}