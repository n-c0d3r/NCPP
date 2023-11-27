#include <ncpp/mem/memory_helper.hpp>
#include <ncpp/mem/default_allocator.hpp>

using namespace ncpp;



namespace ncpp {

}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region New, Delete Operators

namespace {

	ncpp::mem::F_default_allocator default_allocator;

}

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{

	return default_allocator.allocate(size, flags);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{

	return default_allocator.allocate(size, alignment, alignmentOffset, flags);
}



void operator delete[](void* ptr)
{

	default_allocator.deallocate(ptr);
}

#pragma endregion
