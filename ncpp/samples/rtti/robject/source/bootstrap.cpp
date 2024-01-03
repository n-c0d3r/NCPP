
#include <ncpp/.hpp>

using namespace ncpp;



class B {

    NCPP_BASIC_RCLASS(
        B,

        PUBLIC(
            (i32),
            i
        )
    );

};

class C {

    NCPP_BASIC_RCLASS(
        C,

        PUBLIC(
            (i32),
            cc
        )
    );

};

template<typename F__>
class TD {

    NCPP_BASIC_RCLASS(
        TD<F__>,

        PUBLIC(
            (i32),
            dd
        )
    );

};

#define BLOG_THIS void log_this() { std::cout << T_type_fullname<F_this>() << std::endl; }
#define RLOG_THIS std::cout << "Reflecting" << std::endl;
 
class A : public B, public C, public TD<i32> {

	NCPP_BASIC_RCLASS(
		A,

        EXTENDS(B),
        EXTENDS(C),
        EXTENDS(TD<i32>),

        BONLY(BLOG_THIS),
        RONLY(RLOG_THIS),

        SAMPLE_NESTED_MACRO_A(abc),

        PRIVATE(
            (i32),
            private_i_ 
        ),
        PUBLIC_SETTER_NOEXCEPT(set_private_i, private_i_),
        PUBLIC_GETTER_NOEXCEPT(private_i, private_i_),
        PUBLIC_CONST_GETTER(private_i, private_i_),

        PRIVATE_STATIC(
            (i32),
            private_static_i_
        ),
        PUBLIC_STATIC_SETTER(set_private_static_i, private_static_i_),
        PUBLIC_STATIC_GETTER(private_static_i, private_static_i_),

		PUBLIC(
            (i32),
            i
        ),
		PUBLIC(
            (void)(),
            foo
        ),
                      
        PUBLIC_STATIC(
            (i32),
            si
        ),
        PUBLIC_STATIC(
            (void)(int, int, TF_vector<int, F_default_allocator>),
            foo2
        ),

        PUBLIC_CONSTEXPR(
            (i32)(),
            i32_constexpr
        ),

        PUBLIC(
            (i32, b8),
            i32_b8_tuple
        ),
        PUBLIC(
            (i32, b8)(f32),
            i32_b8_tuple_foo
        )
	);

};

void A::foo() {


    
}

i32 A::si = 4;
i32 A::private_static_i_ = 6;
void A::foo2(int, int, TF_vector<int, F_default_allocator>) {



}
constexpr i32 A::i32_constexpr(){

    return 3;
}



struct F_customm_reflector {
    
public:
    struct F_user_reflect_custom_params {
        
        G_string message;
        
    };
    NCPP_ROBJECT_USER_REFLECT_CUSTOM_PARAMS(F_customm_reflector, F_user_reflect_custom_params);
    
public:
    NCPP_ROBJECT_USER_PRE_REFLECT_MEMBER(
        F_customm_reflector
    ) {
        
        cout << "user pre reflect member: "
            << T_cout_value(F_member_static_info__::name())
            << " ("
            << T_cout_value(F_member_static_info__::static_get())
            << ")"
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(
        F_customm_reflector
    ) {
        
        cout << "user post reflect member: "
            << T_cout_value(F_member_static_info__::name())
            << " ("
            << T_cout_value(F_member_static_info__::static_get())
            << ")"
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_BASE(
        F_customm_reflector
    ) {
        
        cout << "user pre reflect base: "
            << T_cout_value(F_base__::static_type_name())
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_BASE(
        F_customm_reflector
    ) {
        
        cout << "user post reflect base: "
            << T_cout_value(F_base__::static_type_name())
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    NCPP_ROBJECT_USER_PRE_REFLECT_OBJECT(
        F_customm_reflector
    ) {
        
        cout << "user pre reflect object: "
            << T_cout_value(F_robject__::static_type_name())
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    NCPP_ROBJECT_USER_POST_REFLECT_OBJECT(
        F_customm_reflector
    ) {
        
        cout << "user post reflect object: "
            << T_cout_value(F_robject__::static_type_name())
            << " "
            << custom_params_p->message
            << std::endl;
        
    }
    
public:
    NCPP_ROBJECT_DISABLE_DEFAULT_REFLECT(F_customm_reflector);
    
};



void log_type_info(A::F_robject_type_info* type_info_p){
    
    for(const auto& it : type_info_p->base_type_info_p_set()){
        
        log_type_info((A::F_robject_type_info*)it);
        
    }
    
    for(const auto& it : type_info_p->name_to_member_info_p_map()){
        
        cout << T_cout_value(it.first) << std::endl;
        
    }
    
}



int main() {

	A a;

	A::F_rcontainer rcontainer;

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer, &a);
    log_type_info(type_info_p);
    
    F_customm_reflector::F_user_reflect_custom_params user_reflect_custom_params = {

        "(user reflect custom params)"

    };
    A::T_static_reflect<F_customm_reflector>(&rcontainer, &user_reflect_custom_params);

	pause_console();

	return 0;
}
