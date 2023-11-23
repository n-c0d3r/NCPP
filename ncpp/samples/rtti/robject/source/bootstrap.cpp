
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



struct F_demo_compiletime_rflag {
    
public:
    NCPP_ROBJECT_USER_REFLECT_MEMBER(F_demo_compiletime_rflag, void){
        
        std::cout << "user reflect member: " << robject_member_info_p->name() << std::endl;
        
    }
    NCPP_ROBJECT_USER_REFLECT_BASE(F_demo_compiletime_rflag, void){
        
        std::cout << "user reflect base: " << base_info_p->name() << std::endl;
        
    }
    
};



void log_type_info(A::F_robject_type_info* type_info_p){
    
    for(const auto& it : type_info_p->base_type_info_p_set()){
        
        log_type_info((A::F_robject_type_info*)it);
        
    }
    
    for(const auto& it : type_info_p->name_to_member_info_p_map()){
        
        std::cout << it.first << std::endl;
        
    }
    
}



int main() {

	A a;

	A::F_rcontainer rcontainer;

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer);
    log_type_info(type_info_p);
    
    A::T_static_reflect<F_demo_compiletime_rflag>(&rcontainer);

	pause_console();

	return 0;
}
