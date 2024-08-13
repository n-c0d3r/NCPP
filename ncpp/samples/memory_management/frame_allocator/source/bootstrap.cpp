
#include <ncpp/.hpp>

using namespace ncpp;



enum class E_frame_param
{
	MAIN,

	GRAPHICS,
	PHYSICS,
	ANIMATION,

	COUNT
};



class F_demo_frame_heap : public TA_frame_heap<F_demo_frame_heap>
{
public:
	F_demo_frame_heap() :
		TA_frame_heap<F_demo_frame_heap>(
			(u32)E_frame_param::COUNT,
			1
		)
	{
	}
};
using F_demo_frame_memory_adapter = F_demo_frame_heap::F_adapter;
using F_demo_frame_allocator = F_demo_frame_heap::F_allocator;



int main()
{
	{
		F_demo_frame_heap heap;
		F_demo_frame_memory_adapter* adapter_p = heap.adapter_p_vector()[0];
		F_demo_frame_allocator allocator(adapter_p, (u32)E_frame_param::GRAPHICS);

		{
			NCPP_SCOPED_PROFILER_SAMPLE("TF_frame_allocator::allocate");

			for(u32 i = 0; i < 100000; ++i)
				allocator.allocate(128);
		}

		log_memory_stats();

		heap.reset_param((u32)E_frame_param::GRAPHICS);

		log_memory_stats();
	}

	log_memory_stats();

	pause_console();

	return 0;
}