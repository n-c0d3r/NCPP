#include <ncpp/.hpp>



namespace ncpp {



}



#pragma region new and delete operators
void* operator new(ncpp::sz size) {

	return ncpp::aligned_alloc(size, NCPP_DEFAULT_ALIGN);
}
void* operator new(ncpp::sz size, ncpp::new_mode::align, ncpp::sz align) {

	return ncpp::aligned_alloc(size, align);
}
void operator delete(void* ptr) {

	if (ncpp::is_allocated_by_ncpp(ptr)) {

		ncpp::aligned_free(ptr);

	}
	else {

		free(ptr);

	}
}
#pragma endregion