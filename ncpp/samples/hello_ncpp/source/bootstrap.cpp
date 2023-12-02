
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
	
    cout << F_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;

    TF_vector<TF_vector<i32>> v = {{1,2,3}};
    cout << v << std::endl;

    ncpp::pause_console();

	return 0;
}
