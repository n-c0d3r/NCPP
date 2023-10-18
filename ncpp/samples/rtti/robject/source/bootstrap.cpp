
#include <ncpp/rtti/.hpp>
#include <ncpp/log.hpp>

using namespace ncpp;



class A {

	NCPP_BASIC_RCLASS(
		A,

		PUBLIC(i32, i),
		PUBLIC_CONST(void(), foo)
	);

};

void A::foo() {

    

}



int main() {

	A a;

	A::F_rcontainer rcontainer;

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer);
    
    for(const auto& it : type_info_p->name_to_member_info_p_map()){
        
        std::cout << it.first << std::endl;
        
    }

	pause_console();

	return 0;
}
