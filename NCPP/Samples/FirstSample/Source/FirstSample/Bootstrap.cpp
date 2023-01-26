#include <NCPP/NCPP.hpp>



NCPP_STRUCT S_Transform {

	DirectX::XMFLOAT3 position;

};

NCPP_STRUCT S_Cube{

	DirectX::XMFLOAT3 size;

};



NCPP_CLASS C_TransformSystem final :
	public NCPP::ECS::T_IC_BasicComponentSystem<C_TransformSystem, S_Transform>
{

public:
	C_TransformSystem(NCPP::ECS::C_BasicEntitySystem* p_EntitySystem) :
		T_IC_ComponentSystem(p_EntitySystem)
	{



	}
	~C_TransformSystem() {



	}

};



int main() {

	NCPP::ECS::C_BasicEntitySystem entitySystem;
	C_TransformSystem transformSystem(&entitySystem);



	NCPP::ECS::EntityId entityId = entitySystem.CreateEntity();
	entitySystem.DestroyEntity(entityId);
	transformSystem.AddComponent(entityId, 
		{

			{1.0f, 2.0f, 3.0f}

		}
	);

	return 0;
}