
#include <ncpp/.hpp>
#include <ncpp/rtti/rtype_info.hpp>

using namespace ncpp;



int main() {

	rtti::rtype_info_t<>* type_info = rtti::rtype_info_t<>::create_t<i32*&&>();

	system("pause");

	return 0;
}