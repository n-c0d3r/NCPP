#include <ncpp/ncpp.hpp>

#include <ctime>







int main() {

	// size_t loop_count = 500000;



	// {

	// 	using map_type = ncpp::containers::handle_map_t<int>;

	// 	map_type map(0, loop_count * sizeof(int));

	// 	clock_t start = clock();
	// 	for (int i = 0; i < loop_count; ++i) {

	// 		map.insert(5);

	// 	}
	// 	clock_t end = clock();
	// 	std::cout << end - start << std::endl;

	// }



	// {

	// 	using map_type = std::unordered_map<int, bool>;

	// 	map_type map;

	// 	clock_t start = clock();
	// 	for (int i = 0; i < loop_count; ++i) {

	// 		map.insert({ i, 5 });

	// 	}
	// 	clock_t end = clock();
	// 	std::cout << end - start << std::endl;

	// }



	// {

	// 	using map_type = ncpp::containers::handle_map_t<int>;

	// 	map_type map(0, loop_count * sizeof(int));

	// 	for (int i = 0; i < loop_count; ++i) {

	// 		map.insert(5);

	// 	}

	// 	clock_t start = clock();

	// 	clock_t end = clock();
	// 	std::cout << end - start << std::endl;

	// }



	// {

	// 	using map_type = std::unordered_map<int, bool>;

	// 	map_type map;

	// 	for (int i = 0; i < loop_count; ++i) {

	// 		map.insert({ i, 5 });

	// 	}

	// 	clock_t start = clock();
	// 	for (auto& it : map) {

	// 		it.second = it.second * 2;
	// 		it.second = it.second * 2;
	// 		it.second = it.second * 2;
	// 		it.second = it.second * 2;
	// 		it.second = it.second * 2;
	// 		it.second = it.second * 2;

	// 	}
	// 	clock_t end = clock();
	// 	std::cout << end - start << std::endl;

	// }


	using map_type = ncpp::containers::handle_map_t<int>;

	map_type map;

	map.insert(5);

	return 0;
}