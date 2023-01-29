#include <ncpp/ncpp.hpp>int_map1



int main() {

	ncpp::containers::handle_map_t<int> map1(0, 1024);
	ncpp::containers::handle_map_t<int> map2(0, 1024);

	auto handle0_1 = map1.insert(0);
	auto handle1_1 = map1.insert(1);
	auto handle2_1 = map1.insert(2);
	auto handle3_1 = map1.insert(3);
	auto handle4_1 = map1.insert(4);

	auto handle0_2 = map2.insert(0);
	auto handle1_2 = map2.insert(1);
	auto handle2_2 = map2.insert(2);
	auto handle3_2 = map2.insert(3);
	auto handle4_2 = map2.insert(4);

	ncpp::containers::bridge_map_t<int, int> bridge(map1, map2);

	bridge.connect(handle1_1, handle3_2);

	std::cout << bridge.right(handle1_1).index << std::endl;
	std::cout << bridge.left(handle3_2).index << std::endl;

	return 0;
}