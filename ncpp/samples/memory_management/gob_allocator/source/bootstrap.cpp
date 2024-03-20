
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

    mem::F_gob_storage gob_storage;
    mem::F_gob_deallocation_list gob_deallocation_list(128);
    mem::F_gob_allocator gob_allocator(&gob_storage, &gob_deallocation_list);

//	mem::F_dummy_allocator dummy_allocator;
	mem::F_default_allocator default_allocator;

	eastl::allocator eastl_allocator;

	const u32 allocation_count = 5000;
	const u32 allocation_size = 1024;

	{

//		NCPP_SCOPED_PROFILER_SAMPLE("Dummy allocator");
//
//		for (u32 i = 0; i < allocation_count; ++i) {
//
//			dummy_allocator.allocate(allocation_size, 0);
//
//		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Default allocator");

		for (u32 i = 0; i < allocation_count; ++i) {

			default_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("EASTL allocator");

		for (u32 i = 0; i < allocation_count; ++i) {

			eastl_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Malloc");

		for (u32 i = 0; i < allocation_count; ++i) {

			malloc(allocation_size);

		}

	}

	pause_console();

	return 0;
}