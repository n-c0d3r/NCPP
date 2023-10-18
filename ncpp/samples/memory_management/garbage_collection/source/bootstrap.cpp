
#include <ncpp/.hpp>

using namespace ncpp;



class B : public mem::TF_garbage_collectable<B> {
    
    NCPP_BASIC_RCLASS(
        B
    );
    
};



class A : public mem::TF_garbage_collectable<A> {
    
    NCPP_BASIC_RCLASS(
        A
    );
    
};



int main() {

	{

        
        
	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
