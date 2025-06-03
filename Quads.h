#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "Cube.h"


/*struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};*/

class Quads
{
public:
	Quads();
	//constructor that makes it so we only need to give our center and size for recs and squares
	//different class needed for triangles in the future
	Quads(float width, float height, float centerx, float centery, std::vector<Vector3D> colors, std::vector<Vector3D> colors2);

	void draw();
	void createBuffer(void** shader_byte_code, size_t* size_shader);
	void destroy();

	vertex list[4];
	VertexBuffer* m_vb;
};
