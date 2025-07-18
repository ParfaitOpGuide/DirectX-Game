#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>
#include "BaseComponentSystem.h"

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner);
	~PhysicsComponent();
	void perform(float deltaTime) override;
	RigidBody* getRigidBody();

private:
	float mass = 1000.00f; //kg
	RigidBody* rigidBody;
};

