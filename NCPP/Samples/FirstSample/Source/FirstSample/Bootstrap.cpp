#include <NCPP/NCPP.hpp>



NCPP_STRUCT S_Transform {

	DirectX::XMFLOAT3 position;

};

NCPP_STRUCT S_Cube{

	DirectX::XMFLOAT3 size;

};



NCPP_CLASS C_TransformSystem final :
	public NCPP::ECS::T_IC_StandardComponentSystem<C_TransformSystem, S_Transform>
{

public:
	C_TransformSystem() :
		T_IC_ComponentSystem()
	{



	}
	~C_TransformSystem() {



	}

};



int main() {

	NCPP::ECS::C_StandardEntitySystem::CreateInstance();

	C_TransformSystem::CreateInstance();



	NCPP::ECS::EntityId entityId1 = NCPP::ECS::C_StandardEntitySystem::Instance().CreateEntity();
	NCPP::ECS::ComponentId transformId1 = C_TransformSystem::Instance().AddComponent(
		entityId1,
		{

			{1.0f, 2.0f, 3.0f}

		}
	);
	C_TransformSystem::Instance().Disable(transformId1);

	NCPP::ECS::EntityId entityId2 = NCPP::ECS::C_StandardEntitySystem::Instance().CreateEntity();
	NCPP::ECS::ComponentId transformId2 = C_TransformSystem::Instance().AddComponent(
		entityId2,
		{

			{3.0f, 2.0f, 1.0f}

		}
	);

	std::cout << "Enabled Transforms: " << std::endl;
	for (auto& transform : C_TransformSystem::Instance())
		std::cout << transform.position.x << " " << transform.position.y << " " << transform.position.z << " " << std::endl;

	std::cout << "Disabled Transforms: " << std::endl;
	for (auto& transform : C_TransformSystem::Instance().DisabledData())
		std::cout << transform.position.x << " " << transform.position.y << " " << transform.position.z << " " << std::endl;


	return 0;
}