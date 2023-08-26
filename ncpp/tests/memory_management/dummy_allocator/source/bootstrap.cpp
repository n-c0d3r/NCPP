
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
	dummy_allocator dummy_allocator;
	eastl::allocator default_eastl_allocator;

	const u32 allocation_count = 5000;
	const u32 allocation_size = 1024;

	{

		NCPP_SCOPED_PROFILE(dummy_allocator, "Dummy allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			dummy_allocator.allocate(allocation_size, 0);

		}

	}

	{

		NCPP_SCOPED_PROFILE(default_eastl_allocator, "Default eastl allocator: ");

		for (u32 i = 0; i < allocation_count; ++i) {

			default_eastl_allocator.allocate(allocation_size, 0);

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