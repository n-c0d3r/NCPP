#include <ncpp/ncpp.hpp>



int main() {

	ncpp::containers::handle_map_array_t<int, 5> map_array;

	map_array[0].insert(1);
	auto handle = map_array[0].insert(2);
	map_array[0].insert(3);

	map_array[1].insert(4);
	map_array[1].insert(5);

	map_array[2].insert(6);

	map_array.transfer(2, 0, handle);

	return 0;
}