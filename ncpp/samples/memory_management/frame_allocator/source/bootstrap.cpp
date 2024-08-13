
#include <ncpp/.hpp>

using namespace ncpp;



class F_demo_frame_heap : public TA_frame_heap<F_demo_frame_heap>
{
public:
	F_demo_frame_heap()
	{
		create_adapter();
		set_uniform_param_count(1);
	}
};
using F_demo_frame_memory_adapter = F_demo_frame_heap::F_adapter;
using F_demo_frame_allocator = F_demo_frame_heap::TF_allocator<>;



int main()
{
	{
		F_demo_frame_heap heap;
		F_demo_frame_memory_adapter* adapter_p = heap.adapter_p_vector()[0];
		F_demo_frame_allocator allocator(adapter_p);

		void* ptr1 = allocator.allocate(128);
		void* ptr2 = allocator.allocate(128);

		log_memory_stats();

		heap.reset_uniform_param(0);

		log_memory_stats();
	}

	log_memory_stats();

	pause_console();

	return 0;
}