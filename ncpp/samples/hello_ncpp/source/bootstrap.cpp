
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
    cout << F_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    TF_vector<i32> v = {1,2,3};
    cout << v << std::endl;

    constexpr b8 isv = utilities::T_is_ostreamable_v<F_ostream, TF_cout_value<i32>>;
    cout << isv << std::endl;

    ncpp::pause_console();

	return 0;
}
