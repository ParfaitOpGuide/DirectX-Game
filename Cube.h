#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "AGameObject.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Camera.h"
#include "AComponent.h"
#include "PhysicsSystem.h"



class Cube : public AGameObject
{
public:
	Cube();
	Cube(float width, float height, float depth, float centerx, float centery, float centerz, Vector3D speed, Vector3D rotation, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name, RasterState* m_raster);

	void update(float deltaTime, float width, float height, Camera cam, bool isPers);
	void draw(float width, float height, VertexShaderPtr m_vs, PixelShaderPtr m_ps, float deltaTime, std::vector<Camera> camList, int currentCam);
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void createBuffer(Cube copy);
	void destroy();

	Vector3D list[8];
	Vector2D texlist[4];
	vertex finlist[24];

	int index_list[36] =
	{
		//front
		0,1,2, // first tri
		2,3,0, // second tri
		//back
		4,5,6, // third tri
		6,7,4, //fourth tri
		//top
		8,9,10,
		10,11,8,
		//bottom
		12,13,14,
		14,15,12,
		//right
		16,17,18,
		18,19,16,
		//left
		20,21,22,
		22,23,20
	};
	float m_time = 0;
	float animation_speed = 1000.0f;
	float change_speed = 5.0f;
	bool increasing;
	float rotSpeed;
	Vector3D moveSpeed;
	bool ticked;
};