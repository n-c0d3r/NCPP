
#include <ncpp/.hpp>

using namespace ncpp;



int main() {
    
    TF_vector<i32> v = {1,2,3};
	
    cout << F_string("Hello NCPP ") + NCPP_VERSION_STR << std::endl;
	wcout << v << std::endl;    

    pause_console();

	return 0;
}
