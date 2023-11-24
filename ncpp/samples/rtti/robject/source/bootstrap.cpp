
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
		PUBLIC_CONST(void(), foo),
                      
        STATIC_PUBLIC(i32, si),
        STATIC_PUBLIC(void(), foo2)
	);

};

void A::foo() {

    std::cout << "A::foo" << std::endl;

}

i32 A::si = 4;
void A::foo2() {

    

}



struct F_demo_compiletime_rflag {
    
public:
    NCPP_ROBJECT_USER_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<!F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user reflect non-static member: " << F_member_static_info__::name() << std::endl;
        
        if (robject_member_info_p->template T_is<void()>()) {
            
            robject_member_info_p->template T_invoke<void()>();

        }
        
    }
    NCPP_ROBJECT_USER_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user reflect static member: " << F_member_static_info__::name() << std::endl;
        
    }
    NCPP_ROBJECT_USER_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, B>, i32> = 0
    ) {
        
        std::cout << "user reflect base B: " << F_base__::static_type_name() << std::endl;
        
    }
    NCPP_ROBJECT_USER_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, C>, i32> = 0
    ) {
        
        std::cout << "user reflect base C: " << F_base__::static_type_name() << std::endl;
        
    }
    NCPP_ROBJECT_USER_REFLECT_OBJECT(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_robject__, C> || std::is_same_v<F_robject__, B>, i32> = 0
    ) {
        
        std::cout << "user reflect object C or B: " << F_robject__::static_type_name() << std::endl;
        
    }
    
// public:
    // NCPP_ROBJECT_DISABLE_DEFAULT_REFLECT(F_demo_compiletime_rflag);
    
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
