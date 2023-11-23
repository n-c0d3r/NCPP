
#include <ncpp/rtti/.hpp>
#include <ncpp/log.hpp>

using namespace ncpp;



class B {

    NCPP_BASIC_RCLASS(
        B,

        PUBLIC(i32, i)
    );

};

class C {

    NCPP_BASIC_RCLASS(
        C,

        PUBLIC(i32, cc)
    );

};

class A : public B, public C {

	NCPP_BASIC_RCLASS(
		A,
                      
        EXTENDS(B),
        EXTENDS(C),

		PUBLIC(i32, i),
		PUBLIC_CONST(void(), foo)
	);

};

void A::foo() {

    

}



void log_type_info(A::F_robject_type_info* type_info_p){
    
    for(const auto& it : type_info_p->name_to_member_info_p_map()){
        
        std::cout << it.first << std::endl;
        
    }
    
    for(const auto& it : type_info_p->base_type_info_p_set()){
        
        log_type_info((A::F_robject_type_info*)it);
        
    }
    
}



int main() {

	A a;

	A::F_rcontainer rcontainer;

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer);
    
    log_type_info(type_info_p);

	pause_console();

	return 0;
}
