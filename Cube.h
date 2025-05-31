#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Matrix4x4.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

class Cube
{
public:
	Cube();
	//constructor that makes it so we only need to give our center and size for recs and squares
	//different class needed for triangles in the future
	Cube(float width, float height, float depth, float centerx, float centery, float centerz, std::vector<Vector3D> colors, std::vector<Vector3D> colors2);

	void draw();
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void destroy();

	vertex list[8];
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
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
};
