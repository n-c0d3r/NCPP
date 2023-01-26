#include <NCPP/NCPP.hpp>



NCPP_STRUCT S_Transform {

	DirectX::XMFLOAT3 position;

};



int main() {

	NCPP::DOD::T_C_DefaultData<S_Transform> transformData;

	transformData.EmplaceBack({

		{1.0f, 2.0f, 3.0f}

	});
	transformData.EmplaceBack({

		{2.0f, 3.0f, 4.0f}

	});
	transformData.EmplaceBack({

		{3.0f, 4.0f, 5.0f}

	});

	for (auto& a : transformData.T_Column<S_Transform>()) {

		std::cout << a.position.x << " " << a.position.y << " " << a.position.z << std::endl;

	}

	return 0;
}