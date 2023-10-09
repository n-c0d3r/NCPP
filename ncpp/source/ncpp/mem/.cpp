#include <ncpp/mem/memory_helper.hpp>

using namespace ncpp;



namespace ncpp {

}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#pragma region New, Delete Operators

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{

	return mem::F_default_memory_helper::allocate(size, pName, flags);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{

	return mem::F_default_memory_helper::allocate(size, alignment, alignmentOffset, pName, flags);
}



void operator delete[](void* ptr) noexcept
{

	mem::F_default_memory_helper::deallocate(ptr);
}

#pragma endregion
