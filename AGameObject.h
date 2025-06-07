#pragma once
#include "Vector3D.h"
#include<string>
using namespace std;
class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime, float width, float height) = 0;
	virtual void draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime)=0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	string name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
};

