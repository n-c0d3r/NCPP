
#include <ncpp/.hpp>

using namespace ncpp;



class B {

    NCPP_BASIC_ROBJECT(
        B,

        PUBLIC(
            (i32) = 4,
            i
        ),

        PUBLIC_ABSTRACT(
            ()(),
            abstract_func
        )
    );

};

class C {

    NCPP_BASIC_ROBJECT(
        C,

        PUBLIC(
            (i32),
            cc
        )
    );

};

template<typename F__>
class TD {

    NCPP_BASIC_ROBJECT(
        TD<F__>,

        PUBLIC(
            (i32),
            dd
        ),
        PUBLIC(
            (F__)(F__),
            dd2
        ),
        PUBLIC_STATIC(
            (F__),
            dd3
        ),
        PUBLIC_STATIC(
            (F__)[4],
            dd4
        )
    );

};

template<typename F__>
NCPP_MAGIC((F__)(F__), TD<F__>::dd2) {

    return {};
}

template<typename F__>
NCPP_MAGIC((F__), TD<F__>::dd3) = 12;
template<typename F__>
NCPP_MAGIC((F__)[4], TD<F__>::dd4);



#define BLOG_THIS void log_this() { NCPP_INFO() << T_type_fullname<F_this>(); }
#define RLOG_THIS NCPP_INFO() << "Reflecting";



class A : public B, public C, public TD<i32> {

	NCPP_BASIC_ROBJECT(
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
            (i32),
            (*)i_p
        ),
		PUBLIC(
            ()(),
            foo
        ),

        PUBLIC_STATIC(
            (i32),
            si
        ),
        PUBLIC_STATIC(
            ()(int, int, TF_vector<int, F_default_allocator>),
            foo2
        ),

        PUBLIC_CONSTEXPR(
            (i32)(),
            i32_constexpr
        ),

        PUBLIC(
            (i32, b8, F_string),
            i32_b8_string_tuple
        ),
        PUBLIC(
            (i32, b8)(f32, f64),
            i32_b8_tuple_foo
        ),

        PUBLIC(
            ()(),
            abstract_func
        )
	);

};



NCPP_MAGIC(()(), A::foo) {

}

NCPP_MAGIC((i32), A::si) = 4;
NCPP_MAGIC((i32), A::private_static_i_) = 6;
NCPP_MAGIC(()(int, int, TF_vector<int, F_default_allocator>), A::foo2) {

}

constexpr NCPP_MAGIC((i32)(), A::i32_constexpr) {

    return 3;
}

NCPP_MAGIC((i32, b8)(f32, f64), A::i32_b8_tuple_foo) {

    return {};
}

NCPP_MAGIC(()(), A::abstract_func) {

}



struct F_customm_reflector {

    struct F_params {

        G_string message;

    };
    NCPP_ROBJECT_USER_REFLECT_CUSTOM_PARAMS(F_params);



    NCPP_ROBJECT_USER_PRE_REFLECT_MEMBER(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user pre reflect member: "
            << T_cout_value(F_member_sinfo__::name())
            << " (static value: "
            << T_cout_value(F_member_sinfo__::static_get())
            << ")"
            << " (accessibility: "
            << T_cout_value((u32)F_member_sinfo__::accessibility())
            << ")"
            << " "
            << custom_params_p->message;

    }
    NCPP_ROBJECT_USER_POST_REFLECT_MEMBER(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user post reflect member: "
            << T_cout_value(F_member_sinfo__::name())
            << " (static value: "
            << T_cout_value(F_member_sinfo__::static_get())
            << ")"
            << " (accessibility: "
            << T_cout_value((u32)F_member_sinfo__::accessibility())
            << ")"
            << " "
            << custom_params_p->message;

    }
    NCPP_ROBJECT_USER_PRE_REFLECT_BASE(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user pre reflect base: "
            << T_cout_value(F_base__::static_type_name())
            << " "
            << custom_params_p->message;

    }
    NCPP_ROBJECT_USER_POST_REFLECT_BASE(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user post reflect base: "
            << T_cout_value(F_base__::static_type_name())
            << " "
            << custom_params_p->message;

    }
    NCPP_ROBJECT_USER_PRE_REFLECT_OBJECT(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user pre reflect object: "
            << T_cout_value(F_robject__::static_type_name())
            << " "
            << custom_params_p->message;

    }
    NCPP_ROBJECT_USER_POST_REFLECT_OBJECT(
        F_customm_reflector
    ) {

        NCPP_INFO() << "user post reflect object: "
            << T_cout_value(F_robject__::static_type_name())
            << " "
            << custom_params_p->message;

    }

public:
    NCPP_ROBJECT_DISABLE_DEFAULT_REFLECT();

};



void log_type_info(A::F_robject_type_info* type_info_p){

    for(const auto& it : type_info_p->base_type_info_p_set()){

        log_type_info((A::F_robject_type_info*)it);

    }

    for(const auto& it : type_info_p->name_to_member_info_p_map()){

        NCPP_INFO() << T_cout_value(it.first);

    }

}



int main() {

    NCPP_INFO() << "A's sinfos: " << T_type_fullname<typename A::F_sinfos>();
    NCPP_INFO() << "A's base sinfos: " << T_type_fullname<typename A::F_base_sinfos>();
    NCPP_INFO() << "A's member sinfos: " << T_type_fullname<typename A::F_member_sinfos>();

    

	A a;

	A::F_rcontainer rcontainer;

	A::F_robject_type_info* type_info_p = A::F_rtti_traits::template T_safe_reflect<A>(&rcontainer, &a);
    log_type_info(type_info_p);

    F_customm_reflector::F_params user_reflect_custom_params = {

        "(user reflect custom params)"

    };
    A::T_static_reflect<F_customm_reflector>(&rcontainer, &user_reflect_custom_params);

	pause_console();

	return 0;
}
