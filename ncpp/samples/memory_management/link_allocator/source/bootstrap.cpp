
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	mem::F_chunk_allocator chunk_allocator;
	mem::TF_link_allocator<mem::F_chunk_allocator> link_allocator(chunk_allocator);
	mem::F_default_allocator default_allocator;

	eastl::allocator eastl_allocator;

	const u32 allocation_count = 5000;
	const u32 allocation_size = 1024;

	{

		NCPP_SCOPED_PROFILE("Chunk allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			chunk_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE("Link allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			link_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE("Default allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			default_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE("EASTL allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			eastl_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE("Malloc: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			malloc(allocation_size);

		}

	}

	system("pause");

	return 0;
}