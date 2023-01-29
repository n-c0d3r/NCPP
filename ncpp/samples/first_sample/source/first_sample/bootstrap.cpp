#include <ncpp/ncpp.hpp>



int main() {

	ncpp::containers::handle_map_t<int> int_map(0, 1555);

	int_map.insert(0);
	int_map.insert(1);
	int_map.insert(2);
	int_map.insert(3);
	int_map.insert(4);

	for (auto meta : int_map.meta_set()) {

		int a = int_map[meta];

		std::cout << a << std::endl;

	}

	return 0;
}