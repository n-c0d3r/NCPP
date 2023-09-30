
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	F_chunk_allocator chunk_allocator;
	TF_link_allocator<F_chunk_allocator> link_allocator(chunk_allocator);
	F_default_allocator default_allocator;

	eastl::allocator eastl_allocator;

	const u32 allocation_count = 5000;
	const u32 allocation_size = 1024;

	{

		NCPP_SCOPED_PROFILE(chunk_allocator, "Chunk allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			chunk_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE(link_allocator, "Link allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			link_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE(default_allocator, "Default allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			default_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE(eastl_allocator, "EASTL allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			eastl_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE(malloc, "Malloc: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			malloc(allocation_size);

		}

	}

	system("pause");

	return 0;
}