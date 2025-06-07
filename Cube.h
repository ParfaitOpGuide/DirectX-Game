#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "AGameObject.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Matrix4x4.h"


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
	Vector3D color;
	Vector3D color1;
};

class Cube : public AGameObject
{
public:
	Cube();
	//constructor that makes it so we only need to give our center and size for recs and squares
	//different class needed for triangles in the future
	Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2, string name);

	void update(float deltaTime, float width, float height);
	void draw(float width, float height, VertexShader* m_vs, PixelShader* m_ps, float deltaTime);
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void destroy();

	vertex list[8];
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	int index_list[36] =
	{
		//front
		0,1,2, // first tri
		2,3,0, // second tri
		//back
		4,5,6, // third tri
		6,7,4, //fourth tri
		//top
		1,6,5,
		5,2,1,
		//bottom
		7,0,3,
		3,4,7,
		//right
		3,2,5,
		5,4,3,
		//left
		7,6,1,
		1,0,7
	};
	float m_time = 0;
	float animation_speed = 1000.0f;
	float change_speed = 5.0f;
	bool increasing;
};
