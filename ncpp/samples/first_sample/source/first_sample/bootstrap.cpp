#include <ncpp/ncpp.hpp>

#include <ctime>







int main() {

	size_t loop_count = 500000;



	{

		using data_type = ncpp::dod::standard_data_t<int>;

		data_type data(loop_count * sizeof(int));

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			data.emplace(5);

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using map_type = ncpp::containers::handle_map_t<int>;

		map_type map(0, loop_count * sizeof(int));

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			map.insert(5);

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using set_type = std::unordered_set<int>;

		set_type set;

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			set.insert(5);

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	{

		using map_type = std::unordered_map<int, bool>;

		map_type map;

		clock_t start = clock();
		for (int i = 0; i < loop_count; ++i) {

			map.insert({ 5, true });

		}
		clock_t end = clock();
		std::cout << end - start << std::endl;

	}



	return 0;
}