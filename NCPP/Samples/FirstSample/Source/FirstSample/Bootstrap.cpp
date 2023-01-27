#include <NCPP/NCPP.hpp>



class A : public NCPP::RTTR::IC_Object {

private:
	int i[32];

	

public:
	A() :
		i{1,2,3,4,5,6,7}
	{



	}
	~A() {

		std::cout << "Destruct A" << std::endl;

	}

};



int main() {

	NCPP::RTTR::T_C_StandardClass<A> aClass;

	{

		NCPP::RTTR::T_C_UniqueObjectPtr<A> p_Object1 = NCPP::RTTR::T_MakeUnique<A>((A*)aClass.CreateInstance());
		NCPP::RTTR::T_C_UniqueObjectPtr<A> p_Object2 = std::move(p_Object1);

	}

	return 0;
}