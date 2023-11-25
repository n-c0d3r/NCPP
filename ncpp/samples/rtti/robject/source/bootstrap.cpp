
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
    struct F_user_reflect_custom_params {
        
        eastl::string message;
        
    };
    NCPP_ROBJECT_USER_REFLECT_CUSTOM_DATA(F_demo_compiletime_rflag, F_user_reflect_custom_params);
    
public:
    NCPP_ROBJECT_USER_PRE_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<!F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user pre reflect non-static member: " << F_member_static_info__::name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<!F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user post reflect non-static member: " << F_member_static_info__::name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user pre reflect static member: " << F_member_static_info__::name() << " (" << F_member_static_info__::static_get() << ")" << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(
        F_demo_compiletime_rflag,
        std::enable_if_t<F_member_static_info__::is_static(), i32> = 0
    ) {
        
        std::cout << "user post reflect static member: " << F_member_static_info__::name() << " (" << F_member_static_info__::static_get() << ")" << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, B>, i32> = 0
    ) {
        
        std::cout << "user pre reflect base B: " << F_base__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, B>, i32> = 0
    ) {
        
        std::cout << "user post reflect base B: " << F_base__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, C>, i32> = 0
    ) {
        
        std::cout << "user pre reflect base C: " << F_base__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_BASE(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_base__, C>, i32> = 0
    ) {
        
        std::cout << "user post reflect base C: " << F_base__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_OBJECT(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_robject__, C> || std::is_same_v<F_robject__, B>, i32> = 0
    ) {
        
        std::cout << "user pre reflect object C or B: " << F_robject__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_OBJECT(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_robject__, C> || std::is_same_v<F_robject__, B>, i32> = 0
    ) {
        
        std::cout << "user post reflect object C or B: " << F_robject__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_OBJECT(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_robject__, A>, i32> = 0
    ) {
        
        std::cout << "user pre reflect object A: " << F_robject__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_OBJECT(
        F_demo_compiletime_rflag,
        std::enable_if_t<std::is_same_v<F_robject__, A>, i32> = 0
    ) {
        
        std::cout << "user post reflect object A: " << F_robject__::static_type_name() << " " << custom_params_p->message << std::endl;
        
    }
    
public:
    NCPP_ROBJECT_DISABLE_DEFAULT_REFLECT(F_demo_compiletime_rflag);
    
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
    
    F_demo_compiletime_rflag::F_user_reflect_custom_params user_reflect_custom_params = {
        
        "(user reflect custom params)"
        
    };
    A::T_static_reflect<F_demo_compiletime_rflag>(&rcontainer, &user_reflect_custom_params);

	pause_console();

	return 0;
}
