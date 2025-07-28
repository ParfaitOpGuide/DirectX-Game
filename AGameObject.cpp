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

void AGameObject::attachComponent(AComponent* component)
{
	if (component)
	{
		componentList.push_back(component);
		component->attachOwner(this);
	}
}

void AGameObject::detachComponent(AComponent* component)
{
	if (component)
	{
		auto it = std::find(componentList.begin(), componentList.end(), component);
		if (it != componentList.end())
		{
			componentList.erase(it);
			component->detachOwner();
		}
	}
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

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 temp;
	this->localMatrix.setIdentity();

	temp.setRotationZ(localRotation.m_z);
	this->localMatrix *= temp;
	temp.setRotationY(localRotation.m_y);
	this->localMatrix *= temp;
	temp.setRotationX(localRotation.m_x);
	this->localMatrix *= temp;

	temp.setTranslation(localPosition);
	this->localMatrix *= temp;

	static float matrix[16];

	matrix[0] = this->localMatrix.m_mat[0][0];
	matrix[1] = this->localMatrix.m_mat[0][1];
	matrix[2] = this->localMatrix.m_mat[0][2];
	matrix[3] = this->localMatrix.m_mat[0][3];

	matrix[4] = this->localMatrix.m_mat[1][0];
	matrix[5] = this->localMatrix.m_mat[1][1];
	matrix[6] = this->localMatrix.m_mat[1][2];
	matrix[7] = this->localMatrix.m_mat[1][3];

	matrix[8] = this->localMatrix.m_mat[2][0];
	matrix[9] = this->localMatrix.m_mat[2][1];
	matrix[10] = this->localMatrix.m_mat[2][2];
	matrix[11] = this->localMatrix.m_mat[2][3];

	matrix[12] = this->localMatrix.m_mat[3][0];
	matrix[13] = this->localMatrix.m_mat[3][1];
	matrix[14] = this->localMatrix.m_mat[3][2];
	matrix[15] = this->localMatrix.m_mat[3][3];

	return &matrix[0];
}
