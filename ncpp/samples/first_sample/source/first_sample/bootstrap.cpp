#include <ncpp/ncpp.hpp>

#include <ctime>







int main() {

	size_t loop_count = 500000;



	{

		using map_type = ncpp::containers::handle_map_t<int>;

		map_type map(loop_count * sizeof(int) * 2);

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			map.insert(5);

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using map_type = std::unordered_map<int, bool>;

		map_type map;

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			map.insert({ i, 5 });

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using map_type = ncpp::containers::handle_map_t<int>;

		map_type map(loop_count * sizeof(int) * 2);

		for (int i = 0; i < loop_count; ++i) {

			map.insert(i);

		}

		clock_t start = clock();
		size_t sum = 0;
		for (auto& meta : map) {

			sum += meta.item;

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using map_type = std::unordered_map<int, bool>;

		map_type map;

		for (int i = 0; i < loop_count; ++i) {

			map.insert({ i, i });

		}

		clock_t start = clock();
		size_t sum = 0;
		for (auto& it : map) {

			sum += it.second;

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}

	return 0;
}