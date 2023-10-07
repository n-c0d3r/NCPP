
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	mem::F_incremental_chunk_allocator incremental_chunk_allocator;
	mem::TF_link_allocator<mem::F_incremental_chunk_allocator> link_allocator(incremental_chunk_allocator);
	mem::F_default_allocator default_allocator;

	eastl::allocator eastl_allocator;

	const u32 allocation_count = 5000;
	const u32 allocation_size = 1024;

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Incremental chunk allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			incremental_chunk_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Link allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			link_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Default allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			default_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("EASTL allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			eastl_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILER_SAMPLE("Malloc: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			malloc(allocation_size);

		}

	}

	pause_console();

	return 0;
}