#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localRotation = Vector3D(0, 0, 0);
	this->localPosition = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

void AGameObject::attachComponent(AComponent* component, PhysicsSystem* phys)
{
}

void AGameObject::detachComponent(AComponent* component, PhysicsSystem* phys)
{
}

bool AGameObject::getComponentsOfTypeExists(AComponent::ComponentType type)
{
	bool b = false;
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (componentList[i]->getType() == (AComponent::ComponentType)3)
		{
			b = true;
			index = i;

			break;
		}
	}

	if (index != -1)
		return true;
	else
		return false;
}

void AGameObject::setLocalMatrix(float mat[16])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			currMat.m_mat[i][j] = mat[i];
		}
	}
}
