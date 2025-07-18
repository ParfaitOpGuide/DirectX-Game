#pragma once
#include "Vector3D.h"
#include "Vector2D.h"
#include "Camera.h"
#include<string>
#include <vector>
#include "RasterState.h"
#include "RenderSystem.h"
#include "Mesh.h"
#include "AComponent.h"
#include "PhysicsSystem.h"

using namespace std;
class VertexShader;
class PixelShader;

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
	Vector3D normcoord;
};

class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime, float width, float height, Camera cam, bool isPers) = 0;
	virtual void draw(float width, float height, VertexShaderPtr m_vs, PixelShaderPtr m_ps, float deltaTime, std::vector<Camera> camList, int currentCam) =0;
	virtual void createBuffer(void** shader_byte_code, size_t* size_shader) = 0;
	virtual void destroy() = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void attachComponent(AComponent* component, PhysicsSystem* phys);
	void detachComponent(AComponent* component, PhysicsSystem* phys);
	bool getComponentsOfTypeExists(AComponent::ComponentType type);

	void setLocalMatrix(float mat[16]);

	PhysicsSystem::ComponentList componentList;

	string name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;

	RasterState* m_raster;
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;

	bool matset;
	Matrix4x4 currMat;
};

