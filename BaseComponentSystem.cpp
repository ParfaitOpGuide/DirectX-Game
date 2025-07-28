#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	if (!sharedInstance)
	{
		sharedInstance = new BaseComponentSystem();
	}
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	if (!sharedInstance)
	{
		sharedInstance = new BaseComponentSystem();
	}
}

void BaseComponentSystem::destroy()
{
	if (sharedInstance)
	{
		delete sharedInstance;
		sharedInstance = nullptr;
	}
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	if (!physicsSystem)
	{
		physicsSystem = new PhysicsSystem();
	}
	return physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
}

BaseComponentSystem::~BaseComponentSystem()
{
}
