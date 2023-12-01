
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
    cout << F_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    TF_vector<i32> v = {1,2,3};
    cout << v << std::endl;

    constexpr b8 isv = utilities::TF_is_ostreamable<F_ostream, TF_cout_value<i32>>::value;
    cout << isv << std::endl;
    cout << TF_cout_value<i32>{32} << std::endl;

    ncpp::pause_console();

	return 0;
}
