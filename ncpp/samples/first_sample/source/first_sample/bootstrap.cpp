#include <ncpp/ncpp.hpp>



int main() {

	ncpp::containers::handle_map_t<int> int_map(0, 1555);

	int_map.insert(5);
	
	int a = 4;
	auto handle = int_map.insert(a);

	int_map.erase(handle);

	std::cout << int_map.at(handle) << std::endl;

	return 0;
}