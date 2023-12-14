
#include <ncpp/.hpp>

using namespace ncpp;



int main() {

	{

        G_hash_table ht;

        ht.add(1, 1);
        ht.add(1, 2);
        ht.add(1, 3);
        ht.add(1, 4);

        ht.add(2, 5);
        ht.add(2, 6);

        cout << ht << std::endl;
        
        for(u32 index = ht.first(1); ht.is_valid(index); index = ht.next(index)){
            
            std::cout << index << std::endl;
            
        }
        
        for(u32 index = ht.first(2); ht.is_valid(index); index = ht.next(index)){
            
            std::cout << index << std::endl;
            
        }

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
